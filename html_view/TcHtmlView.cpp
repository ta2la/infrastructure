//
// Copyright (C) 2013 Petr Talla. [petr.talla@gmail.com]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include "./TcHtmlView.h"
#include <TcCmdTransl.h>
#include "T2lCmdAlias.h"
#include "T2lCmdAliasCol.h"
#include <QVariant>
#include <QUrl>
#include <TcCmdTransl.h>
#include <TcCmdEngine.h>
#include <TcLock.h>
#include <assert.h>
#include "T2lQueue.h"
#include <QImage>

#ifndef FULLHTML
#elif WINDOWS
#include <QWebEnginePage>
#else
#include <QWebPage>
#include <QWebFrame>
#endif

#include <iostream>

using namespace T2l;
using namespace std;

#ifdef WINDOWS
class TcHtmlView::HtmlPage : public QWebEnginePage
{
public:
    HtmlPage(TcHtmlView& parent) : parent_(&parent) {}

    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
    {
        if (url.scheme() == "tcview" ) {
            parent_->urlHandler_(url);
        }
#ifdef WINDOWS
        else if (url.scheme() == "file" ) {
            parent_->urlHandler_(url);
        }
#endif

        return true;
    }

    TcHtmlView* parent_;
};
#endif

//=============================================================================
TcHtmlView::TcHtmlView() :
    forceChanged_(true)
{
#ifndef FULLHTML

#elif WINDOWS
    setPage(new HtmlPage(*this));
#else
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
#endif

#ifdef FULLHTML
    QObject::connect(this, SIGNAL(linkClicked(const QUrl&)), this, SLOT(urlHandler_(const QUrl&)));
#else
    QObject::connect(this, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(urlHandler_(const QUrl&)));
#endif
}

//=============================================================================
void TcHtmlView::execute(QVariant cmd)
{   //TcLock lock;

    QString argsStr(cmd.toByteArray().data());

    argsStr = argsStr.simplified();

    QStringList items = argsStr.split(" ");

    CmdAlias* alias = NULL;

    if (items.size() > 0) {
        alias = CmdAliasCol::instance().get( items.first().toStdString().c_str() );
    }

    if (alias == NULL) {
        if ( Queue::instance()->offerText(cmd.toByteArray()) == false ) {
            //TcCmdTransl::xcall(cmd.toByteArray(), true);
            //cout << "CMD: " << cmd.toByteArray().data() << endl;
            TcCmdTransl::xcall(cmd.toByteArray().data(), true);
        }
        return;
    }

    QString cmds(alias->content());
    for (int i = 1; i < items.size(); i++) {
        QString variable;
        variable = variable.sprintf("%%%d", i);
        cmds.replace(variable, items.at(i));
    }

    QStringList lines = cmds.split("\n");
    for (int i = 0; i < lines.size(); i++) {
        QString line = lines.at(i);
        bool skip = false;
        for (int i = 0; i < 10; i++) {
            QString variable;
            variable = variable.sprintf("%%%d", i);
            if (line.contains(variable)) {
                skip = true;
                break;
            }
        }
        if (skip) continue;

        TcCmdTransl::xcall(line.toStdString().c_str(), true);
    }
}

#ifndef FULLHTML
QVariant TcHtmlView::loadResource(int type, const QUrl &name)
{
    if ( name.path().contains(".png") ) {
        QImage image(name.path());
        return image;
    }

    return QVariant();
}
#endif

//=============================================================================
void TcHtmlView::urlHandler_(const QUrl& url)
{

    QString urlScheme = url.scheme();
    QString urlFragment = url.fragment();
    QString urlHost = url.fragment();
    QString urlPath = url.path();
    QString urlQuery = url.query();

    if (url.scheme() == "tcview" ) {
        QString cmd(QUrl::fromPercentEncoding(url.fragment().toLatin1()));
        //cout << "CMD: " << cmd.toUtf8().data() << endl;
        TcCmdTransl::xcall( cmd.toUtf8().data(), true );
    }
#ifdef WINDOWS
    else if (url.scheme() == "file") {

        QString urls = url.path();
        urls = urls.right(urls.count() - urls.lastIndexOf('/') - 1);
        urls.append(" ");
        urls.append("");

        QString cmds = url.query();
        cmds.replace("cmd=", "");
        cmds = cmds.replace('+', ' ');

        QString cmd( urls + " \"" + cmds + "\"");

        //cout << "CMD: " << cmd.toUtf8().data() << endl;
        TcCmdTransl::xcall( cmd.toUtf8().data(), true );
    }
#endif
    else
    {   QString URL = url.toString();
#ifdef FULLHTML
        setUrl(URL);
#elifndef WINDOWS
        page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
#endif
    }

    forceChanged_ = true;
}

//=============================================================================

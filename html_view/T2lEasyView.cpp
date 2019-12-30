//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEasyView.h"

#include "T2lHtmlTabsRegistry.h"

#include "TcCmdEngine.h"
#include "TcSysInfo.h"

#include "FlowLayout.h"

#include "T2lEasyViewTml.h"

#include <QGraphicsProxyWidget>

#include <QToolBar>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QIcon>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextStream>
#include "T2lAfile.h"
#include "T2lAfileRecord.h"
#include <QDesktopServices>
#include "T2lEasyViewHtml.h"
//#include "T2lEasyViewButton.h"
#include <QStackedLayout>
#include "T2lEasyApp.h"

#include "TcCmdTransl.h"

#include <iostream>

#include <QApplication>
#include <T2lEasyViewTab.h>

using namespace T2l;
using namespace std;

//QTextBrowser* html = NULL;

string EasyView::active_ = "cad";

#define TAB_HEIGHT 40

//=============================================================================
EasyView::EasyView()
{
    setWindowFlags(Qt::WindowStaysOnTopHint);

    resize(700, 250);
    setWindowTitle("Cad2l");
    QString iconName = EasyApp::instance().dirResource() + "/honney_annot.png";
    setWindowIcon(QIcon(iconName));

    //=======================================================
    tabs_ = new QWidget(this);
    tabs_->move(0,0);
    tabs_->resize(10000, TAB_HEIGHT);

    main_ = new QWidget(this);
    main_->move(0,TAB_HEIGHT);

    //=======================================================
    stacked_ = new QStackedLayout();

    main_->setLayout(stacked_);

    //=======================================================
    tabs_->show();
    main_->show();
}

//=============================================================================
void EasyView::createTab( const char* id, QWidget* widget )
{
    EasyViewTab* tab = new EasyViewTab(this, id, widget );
    tabItems_.append(tab);
    stacked_->addWidget(tab->widget_);
}

//=============================================================================
void EasyView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    tabs_->resize(width(), TAB_HEIGHT);
    main_->resize(width(), height()-TAB_HEIGHT);
}

//=============================================================================
void EasyView::onEmptyQueue()
{
    for (int i = 0; i < tabItems_.count(); i++) {
        EasyViewTab* tab = tabItems_.at(i);

        if (active_ == tab->id_) {
            tab->button_->setText(QString(">> ") + tab->id_.c_str());
            stacked_->setCurrentWidget(tab->widget_);
        }
        else {
            tab->button_->setText(QString() + tab->id_.c_str());
        }
    }
}

//=============================================================================
void EasyView::urlHandler_(const QUrl& url)
{
    QString urlScheme = url.scheme();
    QString urlFragment = url.fragment();
    QString urlHost = url.fragment();
    QString urlPath = url.path();
    QString urlQuery = url.query();

    if (url.scheme() != "tcview" ) return;

    QString cmd(QUrl::fromPercentEncoding(url.fragment().toLatin1()));
    TcCmdTransl::xcall( cmd.toUtf8().data(), true );
}

//=============================================================================
void EasyView::urlHandlerHtml_(const QUrl& url)
{
    urlHandler_(url);
}

//=============================================================================
/*void EasyView::onLinkActivated(const QString& link)
{
    urlHandler_(link);
}*/

//=============================================================================
EasyViewTml* EasyView::loadTml(QString content, const char* id)
{
    EasyViewTml* widget = new EasyViewTml(id);
    widget->load(content);
    widget->show();

    return widget;
}

//=============================================================================
/*QTextBrowser* EasyView::loadHtml(QString content)
{
    EasyViewHtml* widget = new EasyViewHtml();
    content = "";
    for (int i = 0; i < 50; i++) content+="text<br>";

    widget->setHtml(content);

    QObject::connect(widget, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(urlHandlerHtml_(const QUrl&)));

    return widget;
}*/

//=============================================================================

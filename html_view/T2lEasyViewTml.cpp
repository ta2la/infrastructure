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
#include "T2lEasyViewTml.h"
#include "TcCmdTransl.h"
#include "T2lHtmlTabsRegistry.h"
#include "TcHtmlViewTabbed.h"
#include "T2lEasyViewButton.h"
#include "T2lEasyViewCtrl_edit.h"

#include <QTextStream>
#include <T2lAfile.h>
#include <QVBoxLayout>
#include <FlowLayout.h>
#include "T2lAfileAttr.h"
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <T2lAfileRecord.h>

#include <QLineEdit>

#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
EasyViewTml::EasyViewTml(const char* refresher) :
    refresher_(refresher)
{

}

//=============================================================================
void EasyViewTml::onEmptyQueue()
{
    if (refresher_.empty()) return;

    std::string cmd("tab_set_");
    cmd += refresher_.c_str();
    EXECUTE(cmd.c_str());

    HtmlTabsRegistry::instance().tabGet_(refresher_.c_str())->content();

    QString content(HtmlTabsRegistry::instance().tabGet_(refresher_.c_str())->content());
    load(content);
}

//=============================================================================
void EasyViewTml::load(QString content)
{
    if (layout()) {
        for (int i = 0; i < items_.count(); i++) {
            layout()->removeWidget(items_.at(i));
            delete items_.at(i);
        }
        items_.clear();
        layout()->removeWidget(this);
        delete layout();
    }

    QString contents = content.replace("<br>", "\n");
    QTextStream stream(&contents);

    Afile afile;
    afile.loadStream(stream);

    QVBoxLayout *wlayout = new QVBoxLayout;

    FlowLayout *flowLayout = new FlowLayout();
    for ( int i = 0; i < afile.recordCount(); i++) {
        AfileRecord* reci =  afile.recordGet(i);

        AfileAttr* typeA = reci->attrsGet("type");
        if (typeA == nullptr) continue;
        if ( typeA->value() != "control") continue;

        QString text = "";
        AfileAttr* textA = reci->attrsGet("text");
        if (textA != nullptr) text = textA->value();

        AfileAttr* cmdA = reci->attrsGet("cmd");
        QString cmd;
        if (cmdA != nullptr) cmd = cmdA->value();

        AfileAttr* controlA = reci->attrsGet("control");
        if (controlA == nullptr) continue;
        if ( controlA->value() == "text") {

            if (cmd.isEmpty() == false) {
                text = QString("<a href='tcview:://#") + cmd + "'>" + text + "</a>";
            }

            QLabel* label = new QLabel();
            label->setTextFormat(Qt::RichText);
            label->setTextInteractionFlags(Qt::TextBrowserInteraction);
            label->setText(text);
            connect(label, SIGNAL(linkActivated(const QString&)), this, SLOT(onLinkActivated(const QString&)) );
            flowLayout->addWidget(label);

            items_.append(label);
        }
        if ( controlA->value() == "button") {
            EasyViewButton* button = new EasyViewButton(cmd.toStdString().c_str());
            button->setText(text);
            flowLayout->addWidget(button);

            bool mark = false;
            AfileAttr* markA = reci->attrsGet("mark");
            if (markA != nullptr) mark = true;

            AfileAttr* iconA = reci->attrsGet("icon");
            if (iconA != nullptr) {
                button->setImage( iconA->value() );
            }
            AfileAttr* colorA = reci->attrsGet("color");
            if (colorA != nullptr) {
                QStringList colors = colorA->value().split(",");
                if (colors.count() >= 3) {
                    button->setColorBack(QColor(colors[0].toInt(),
                                                colors[1].toInt(),
                                                colors[2].toInt()), mark);
                }
            }
            AfileAttr* activeA = reci->attrsGet("active");
            if (activeA != nullptr) {
                button->setActiveOn();
            }


            items_.append(button);
        }
        if ( controlA->value() == "edit") {
            EasyViewCtrl_edit* line = new EasyViewCtrl_edit(cmd.toStdString().c_str());
            AfileAttr* widthA = reci->attrsGet("width");
            if (widthA) {
                int width = widthA->value().toInt();
                line->setFixedWidth(width);
            }
            else {
                line->setMinimumWidth(300);
            }

            flowLayout->addWidget(line);

            line->setText(text);

            items_.append(line);
        }
    }
    wlayout->addLayout(flowLayout);

    setLayout(wlayout);
}

//=============================================================================
void EasyViewTml::urlHandler_(const QUrl& url)
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
void EasyViewTml::onLinkActivated(const QString& link)
{
    urlHandler_(link);
}


//=============================================================================

//
// Copyright (C) 2019, 2024 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEasyViewTmlBase.h"
#include "TcCmdTransl.h"
#include "T2lEasyViewButton.h"
#include "T2lEasyViewCtrl_edit.h"
#include "T2lEasyViewSpacer.h"
#include "T2lEasyViewButtonEx.h"

#include <QTextStream>
#include <T2lAfile.h>
#include <QVBoxLayout>
#include <FlowLayout.h>
#include "T2lAfileAttr.h"
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <T2lAfileRecord.h>
#include "T2lLayoutFlow.h"

#include <QLineEdit>
#include <QScreen>

#include <QApplication>

using namespace T2l;
using namespace std;

//=============================================================================
EasyViewTmlBase::EasyViewTmlBase() :
    flowLayout_(nullptr)
{
}

//=============================================================================
void EasyViewTmlBase::load(QString content)
{

    if (content == lastContent_) {
        //if (lastScreen_ == QGuiApplication::primaryScreen()->screenNumber(this) ) { //TODO_NOW
            return;
        //}
    }

    //lastScreen_ = QApplication::desktop()->screenNumber(this);
    lastContent_ = content;

    if (layout()) {
        if (flowLayout_ != nullptr) {
            QLayoutItem* child;
            while ( flowLayout_->count() != 0 ) {
                child = flowLayout_->takeAt ( 0 );
                /*if ( child->layout() != 0 ) {
                    remove ( child->layout() );
                } else*/ if ( child->widget() != 0 ) {
                    delete child->widget();
                }

                delete child;
            }

            layout()->removeItem(flowLayout_);
            delete flowLayout_;
        }
        layout()->removeWidget(this);
        delete layout();
    }

    QString contents = content.replace("<br>", "\n");
    QTextStream stream(&contents);

    Afile afile;
    afile.load(stream);

    QVBoxLayout *wlayout = new QVBoxLayout;

    LayoutFlow *flowLayout = new LayoutFlow(LayoutFlow::VERAL_TOP);
    flowLayout_ = flowLayout;
    for ( int i = 0; i < afile.recordCount(); i++) {
        AfileRecord* reci =  afile.recordGet(i);

        AfileAttr* typeA = reci->attrGet("type");
        if (typeA == nullptr) continue;
        if ( typeA->value() != "control") continue;

        QString text = "";
        AfileAttr* textA = reci->attrGet("text");
        if (textA != nullptr) text = textA->value();

        QString cmd;
        for ( int ci = 0; ci < reci->attrCount(); ci++) {
            AfileAttr* cmdA = reci->attrGet("cmd", ci);
            if (cmdA == nullptr) break;
            if (!cmd.isEmpty()) cmd += ";";
            cmd += cmdA->value();
        }

        AfileAttr* controlA = reci->attrGet("control");
        if (controlA == nullptr) continue;
        if ( controlA->value() == "spacer") {
            AfileAttr* spacerAttr = reci->attrGet("spacer");
            AfileAttr* valueAttr = reci->attrGet("value");
            if (spacerAttr) {
                EasyViewSpacer::ESpacerType spacer = EasyViewSpacer::SPACER_OFFSET_X;
                int value = 0;
                if (valueAttr) value = valueAttr->value().toUInt();

                if ( spacerAttr->value() == "offset_x" ) {
                    spacer = EasyViewSpacer::SPACER_OFFSET_X;
                }
                else if ( spacerAttr->value() == "newline" ) {
                    spacer = EasyViewSpacer::SPACER_NEWLINE;
                }
                else if ( spacerAttr->value() == "relative_y" ) {
                    spacer = EasyViewSpacer::SPACER_RELATIVE_Y;
                }
                else if ( spacerAttr->value() == "minx" ) {
                    spacer = EasyViewSpacer::SPACER_MINX;
                }

                flowLayout->addItem(new EasyViewSpacer(spacer, value));
            }
        }
        if ( controlA->value() == "text") {

            if (cmd.isEmpty() == false) {
                text = QString("<a href='tcview:://#") + cmd + "'>" + text + "</a>";
            }

            if (text == "<hup>") {
                flowLayout->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_NEWLINE));
            }
            else if (text == "<space>") {
                flowLayout->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_OFFSET_X, 5));
            }
            /*else if (text == "<line>") {
                QFrame* line = new QFrame;
                line->setFixedHeight(2);
                line->setFrameShape(QFrame::HLine);
                flowLayout->addWidget(line);
                line->show();
            }*/
            else {
                flowLayout->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_RELATIVE_Y, 5));

                QLabel* label = new QLabel();
                label->setTextFormat(Qt::RichText);
                label->setTextInteractionFlags(Qt::TextBrowserInteraction);
                label->setText(text);
                if (text.contains("img")) label->setStyleSheet("border: 1px solid darkgray");
                connect(label, SIGNAL(linkActivated(const QString&)), this, SLOT(onLinkActivated(const QString&)) );
                flowLayout->addWidget(label);
            }
        }
        if ( controlA->value()=="button" ) {
            EasyViewButton* button = new EasyViewButton(cmd.toStdString().c_str());
            button->setText(text);

            bool mark = false;
            AfileAttr* markA = reci->attrGet("mark");
            if (markA != nullptr) mark = true;

            AfileAttr* iconA = reci->attrGet("icon");
            if (iconA != nullptr) {
                button->setImage( iconA->value() );
                button->setIconSize(QSize(24,24));
            }
            else {
                flowLayout->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_RELATIVE_Y, 2));
            }

            AfileAttr* colorA = reci->attrGet("color");
            if (colorA != nullptr) {
                QStringList colors = colorA->value().split(",");
                if (colors.count() >= 3) {
                    button->setColorBack(QColor(colors[0].toInt(),
                                                colors[1].toInt(),
                                                colors[2].toInt()), mark);
                    button->setIconSize(QSize(24,24));
                }
            }
            AfileAttr* activeA = reci->attrGet("active");
            if (activeA != nullptr) {
                button->setActiveOn();
            }

            AfileAttr* iconSize = reci->attrGet("iconsize");
            if (iconSize) {
                int size = iconSize->value().toInt();
                button->setIconSize(QSize(size, size));
            }

            flowLayout->addWidget(button);
        }
        if ( controlA->value()=="buttonex" ) {
            EasyViewButtonEx* button = new EasyViewButtonEx(cmd.toStdString().c_str());
            AfileAttr* iconA = reci->attrGet("icon");
            if (iconA != nullptr) {
                button->setImage( iconA->value() );
            }
            button->setText(text);

            AfileAttr* iconSize = reci->attrGet("iconsize");
            if (iconSize) {
                int size = iconSize->value().toInt();
                button->setIconSize(QSize(size, size));
            }

            AfileAttr* activeA = reci->attrGet("active");
            if (activeA != nullptr) {
                button->setActiveOn();
            }

            flowLayout->addWidget(button);
        }
        if ( controlA->value() == "edit") {
            flowLayout->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_RELATIVE_Y, 3));
            EasyViewCtrl_edit* line = new EasyViewCtrl_edit(cmd.toStdString().c_str());
            AfileAttr* widthA = reci->attrGet("width");
            if (widthA) {
                int width = widthA->value().toInt();
                line->setFixedWidth(width);
            }
            else {
                line->setMinimumWidth(300);
            }

            flowLayout->addWidget(line);

            line->setText(text);
        }
        if ( controlA->value() == "hr") {
            QLabel* line = new QLabel("-------------------------------------");
            flowLayout->addWidget(line);
        }
    }
    wlayout->addLayout(flowLayout);

    setLayout(wlayout);
}

//=============================================================================
void EasyViewTmlBase::urlHandler_(const QUrl& url)
{
    QString urlScheme   = url.scheme();
    QString urlFragment = url.fragment();
    QString urlHost     = url.fragment();
    QString urlPath     = url.path();
    QString urlQuery    = url.query();

    if (url.scheme() != "tcview" ) return;

    //QString cmd(QUrl::fromPercentEncoding(url.fragment().toLatin1()));
    QString cmd(QUrl::fromPercentEncoding(url.fragment().toUtf8()));
    TcCmdTransl::xcall( cmd.toUtf8().data()/*, true*/ );
}

//=============================================================================
void EasyViewTmlBase::substitute(QString& content)
{
    content = content.replace("T:C;", "type: control;");
    content = content.replace("C:T;", "control: text;");
    content = content.replace("C:B;", "control: button;");
    content = content.replace("C:E;", "control: edit;");
    content = content.replace(";", "\n");
    content = content.replace("&nbsp_", "&nbsp;");
}

//=============================================================================
void EasyViewTmlBase::substituteEx(QString& content)
{
    content = content.replace("TEXT:",    "type: control;control:text;text:");
    content = content.replace("BUTTON:",  "type: control;control:button;cmd:");
    content = content.replace("BUTTONEX:","type: control;control:buttonex;cmd:");
    content = content.replace("EDIT:",    "type: control;control:edit;cmd:");
    content = content.replace("NEWLINE:", "type: control;control:spacer;spacer:newline");
    content = content.replace("SPACE:",   "type: control;control:spacer;spacer:offset_x;value:5");
    content = content.replace("TAB:",     "type: control;control:spacer;spacer:minx;value:");
    content = content.replace(";", "\n");
    content = content.replace("&nbsp_", "&nbsp;");
}


//=============================================================================
void EasyViewTmlBase::onLinkActivated(const QString& link)
{
    urlHandler_(link);
}


//=============================================================================

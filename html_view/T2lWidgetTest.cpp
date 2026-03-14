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
#include "T2lWidgetTest.h"

#include "TcCmdEngine.h"
#include "TcSysInfo.h"

#include "FlowLayout.h"
#include "T2lLayoutFlow.h"
#include "T2lEasyViewSpacer.h"
#include "T2lEasyViewButton.h"
#include "T2lEasyApp.h"

#include <QGraphicsProxyWidget>

#include <QToolBar>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QIcon>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include <iostream>

using namespace T2l;
using namespace std;

void WidgetTest::doit_()
{
}

//=============================================================================
WidgetTest::WidgetTest(const QString& resourceDir):
    TcCmdProcess(&TcCmdEngine::engine()),
    resourceDir_(resourceDir)
{
    TcCmdEngine::engine().append(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    resize(700, 250);
    setWindowTitle("LabeL T2L");
    setWindowIcon(QIcon(resourceDir_ + "/honney_annot.png"));
    setWindowIconText("LabeL T2L");

    textEdit_ = new QLineEdit();
    textEdit_->setText("");
    textEdit_->show();

    QObject::connect(textEdit_, SIGNAL(returnPressed()), this, SLOT(enterText_()));

    QVBoxLayout *layout = new QVBoxLayout;

    //======================================================
    QHBoxLayout *layoutEdit = new QHBoxLayout;
    layoutEdit->addWidget(textEdit_);
    textLabel_ = new QLabel("aaa");
    layoutEdit->addWidget(textLabel_);
    layout->addLayout(layoutEdit);

    QLabel* text1 = new QLabel("Simsala <b>bim</b> ba");
    text1->adjustSize();

    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");

    //=======================================================
    QHBoxLayout *lh = new QHBoxLayout;
    lh->addWidget(button1);
    lh->addWidget(button5);

    layout->addLayout(lh);

    //=======================================================
    FlowLayout *flowLayout = new FlowLayout();
    flowLayout->addWidget(new QPushButton(tr("Short")));
    flowLayout->addWidget(new QPushButton(tr("Longer")));
    flowLayout->addWidget(new QLabel("ahojky"));
    flowLayout->addWidget(new QPushButton(tr("Different text")));
    QLabel* br = new QLabel("<hup>");
    br->resize(1, br->height());
    br->setTextFormat(Qt::RichText);
    flowLayout->addWidget(br);
    flowLayout->addWidget(new QPushButton(tr("More text")));
    flowLayout->addWidget(new QPushButton(tr("Laaaaaaaa 1")));
    flowLayout->addWidget(new QPushButton(tr("Laaaaaaaa 2")));
    flowLayout->addWidget(new QPushButton(tr("Even longer button text")));
    layout->addLayout(flowLayout);

    //======================================================
    FlowLayout *flowLayout2 = new FlowLayout();
    flowLayout2->addWidget(new QPushButton(tr("sss Short")));
    flowLayout2->addWidget(new QPushButton(tr("sss Longer")));
    flowLayout2->addWidget(new QLabel("sahojky"));
    flowLayout2->addWidget(new QPushButton(tr("ssssssDifferent text")));
    flowLayout2->addWidget(new QPushButton(tr("sssssssssMore text")));
    flowLayout2->addWidget(new QPushButton(tr("ssssssssssLaaaaaaaa 1")));
    flowLayout2->addWidget(new QPushButton(tr("sssssssssssLaaaaaaaa 2")));
    flowLayout2->addWidget(new QPushButton(tr("ssssssssssssssssss Even longer button text")));
    layout->addLayout(flowLayout2);

    //======================================================
    LayoutFlow *layoutFlow = new LayoutFlow(nullptr, LayoutFlow::VERAL_MID);
    layoutFlow->addWidget(new QPushButton(tr("sss Short")));
    layoutFlow->addWidget(new QPushButton(tr("sss Longer")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_NEWLINE));
    layoutFlow->addWidget(new QLabel("sahojky"));
    layoutFlow->addWidget(new QPushButton(tr("ssssssDifferent text")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_OFFSET_X, 20));
    layoutFlow->addWidget(new QPushButton(tr("sssssssssMore text")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_OFFSET_X, 40));
    layoutFlow->addWidget(new QPushButton(tr("ssssssssssLaaaaaaaa 1")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_RELATIVE_Y, 10));
    layoutFlow->addWidget(new QPushButton(tr("sssssssssssLaaaaaaaa 2")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_RELATIVE_Y, 0));
    layoutFlow->addWidget(new QPushButton(tr("ssssssssssssssssss Even longer button text")));
    EasyViewButton* button = new EasyViewButton("");
    button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
    layoutFlow->addWidget(button);
    layout->addLayout(layoutFlow);

    layoutFlow = new LayoutFlow(nullptr, LayoutFlow::VERAL_TOP);
    button = new EasyViewButton("");
    button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
    layoutFlow->addWidget(button);

    QPixmap pixmap(EasyApp::instance().iconPath("icons/image"));
    QIcon icon(pixmap);
    QToolButton* but = new QToolButton(this);
    but->resize(200,200);
    but->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    but->setIcon(icon);
    but->setText("Sample text");
    but->setIconSize(QSize(60, 60));
    layoutFlow->addWidget(but);

    {
        QPushButton *button = new QPushButton;
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *label = new QLabel;
        label->setPixmap(QPixmap(EasyApp::instance().iconPath("icons/image")));
        button->setText("Button Text");
        layout->addWidget(label);
        layoutFlow->addWidget(button);
    }

    {
        QPushButton *button = new QPushButton;
        button->setIcon(QIcon(EasyApp::instance().iconPath("icons/image")));
        button->setText("Button Text");
        button->setIconSize(QSize(64, 64));
        button->setStyleSheet("QPushButton { text-align: bottom; }");
        layoutFlow->addWidget(button);
    }

    {
        QHBoxLayout *layout = new QHBoxLayout;
        QPushButton *button = new QPushButton;
        button->resize(200,200);
        QLabel *imageLabel = new QLabel;
        QLabel *textLabel = new QLabel("Text under image");

        QPixmap image(EasyApp::instance().iconPath("icons/image"));
        imageLabel->setPixmap(image);

        layout->addWidget(imageLabel);
        layout->addWidget(textLabel);
        button->setLayout(layout);

        layoutFlow->addWidget(button);
    }

    layout->addLayout(layoutFlow);

    layoutFlow = new LayoutFlow(nullptr, LayoutFlow::VERAL_MID);
    layoutFlow->addWidget(new QPushButton(tr("sss Short 1")));
    layoutFlow->addWidget(new QPushButton(tr("sss Short 2")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_OFFSET_X, 10));
    layoutFlow->addWidget(new QPushButton(tr("sss Longe 3")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_NEWLINE));
    button = new EasyViewButton("");
        button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
        layoutFlow->addWidget(button);
    layoutFlow->addWidget(new QPushButton(tr("sss Longe 4")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_RELATIVE_Y, 10));
    layoutFlow->addWidget(new QPushButton(tr("sss Short 5")));
    layoutFlow->addWidget(new QPushButton(tr("sss Longe 6")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_NEWLINE));
    button = new EasyViewButton("");
        button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
        layoutFlow->addWidget(button);
    layoutFlow->addWidget(new QPushButton(tr("sss Longe 7")));
    layoutFlow->addWidget(new QPushButton(tr("sss Longe 8")));
    layoutFlow->addItem(new EasyViewSpacer(EasyViewSpacer::SPACER_NEWLINE));
    button = new EasyViewButton("");
        button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
        layoutFlow->addWidget(button);
    button = new EasyViewButton("");
        button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
        layoutFlow->addWidget(button);
    button = new EasyViewButton("");
        button->setImage(EasyApp::instance().iconPath("icons/create_dimm"));
        layoutFlow->addWidget(button);
    layoutFlow->addWidget(new QPushButton(tr("sss Short 9")));
    layoutFlow->addWidget(new QPushButton(tr("sss Longe 10")));
    layout->addLayout(layoutFlow);

    layout->addStretch();

    resize(600, 400);

    setLayout(layout);
}

//=============================================================================
int WidgetTest::execute(TcArgCol& args, bool isFrontController)
{
    textLabel_->setText(TcSysInfo::instance().getCommandBase());
    return 0;
}

//=============================================================================
void WidgetTest::enterText_()
{
    TcSysInfo::instance().exeCommandBase(textEdit_->text().toStdString().c_str());
    textEdit_->setText("");
}

//=============================================================================

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
//#include "HnwWidget_button.h"
//#include "HnwWidget_cmdDialog.h"
//#include "HnwWidget_toolbar.h"

#include "TcCmdEngine.h"
#include "TcSysInfo.h"

#include "FlowLayout.h"

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

    //Widget_toolbar* toolbar = new Widget_toolbar(this);

    textEdit_ = new QLineEdit();
    textEdit_->setText("");
    textEdit_->show();

    QObject::connect(textEdit_, SIGNAL(returnPressed()), this, SLOT(enterText_()));

    //Widget_cmdDialog* tb = new Widget_cmdDialog(this);
    //tb->setFrameStyle(QFrame::NoFrame);
    //QString style("background-color:");
    //style.append( palette().color(QWidget::backgroundRole()).name() );
    //style.append(";");
    //tb->setStyleSheet(style);

    QVBoxLayout *layout = new QVBoxLayout;

    //======================================================
    //layout->addStretch();
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
    //layout->addStretch();
    QHBoxLayout *lh = new QHBoxLayout;
    lh->addWidget(button1);
    lh->addWidget(button5);

    layout->addLayout(lh);

    //=======================================================
    //layout->addStretch();
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
    //layout->addStretch();
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

    layout->addStretch();

    resize(600, 400);

    setLayout(layout);

    //layout->addSpacerItem(new QSpacerItem(10, 300, QSizePolicy::Expanding) );
}

//=============================================================================
int WidgetTest::execute(TcArgCol& args, bool isFrontController)
{
    textLabel_->setText(TcSysInfo::instance().getCommandBase());
}

//=============================================================================
void WidgetTest::enterText_()
{
    TcSysInfo::instance().exeCommandBase(textEdit_->text().toStdString().c_str());
    textEdit_->setText("");
}

//=============================================================================

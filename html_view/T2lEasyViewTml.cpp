//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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

#include <QTextStream>
#include <T2lAfile.h>
#include <QVBoxLayout>
#include <FlowLayout.h>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <T2lAfileRecord.h>
#include "T2lLayoutFlow.h"

#include <QLineEdit>
#include <QScreen>

#include <QApplication>
//#include <QDesktopWidget>

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
    //parentWidget()->setUpdatesEnabled(false);

    if (refresher_.empty()) return;

    std::string cmd("tab_set_");
    cmd += refresher_.c_str();
    EXECUTE(cmd.c_str())

    //HtmlTabsRegistry::instance().tabGet_(refresher_.c_str())->content();

    QString content = QString::fromStdString(HtmlTabsRegistry::instance().tabGet_(refresher_.c_str())->contentEx());
    QString last = content.right(100);
    load(content);
}

//=============================================================================

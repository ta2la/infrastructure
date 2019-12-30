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
#include "T2lEasyViewHtml.h"
#include "TcCmdTransl.h"
#include "T2lHtmlTabsRegistry.h"
#include "TcHtmlViewTabbed.h"

#include <iostream>

using namespace T2l;
using namespace std;

std::string EasyViewHtml::activeSingle_ = "cad";

//=============================================================================
EasyViewHtml::EasyViewHtml()
{
}

//=============================================================================
QVariant EasyViewHtml::loadResource(int type, const QUrl &name)
{
    if ( name.path().contains(".png") ) {
        QImage image(name.path());
        return image;
    }

    return QVariant();
}

//=============================================================================
void EasyViewHtml::onEmptyQueue()
{
    string aaa = active_;
    if (aaa.empty()) aaa = activeSingle_;

    //<STEP> refreshing the content
    std::string cmd("tab_set_");
    cmd += aaa.c_str();
    EXECUTE(cmd.c_str());

    TcHtmlViewTab* tab = HtmlTabsRegistry::instance().tabGet_(aaa.c_str());
    //HtmlTabsRegistry::instance().tabGet("cad");

    QString contentBody = "NO CONTENT";

    if ( tab ) {
        contentBody = tab->content();
    }

    setHtml(contentBody);

    cout << "refresh" << endl;
}

//=============================================================================

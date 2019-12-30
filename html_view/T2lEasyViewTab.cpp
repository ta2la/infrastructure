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
#include "T2lEasyViewTab.h"
#include "T2lEasyView.h"
#include "T2lEasyViewHtml.h"
#include <QString>

using namespace T2l;

//=============================================================================
EasyViewTab::EasyViewTab(EasyView* parent, const char* id, QWidget* widget ) :
    id_(id)
{
    QString cmd = "set_main_tab ";
    cmd += id;

    button_ = new EasyViewButton(cmd.toStdString().c_str(), parent->tabs_);
    button_->setText(id);
    button_->move((parent->tabItems_.count())*90, 5);
    button_->resize(80, 30);
    button_->show();

    if (widget == NULL) {
        EasyViewHtml* view = new EasyViewHtml();
        view->activeSet(id);
        view->setHtml("empty");
        QObject::connect(view, SIGNAL(anchorClicked(const QUrl&)), parent, SLOT(urlHandlerHtml_(const QUrl&)));
        widget_ = view;
        //parent_->stacked_->addWidget(view);
    }
    else {
        widget_ = widget;
    }
}

//=============================================================================
EasyViewTab::~EasyViewTab()
{
}

//=============================================================================
EasyViewHtml* EasyViewTab::getAsEasyViewHtml()
{
    return dynamic_cast<EasyViewHtml*>(widget_);
}

//=============================================================================

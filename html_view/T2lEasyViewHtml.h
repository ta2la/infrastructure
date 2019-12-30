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
#pragma once

#include "TcCmdEngineMsgReceiver.h"
#include "TcHtmlViewTab.h"

#include <QVariant>
#include <QTextBrowser>
#include <QUrl>

namespace T2l {

//=============================================================================
class EasyViewHtml : public QTextBrowser, public TcCmdEngineMsgReceiver {
    virtual QVariant loadResource(int type, const QUrl &name);
//=============================================================================
public:
//<CONSTRUCTION>
    EasyViewHtml();
    virtual ~EasyViewHtml() {}
//<METHOD>
    static std::string activeSingle() { return activeSingle_; }
    static void activeSingleSet(const char* active) {activeSingle_ = active; }

    std::string active() { return active_; }
    void        activeSet(const char* active) {active_ = active; }
//Q_OBJECT
//public slots:
//=============================================================================
//<QT>
//<DATA>
    static std::string activeSingle_;
    std::string active_;
//<OVERRIDES>
    virtual void onEmptyQueue();
};

} //namespace T2l

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
#pragma once

#include "./TcHtmlView.h"
#include <TcCmdEngineMsgReceiver.h>
#include <QString>
#include <list>

class TcHtmlViewTab;
class TcCmdLog;

//=============================================================================
class TcHtmlViewTabbed : public TcHtmlView, public TcCmdEngineMsgReceiver {
//=============================================================================
public:
//<CONSTRUCTION>
    TcHtmlViewTabbed();
    virtual ~TcHtmlViewTabbed();
//<METHODS>
    static TcHtmlViewTabbed& mainView();
    static noview() { noview_ = true; }
    void tabAdd(const char* id, const char* name);

    void tabSet(const char* id, const char* content);
    void tabSetCurrent(const char* id) {currentTab_ = id; }

    void tabSetAncient(const char* id);

    void setShowSysinfo(bool value) { showSysinfo_ = value; }

    TcCmdLog& log() { return *log_; }

    void appendSyles(const QString& styles) { styles_ += styles; }
    void appNameSet(const QString& name) { appName_ = name; }
//=============================================================================
//<OVERRIDES>
    virtual void onEmptyQueue();
//<DATA>
    std::string currentTab_;
    std::list<TcHtmlViewTab*> tabs_;
protected:
    TcCmdLog* log_; //TODO

    QString contentBody_;
    bool showSysinfo_;

    QString styles_;
    QString appName_;

    static bool noview_;
//<INTERNALS>
    TcHtmlViewTab* tabGet_(const char* id);
//<QT>
    Q_OBJECT
//<FRIENDS>
    friend class TcCmds_htmlView;
    friend class WrCmdsUi;
    friend class TcCmds_areaAnalyzer;
};

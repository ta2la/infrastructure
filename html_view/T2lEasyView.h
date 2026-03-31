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

//self
#include "T2lEasyViewTab.h"

//command registry
#include <TcCmdProcess.h>
#include <TcCmdEngineMsgReceiver.h>

//QT
#include <QStackedLayout>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextBrowser>

namespace T2l
{

class EasyViewTml;

//===================================================================
class EasyView : public QWidget, public TcCmdEngineMsgReceiver {
//===================================================================
public:
//<CONSTRUCTION>
    EasyView(const char* name);
    virtual ~EasyView();

    void createTab(const char* id, QWidget* widget = nullptr, const char* text = "");
//<METHODS>
    EasyViewTml*  loadTml(QString content, const char* id = "");

    static void activeSet(const char* value) { active_ = value; }
    static std::string active() { return active_; }

    static EasyView* instanceBase_;
    static EasyView* instanceBase() { return instanceBase_; }

    void tabButtonWidthSet(int value) { tabButtonWidth_ = value; }
    int tabButtonWidth() const { return tabButtonWidth_; }
//===================================================================
//<INTERNALS>
//<OVERRIDES>
    virtual void onEmptyQueue();
    virtual void resizeEvent(QResizeEvent *event);
protected:
//<DATA>
    static std::string active_;

    QList<EasyViewTab*> tabItems_;

    QWidget*        tabs_;
    QWidget*        main_;
    QStackedLayout* stacked_;
    int             tabButtonWidth_ {100};

//<QT>
    Q_OBJECT
private slots:
    void urlHandler_(const QUrl& url);
    void urlHandlerHtml_(const QUrl& url);
//<FRIENDS>
    friend class EasyViewTab;
};

} // namespace T2l

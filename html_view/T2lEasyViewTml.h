//
// Copyright (C) 20198 Petr Talla. [petr.talla@gmail.com]
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
class EasyViewTml : public QWidget, public TcCmdEngineMsgReceiver {

//=============================================================================
public:
//<CONSTRUCTION>
    EasyViewTml(const char* refresher = "");
    virtual ~EasyViewTml() {}
//<METHOD>
    void load(QString content);
//Q_OBJECT
//public slots:
//=============================================================================
//<DATA>
    std::string refresher_;
    QList<QWidget*> items_;
//<OVERRIDES>
    virtual void onEmptyQueue();
//<INTERNALS>
    void urlHandler_(const QUrl& url);
//<QT>
Q_OBJECT
private slots:
    void onLinkActivated(const QString& link);
};

} //namespace T2l

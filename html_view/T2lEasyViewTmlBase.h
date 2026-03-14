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
#pragma once

#include "TcCmdEngineMsgReceiver.h"

#include <QVariant>
#include <QUrl>
#include <QString>
#include <QWidget>
#include <QLayoutItem>

#include <QLayout>

namespace T2l {

//=============================================================================
class EasyViewTmlBase : public QWidget, public TcCmdEngineMsgReceiver {
// https://github.com/ta2la/infrastructure/wiki#EasyViewTml
//=============================================================================
public:
//<CONSTRUCTION>
    EasyViewTmlBase();
    virtual ~EasyViewTmlBase() {}
//<METHOD>
    virtual void load(QString content);
    static  void substitute(QString& content);
    static  void substituteEx(QString& content);
//=============================================================================
//<DATA>
    QString     lastContent_;
    int         lastScreen_;

    QLayout*    flowLayout_;
//<OVERRIDES>
//<INTERNALS>
    void urlHandler_(const QUrl& url);
//<QT>
Q_OBJECT
private slots:
    void onLinkActivated(const QString& link);
};

} //namespace T2l

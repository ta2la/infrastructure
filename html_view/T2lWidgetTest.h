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

#include <QWidget>
#include <QString>
#include "TcCmdProcess.h"
#include <QLabel>
#include <QLineEdit>

namespace T2l
{
//===================================================================
class WidgetTest : public QWidget, public TcCmdProcess {
//===================================================================
public:
//<CONSTRUCTION>
    WidgetTest(const QString& resourceDir);
    virtual ~WidgetTest() {}
//<METHODS>
    const QString& resourceDir() { return resourceDir_; }
//===================================================================
//<OVERRIDES>
    virtual int execute(TcArgCol& args, bool isFrontController);
protected:
//<DATA>
    QString  resourceDir_;
    QWidget* textWidget_;
    QLabel*    textLabel_;
    QLineEdit* textEdit_;
//<QT>
    Q_OBJECT
private slots:
    void doit_();
    void enterText_();
};

} // namespace T2l

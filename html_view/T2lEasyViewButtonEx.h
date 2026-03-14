//
// Copyright (C) 2023 Petr Talla. [petr.talla@gmail.com]
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

#include <QToolButton>
#include <string>

namespace T2l {

//=============================================================================
class EasyViewButtonEx : public QToolButton
{
public:
//<CONSTRUCTION>
    EasyViewButtonEx( const char* cmd, QWidget* parent = nullptr );
    virtual ~EasyViewButtonEx();
//<METHOD>
    void setActiveOn();
    void setImage( const QString& imagePath );

    void setCmd(const QString& cmd) { cmd_ = cmd.toStdString(); }

    //virtual void paintEvent(QPaintEvent *event);
//=============================================================================
//<QT>
//<DATA>
private:
    std::string cmd_;
Q_OBJECT
public slots:
    void onClick();
};

} //namespace T2l

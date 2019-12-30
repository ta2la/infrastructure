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

#include <QPushButton>
#include <string>

namespace T2l {

//=============================================================================
class EasyViewButton : public QPushButton
{
public:
//<CONSTRUCTION>
    EasyViewButton( const char* cmd, QWidget* parent = nullptr );
    virtual ~EasyViewButton();
//<METHOD>
    void setImage( const QString& imagePath );
    void setColorBack( const QColor& color, bool mark);
    void setActiveOn();
//=============================================================================
//<QT>
//<DATA>
private:
    std::string cmd_;
//<OVERRIDES>
Q_OBJECT
public slots:
    void onClick();
};

} //namespace T2l

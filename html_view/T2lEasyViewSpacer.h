//
// Copyright (C) 2022 Petr Talla. [petr.talla@gmail.com]
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

#include <QSpacerItem>

namespace T2l {

//=============================================================================
class EasyViewSpacer : public QSpacerItem
{
public:
//<ENUMS>
    enum ESpacerType {
        SPACER_OFFSET_X,
        SPACER_NEWLINE,
        SPACER_RELATIVE_Y,
        SPACER_MINX
    };
//<CONSTRUCTION>
    EasyViewSpacer(ESpacerType type, double value = 0);
    virtual ~EasyViewSpacer();
//<METHOD>
    ESpacerType type() { return type_; }
    double value() { return value_; }
//=============================================================================
//<QT>
//<DATA>
    double      value_;
    ESpacerType type_;
private:
//<OVERRIDES>
};

} //namespace T2l

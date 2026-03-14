//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lEasyViewTmlBase.h"

#include <QVariant>
#include <QUrl>
#include <QString>
#include <QWidget>
#include <QLayoutItem>

#include <QLayout>

namespace T2l {

//=============================================================================
class EasyViewTml : public EasyViewTmlBase {
// https://github.com/ta2la/infrastructure/wiki#EasyViewTml
//=============================================================================
public:
//<CONSTRUCTION>
    EasyViewTml(const char* refresher = "");
//<METHOD>
//=============================================================================
//<DATA>
    std::string refresher_;
//<OVERRIDES>
    virtual void onEmptyQueue();
//<INTERNALS>
//<QT>
Q_OBJECT
};

} //namespace T2l

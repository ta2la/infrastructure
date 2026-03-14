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

#include "T2lComRecItem.h"

#include <QList>
#include <QString>

#define COM_REC ComRecCol::instance()

namespace T2l {

//=============================================================================
class ComRecCol {
//=============================================================================
public:
//<CONSTRUCTION>
    ComRecCol();
    static ComRecCol& instance() {  static ComRecCol i; return i; }
//<METHODS>
//<ITEMS>
    int count() { return items_.size(); }
    ComRecItem* get(int index) { return items_.at(index); }

    void append(ComRecItem* item) { items_.append(item); }
    void append(const char* text) { append(new ComRecItem(text)); }
//<NEIGHBOURS>
//=============================================================================
private:
//<DATA>
    QList<ComRecItem*> items_;
//<FRIENDS>
};

} // namespace t2l

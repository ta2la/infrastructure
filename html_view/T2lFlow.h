//
// Copyright (C) 2018 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lFlowRow.h"

namespace T2l {

class LayoutFlow;

//=============================================================================
class Flow {
//=============================================================================
public:
//<CONSTRUCTION>
    Flow();
    virtual ~Flow() {}
//<METHOD>
    void add() { items_.append(FlowRow()); }
    FlowRow& item(int index) { return items_[index]; }
    int count() { return items_.count(); }
    FlowRow& last() { return items_[count()-1]; }
    FlowItem& lastItem() { return last().last(); }

    void loadTest(const LayoutFlow* lf);
    void load(const LayoutFlow* lf, int width);

    QList<FlowItem> itemsAll();
//=============================================================================
protected:
    QList<FlowRow> items_;


};

}

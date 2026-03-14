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
#include "T2lFlowRow.h"
#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
FlowRow::FlowRow()
{
}

//=============================================================================
void FlowRow::add(QLayoutItem* litem, int x, int y)
{
    FlowItem fi(litem, x, y);
    items_.append(fi);
}

//=============================================================================
int FlowRow::height()
{
    if (count() == 0) return 4;

    int result = 0;

    for ( int i = 0; i < count(); i++ ) {
        double hi = item(i).item()->sizeHint().height();
        double dy = item(i).y();
        hi += dy;
        if (hi > result) result = hi;
    }

    return result;
}

//=============================================================================

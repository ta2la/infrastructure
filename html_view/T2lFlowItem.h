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

#include <QLayoutItem>

namespace T2l {

//=============================================================================
class FlowItem {
//=============================================================================
public:
//<CONSTRUCTION>
    FlowItem(QLayoutItem* item, int x, int y);
    virtual ~FlowItem() {}
//<METHOD>
    QLayoutItem* item() { return item_; }
    int x() { return x_; }
    int y() { return y_; }

    void setY(int y) { y_ = y; }
    void setX(int x) { x_ = x; }
//=============================================================================
protected:
    QLayoutItem* item_;
    int x_;
    int y_;
};

}

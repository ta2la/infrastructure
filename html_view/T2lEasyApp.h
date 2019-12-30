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

#include <QString>

namespace T2l {

//=============================================================================
class EasyApp {
//=============================================================================
public:
//<CONSTRUCTION>
    EasyApp();
    virtual ~EasyApp() {}

    static EasyApp& instance() { static EasyApp i; return i; }
//<METHOD>
    QString dirRoot();
    QString dirResource () { return dirRoot() + "/resource"; }
//=============================================================================
protected:
    QString dir_;
};

}

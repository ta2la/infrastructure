//
// Copyright (C) 2016 Petr Talla. [petr.talla@gmail.com]
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

#include <vector>

class CmdAlias;

//=============================================================================
class  CmdAliasCol {
//=============================================================================
public:
//<CONSTRUCTION>
    CmdAliasCol();
    virtual ~CmdAliasCol() {;}

    static CmdAliasCol& instance();
//<ITEMS>
    int count() { return items_.size(); }
    CmdAlias* get(int index) { return items_.at(index); }
//<METHODS>
    void add(CmdAlias* alias) { items_.push_back(alias); }
    CmdAlias* get(const char* id);
//=============================================================================
protected:
//<DATA>
    std::vector<CmdAlias*> items_;
};


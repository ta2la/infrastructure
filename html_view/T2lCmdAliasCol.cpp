//
// Copyright (C) 2013 Petr Talla. [petr.talla@gmail.com]
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
#include "./T2lCmdAliasCol.h"
#include "./T2lCmdAlias.h"

//=============================================================================
CmdAliasCol::CmdAliasCol()
{
}

//=============================================================================
CmdAliasCol& CmdAliasCol::instance()
{
    static CmdAliasCol aliases;
    return aliases;
}

//=============================================================================
CmdAlias* CmdAliasCol::get(const char* id)
{
    std::string ID(id);

    for (int i = 0; i < items_.size(); i++) {
        CmdAlias* itemi = items_.at(i);
        if ( ID != itemi->id() ) continue;
        return itemi;
    }

    return NULL;
}

//=============================================================================

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

#include <string>

//=============================================================================
class  CmdAlias {
//=============================================================================
public:
//<CONSTRUCTION>
    CmdAlias(const char* id, const char* content);
    virtual ~CmdAlias() {;}
//<METHODS>
    const char* id()      const { return id_.c_str(); }
    const char* content() const { return content_.c_str(); }
    void addContentLine(const char* contentLine);
//=============================================================================
protected:
//<DATA>
    std::string id_;
    std::string content_;
};


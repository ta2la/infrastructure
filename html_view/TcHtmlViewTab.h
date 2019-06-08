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
#pragma once

#include <string>

//=============================================================================
class TcHtmlViewTab {
//=============================================================================
public:
//<CONSTRUCTION>
    TcHtmlViewTab(const char* id);

//<METHODS>
    const char* id() { return id_.c_str(); }
    void idSet(const char* id);

    const char* name() { return name_.c_str(); }
    void nameSet(const char* name);

    const char* content() { return content_.c_str(); }
    void contentSet(const char* content);
//=============================================================================
protected:
//<DATA>
    std::string id_;
    std::string name_;
    std::string content_;
};

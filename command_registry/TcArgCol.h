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

#include "./TcArg.h"
#include <list>

class TcArgVal;

//=============================================================================
class  TcArgCol : public TcArg {
// Argument list. Can serve as partial argument TcArg in this list.
//=============================================================================
public:
//<CONSTRUCTION>
    TcArgCol(const char* name = "");
    ~TcArgCol();
//<ITEMS>
    TcArgVal*   appendVal(const char* value, const char* name = "");
    TcArgVal*   appendVal(int value, const char* name = "");
    TcArgCol*   appendCol(const char* name = "");
    int         appendError(const char* value, ...);

    int         count() const {return (int)items_.size(); }
    TcArg*      at(int index);

    TcArgVal*   getVal(const char* name, int index = 0);
    const char* value(const char* name, const char* defaultArg = "", int index = 0);
    int         count(const char* name); //TODO const;

//=============================================================================
//<OVERRIDES>
    virtual void      toString(std::string& result);
    virtual TcArgCol* getAsCol() { return this; }
protected:
//<DATA>
    std::list<TcArg*> items_;
//<FRIENDS>
    friend class TcCmdTransl;
    friend class TcHtmlView; // Temporary here
};

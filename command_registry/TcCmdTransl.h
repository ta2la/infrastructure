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

#include "./TcArgCol.h"

class TcArgVal;
class parseStruct;

//=============================================================================
class  TcCmdTransl {
//=============================================================================
public:
//<CONSTRUCTION>
    TcCmdTransl(const char* script);
//<METHODS>
    static void xcall(const char* cmd, bool late);
    TcArgCol& result(void) {return result_;}
//=============================================================================
protected:
//<DATA>
    TcArgCol result_;
//<INTERNALS>
    void parseLines_(const char* script, TcArgCol* result);

    bool isEoWord_(unsigned char ch);
    bool isEoCmd_(unsigned char ch);
    void getWord_(parseStruct& ps);
    bool passSeparators_(parseStruct& ps);

    friend class TcHtmlView; //Temporary
};

#define XCALL(X) TcCmdTransl::xcall(X, true);
#define EXECUTE(X) TcCmdTransl::xcall(X, false);

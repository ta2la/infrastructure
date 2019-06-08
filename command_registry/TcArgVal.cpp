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
#include "./TcArgVal.h"
#include <cstdio>

//=============================================================================
TcArgVal::TcArgVal(const char* value, const char* name) :
    TcArg(name),
    value_(value)
{
}

//=============================================================================
TcArgVal::TcArgVal(int value, const char* name) :
    TcArg(name)
{   char buffer[100];
    sprintf(buffer, "%d", value);
    value_ = buffer;
}

//=============================================================================
const char* TcArgVal::value() const
{    return value_.c_str();
}

//=============================================================================
void TcArgVal::valueSet(const char* value)
{   value_ = value;
}

//=============================================================================
void TcArgVal::toString(std::string& result)
{   if ( name_.empty() && value_.empty() ) return;
    TcArg::toString(result);

    bool spaces = false;
    for ( unsigned i = 0; i < value_.size(); i++ )
    {   if (value_.at(i) == '"' ) spaces = true;
    }

    if ( !result.empty() && (result.at(result.size()-1) != '{') ) result.append(" ");
    if (spaces) result.append("\"");
    for ( unsigned i = 0; i < value_.size(); i++ )
    {   char ch = value_.at(i);
        if (ch == '"') result.append("\\");
        result.push_back(ch);
    }
    if (spaces) result.append("\"");
}

//=============================================================================

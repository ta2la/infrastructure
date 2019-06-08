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
#include "./TcArg.h"

using namespace std;

//=============================================================================
TcArg::TcArg(const char* name) :
    name_(name)
{
}

//=============================================================================
const char* TcArg::name() const
{   return name_.c_str();
}

//=============================================================================
void TcArg::toString(std::string& result)
{   if (name_.empty() ) return;
    if ( !result.empty() && (result.at(result.size()-1) != '{') ) result.append(" ");
    result.append("-");
    result.append(name_);
}

//=============================================================================
string TcArg::getString()
{
    string result;
    toString(result);
    return result;
}

//=============================================================================

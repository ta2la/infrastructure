//
// Copyright (C) 2013, 2023 Petr Talla. [petr.talla@gmail.com]
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
#include <assert.h>

//=============================================================================
class  TcArg {
// Specialization of hargument which has string value.
//=============================================================================
public:
    TcArg(const char* value, const char* name = "");
    TcArg(int value, const char* name = "");
//<METHODS>
    const char* name() const { return name_.c_str(); };
    const char* value() const;
    void valueSet(const char* value);
    std::string getString();
//=============================================================================
//<OVERRIDES>
    virtual void toString(std::string& result);
protected:
//<DATA>
    std::string name_;
    std::string value_;
};

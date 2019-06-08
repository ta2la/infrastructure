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

class TcArgCol;
class TcCmdEngine;
class TcCmdContext;

//=============================================================================
class  TcCmd {
// Command. Equivalent to function, but with unified set of arguments.
//=============================================================================
public:
//<TYPEDEFS>
    typedef int (*Cmd) (TcCmdContext* context, TcArgCol& args);
//<CONSTRUCTION>
    TcCmd(const char* name, Cmd cmd, const char* block, const char* help);
    ~TcCmd();
//<METHODS>
    Cmd cmd(void) { return cmd_; }

    const char* name(void) const { return name_.c_str(); }
    const char* block(void) const { return block_.c_str(); }
    const char* help(void) const { return help_.c_str(); }

    bool frontControll(void) { return frontControll_;}
    void frontControllExclude() { frontControll_ = false; }
//=============================================================================
protected:
//<DATA>
    Cmd          cmd_;
    std::string  name_;
    bool         frontControll_;

    std::string  block_;
    std::string  help_;
};

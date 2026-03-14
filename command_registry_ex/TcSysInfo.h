//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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
#include <vector>

//=============================================================================
class  TcSysInfo {
//=============================================================================
public:
//<METHODS>
    static TcSysInfo& instance();

    bool changed() { bool result = changed_; changed_ = false; return result; }

    const char* getCommandName() { return commandName_.c_str(); }
    void        setCommandName(const char* commandName) { changed_ = true; commandName_ = commandName; }

    const char* getCommandHint() { return commandHint_.c_str(); }
    void        setCommandHint(const char* commandHint) { changed_ = true; commandHint_ = commandHint; }

    int    commandsExCount() { return commandsExNames_.size(); }
    std::string commandsExName(int index) { return commandsExNames_[index]; }
    std::string commandExHint() { return commandExHint_; }

    const char* getCommandBase() const { return commandBase_.c_str(); }
    void        setCommandBase(const char* commandBase) { commandBase_ = commandBase; }
    void        exeCommandBase( const char* variable );

//=============================================================================
protected:
//<DATA>
    bool                       changed_;

    std::string                commandName_;
    std::string                commandHint_;

    std::vector< std::string > commandsExNames_;
    std::string                commandExHint_;

    std::string                commandBase_;
//<HIDDING>
    TcSysInfo();
//<FRIENDS>
    friend class TcViewSys_filter;
};

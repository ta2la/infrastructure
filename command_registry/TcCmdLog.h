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

#include "./TcCmdProcess.h"
#include "./TcCmdLogItem.h"
#include <vector>
#include <string>

//=============================================================================
class  TcCmdLog : public TcCmdProcess {
//=============================================================================
public:
//<COMMANDS>
    TcCmdLog(TcCmdEngine* engine);
//<METHODS>
    virtual int execute(TcArgCol& args, bool isFrontController);
    int count() {return items_.size(); }
    TcCmdLogItem& at(int i) { return items_[i]; }
    virtual bool cleanProtocol();
//=============================================================================
protected:
//<DATA>
    std::vector<TcCmdLogItem> items_;
};


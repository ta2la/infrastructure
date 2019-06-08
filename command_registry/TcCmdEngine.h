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

#include "./TcCmd.h"
#include "./TcCmdProcess.h"
#include <map>
#include <list>

class TcCmdEngine;
class TcArgCol;
class TcCmdEngineMsgReceiver;

//=============================================================================
class  TcCmdEngine {
//=============================================================================
public:
//<CONSTRUCTION>
    TcCmdEngine();
    static TcCmdEngine& engine();
//<NEIGHBOURS>
    void append(TcCmdProcess* process);
//<METHODS>
    TcCmd* registerCmd(const char* name, TcCmd::Cmd cmd, const char* block = "__UNDEFINED__", const char* help = "__UNDEFINED__");
    int  execute(TcArgCol* args, bool queued);
    TcCmd* find(TcArgCol& args);
    bool frontControllerActive(void) {return frontControllerActive_;}
    void executeQueue(void);
    void queuedSetOn() { queued_ = true; }

    std::list<std::string> list();
//=============================================================================
protected:
//<DATA>
    std::map<std::string, TcCmd*> items_;
    std::list<TcCmdProcess*>      processes_;
    std::list<TcArgCol*>          queue_;
    std::list<TcCmdEngineMsgReceiver*>  msgReceivers_;
    bool                          frontControllerActive_;
    bool                          queued_;
    int                           loop_;
    bool                          pendingExecution_;
//<FRIENDS>
    friend class TcCmdProcessExe;
    friend class TcCmdEngineMsgReceiver;
};

#define REGISTER_CMD TcCmdEngine::engine().registerCmd

#define CMD_FCE(FCE) static int FCE( TcCmdContext* context, TcArgCol& args )


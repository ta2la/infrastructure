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
class TcCmdEngineMsgLogger;

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
    int    execute(TcArgCol* args/*, bool queued*/);
    TcCmd* find(TcArgCol& args);
    void   refreshReceivers(void);

    std::list<std::string> list();
//=============================================================================
    TcCmdEngineMsgLogger* logger = nullptr;
protected:
//<DATA>
    std::map<std::string, TcCmd*> items_;
    std::list<TcCmdProcess*>      processes_;
    std::list<TcCmdEngineMsgReceiver*>  msgReceivers_;
    int                           loop_;
//<FRIENDS>
    friend class TcCmdProcessExe;
    friend class TcCmdEngineMsgReceiver;
};

#define REGISTER_CMD TcCmdEngine::engine().registerCmd

#define CMD_FCE(FCE) static int FCE( TcCmdContext* context, TcArgCol& args )

#define CMD_FCE_IMPLEMENT_SET_NUMBER(FCE, OBJECT, SETTER) \
static int FCE(TcCmdContext*, TcArgCol& args) \
{ \
    if ( args.count() <= 1 ) return args.appendError("you must enter the value"); \
    TcArg* arg1 = args.at(1); \
    double value = atof(arg1->value()); \
    OBJECT ().SETTER (value); \
    return 0; \
}


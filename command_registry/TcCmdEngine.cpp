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
#include "./TcCmdEngine.h"
#include "./TcArgCol.h"
#include "./TcArgVal.h"
#include "./TcCmd.h"
#include "./TcCmdProcess.h"
#include "./TcCmdProcessExe.h"
#include "./TcCmdEngineMsgReceiver.h"
#include "TcLogger.h"
#include <list>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "TcCmdEngineMsgLogger.h"

using namespace std;

//=============================================================================
TcCmdEngine::TcCmdEngine() :
    //frontControllerActive_(false),
    loop_(0)
{   append(new TcCmdProcessExe(this));
}

//=============================================================================
TcCmd* TcCmdEngine::registerCmd(const char* name, TcCmd::Cmd cmd, const char* block, const char* help)
{   TcCmd* result = new TcCmd(name, cmd, block, help);
    items_.insert(std::pair<std::string, TcCmd*>(name, result));
    return result;
}

//=============================================================================
TcCmd* TcCmdEngine::find(TcArgCol& args)
{   if (args.count() == 0) return nullptr;
    TcArg* name = args.at(0);
    if ( name == nullptr ) return nullptr;
    std::map<std::string, TcCmd*>::iterator it = items_.find(name->value());
    if ( it == items_.end() ) return nullptr;
    return it->second;
}

//=============================================================================
int TcCmdEngine::execute(TcArgCol* args)
{
    int result = 0;

    TcCmd* cmd = find(*args);

    if (cmd == nullptr) {
        T2LOG << "command " << args->at(0)->value() << "<b> not found</b>"; T2LOG.log("");
        return 0;
    }

    bool isFrontController = cmd->frontControll();

    // running processes
    std::list<TcCmdProcess*>::iterator it;
    for ( it = processes_.begin(); it != processes_.end(); it++ )
    {
        TcCmdProcess* process = *it;
        result += process->execute(*args, isFrontController);
    }

    for ( it = processes_.begin(); it != processes_.end(); it++ ) { // TODO NOT NICE
        TcCmdProcess* process = *it;
        if ( process->cleanProtocol() ) break;
    }

    TcLogger::instance().log(args->at(0)->value());

    if (logger) {
        string cmd;
        args->toString(cmd);
        logger->onCmdExecuted(cmd);
    }

    return result;
}

//=============================================================================
void TcCmdEngine::refreshReceivers(void)
{
    std::list<TcCmdEngineMsgReceiver*>::iterator it;
    int i = 0;
    for ( it = msgReceivers_.begin(); it != msgReceivers_.end(); it++ )
    {
        (*it)->onEmptyQueue();
    }
}

//=============================================================================
TcCmdEngine& TcCmdEngine::engine()
{   static TcCmdEngine* theEngine = nullptr;
    if ( theEngine == nullptr ) theEngine = new TcCmdEngine();
    return *theEngine;
}

//=============================================================================
void TcCmdEngine::append(TcCmdProcess* process)
{   processes_.push_back(process);
}

//=============================================================================
list<string> TcCmdEngine::list()
{
    std::list<string> result;
    for (map<std::string, TcCmd*>::iterator it = items_.begin(); it != items_.end(); it++) {
        string cmd = it->first;
        result.push_back(cmd);
    }

    return result;
}

//=============================================================================

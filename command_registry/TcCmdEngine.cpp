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
#include <list>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

//=============================================================================
TcCmdEngine::TcCmdEngine() :
    //frontControllerActive_(false),
    loop_(0),
    pendingExecution_(false)
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
{   if (args.count() == 0) return NULL;
    TcArgVal* name = args.at(0)->getAsVal();
    if ( name == NULL ) return NULL;
    std::map<std::string, TcCmd*>::iterator it = items_.find(name->value());
    if ( it == items_.end() ) return NULL;
    return it->second;
}

//=============================================================================
int TcCmdEngine::execute(TcArgCol* args, bool queued  )
{
    int result = 0;

    bool isFrontController = false;
    TcCmd* cmd = find(*args);
    /*if ( (cmd != NULL) && cmd->frontControll() && (frontControllerActive_ == false) )
    {   isFrontController = true;
    }
    if ( isFrontController ) frontControllerActive_ = true;*/

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

    //if ( isFrontController ) frontControllerActive_ = false;

    pendingExecution_ = true;

    return result;
}

//=============================================================================
void TcCmdEngine::executeQueue(void)
{
    if ( !pendingExecution_ && queue_.empty() ) return;

    loop_++;

    //cout << "---------------------------------- loop: " << loop_ << endl;

    while (queue_.empty() == false)
    {
        TcArgCol* args = queue_.front();
        execute(args, false);
        queue_.pop_front();
    }

    std::list<TcCmdEngineMsgReceiver*>::iterator it;
    int i = 0;
    for ( it = msgReceivers_.begin(); it != msgReceivers_.end(); it++ )
    {
        /*if ( (*it)->receiverActive() == false ) {
            cout << "skipping " << i++ << endl;
            continue;
        }*/
        (*it)->onEmptyQueue();
        //cout << "REFRESH " << i++ << endl;
    }

    pendingExecution_ = false;
}

//=============================================================================
TcCmdEngine& TcCmdEngine::engine()
{   static TcCmdEngine* theEngine = NULL;
    if ( theEngine == NULL ) theEngine = new TcCmdEngine();
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

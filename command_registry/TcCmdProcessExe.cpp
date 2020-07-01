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
#include "./TcCmdProcessExe.h"
#include "./TcArgCol.h"
#include "./TcArgVal.h"
#include "./TcCmd.h"
#include "./TcCmdEngine.h"
#include <map>

//=============================================================================
TcCmdProcessExe::TcCmdProcessExe(TcCmdEngine* engine) :
    TcCmdProcess(engine)
{
}

//=============================================================================
int TcCmdProcessExe::execute(TcArgCol& args, bool /*isFrontController*/)
{   if ( args.count() == 0 ) return args.appendError("enter at least first argument which is command name");

    TcArgVal* cmdName = args.at(0)->getAsVal();
    if ( cmdName == nullptr )
    {   return args.appendError("command name (the first argument) must be of category TcArgVal");
    }

    TcCmd* cmd = engine_->find(args);
    if ( cmd == nullptr ) return args.appendError("comand name not found");
    int result = cmd->cmd()(this->context_, args);

    return result;
}

//=============================================================================

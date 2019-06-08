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
#include "TcCmdLog.h"
#include "TcArgCol.h"
#include "Protocol.h"

//=============================================================================
TcCmdLog::TcCmdLog(TcCmdEngine* engine) :
    TcCmdProcess(engine)
{
}

//=============================================================================
int TcCmdLog::execute(TcArgCol& args, bool isFrontController)
{   if (isFrontController == false) return 0;

    std::string ARGS;
    args.toString(ARGS);
    items_.push_back(TcCmdLogItem(ARGS.c_str(), Protocol::protocolCmdGet().get(), isFrontController));

    return 0;
}

//=============================================================================
bool TcCmdLog::cleanProtocol()
{
    Protocol::protocolCmdGet().clean();
    return true;
}

//=============================================================================

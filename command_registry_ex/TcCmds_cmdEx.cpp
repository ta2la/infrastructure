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
#include "./TcCmds_cmdEx.h"
#include <TcArgCol.h>
#include <TcArgVal.h>
#include <TcCmdTransl.h>
#include <Protocol.h>
#include <QString>
#include <list>

using namespace std;
//using namespace T2l;

//=============================================================================
bool TcCmds_cmdEx::registrator_ = TcCmds_cmdEx::registerCmds_();

//=============================================================================
int TcCmds_cmdEx::cmdlist(TcCmdContext* context, TcArgCol& args)
{
    list<string> cmds = TcCmdEngine::engine().list();

    for ( list<string>::iterator it = cmds.begin(); it != cmds.end(); it++) {
        string cmdName = *it;

        TcArgCol args;
        args.appendVal(cmdName.c_str(), "");
        TcCmd* cmd = TcCmdEngine::engine().find(args);
        if (cmd == NULL) {
            Protocol::protocolCmdGet().append("%s NOT FOUND", cmdName.c_str());
        }
        else {
            Protocol::protocolCmdGet().append("%s  [%s]", cmdName.c_str(), cmd->block());
        }

        Protocol::protocolCmdGet().append("{}");
    }

    return 0;
}


//=============================================================================

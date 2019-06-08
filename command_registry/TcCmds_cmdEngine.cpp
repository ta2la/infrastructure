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
#include "TcCmds_cmdEngine.h"

// base/base
#include "TcArgCol.h"
#include "TcArgVal.h"
#include "TcCmdTransl.h"
#include "Protocol.h"

// std
#include <iostream>
#include <string>

using namespace std;

//=============================================================================
bool TcCmds_cmdEngine::registrator_ = TcCmds_cmdEngine::registerCmds_();


//=============================================================================
TcCmds_cmdEngine::TcCmds_cmdEngine()
{
}

//=============================================================================
int TcCmds_cmdEngine::voidcmd(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    return 0;
}

//=============================================================================
int TcCmds_cmdEngine::testcmd(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() == 0) {
        Protocol::protocolCmdGet().append("No command entered{}");
        return 0;
    }

    TcArgVal* val = args.at(0)->getAsVal();
    if (val) {
        Protocol::protocolCmdGet().append("command name: %s{}", val->value());
    }
    else {
        Protocol::protocolCmdGet().append("command name is not value{}");
    }

    for (int i = 1; i < args.count(); i++) {
        TcArgVal* val = args.at(i)->getAsVal();
        if (val) {
            Protocol::protocolCmdGet().append("[%d] %s: %s{}", i, val->name(), val->value());
        }
        else {
            Protocol::protocolCmdGet().append("[%d] is not a value{}", i);
        }
    }

    args.appendVal("this is result", "result");

    return 1;
}

//=============================================================================
int TcCmds_cmdEngine::cmdlist(TcCmdContext* /*context*/, TcArgCol& /*args*/)
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

        if (Protocol::useHtml()) {
            Protocol::protocolCmdGet().append("<br/>");
        }
        else {
            Protocol::protocolCmdGet().append("{}");
        }
    }

    return 0;
}

//=============================================================================
int TcCmds_cmdEngine::notfound(TcCmdContext* /*context*/, TcArgCol& args)
{
    TcArgVal* val = args.at(0)->getAsVal();
    if ( val == NULL ) {
        Protocol::protocolCmdGet().append("ERROR: command was not found, because its name is complex value{}");
        return 0;
    }
    else if ( string("notfound") == val->value() ) {
        Protocol::protocolCmdGet().append("WARNING: this command is used only internaly as a substitute of unknown commands{}"
                                          "do not call this command explicitly, it has no effect");
        return 0;
    }

    Protocol::protocolCmdGet().append("ERROR: command [%s] not registered in command system{}", val->value());
    return 0;
}

//=============================================================================

//=============================================================================

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

#include "TcCmdEngine.h"

// base/base
#include "TcArgCol.h"
#include "TcArgVal.h"
#include "TcCmdTransl.h"
#include "Protocol.h"
#include "TcLogger.h"

// std
#include <iostream>
#include <string>

using namespace std;

//=============================================================================
int TcCmds_cmdEngine::voidcmd(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    return 0;
}

//=============================================================================
int TcCmds_cmdEngine::log(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    return 0;
}

//=============================================================================
int TcCmds_cmdEngine::testcmd(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*if (args.count() == 0) {
        Protocol::protocolCmdGet().append("No command entered{}");
        return 0;
    }

    TcArgVal* val = args.at(0);
    if (val) {
        Protocol::protocolCmdGet().append("command name: %s{}", val->value());
    }
    else {
        Protocol::protocolCmdGet().append("command name is not value{}");
    }

    for (int i = 1; i < args.count(); i++) {
        TcArgVal* val = args.at(i);
        if (val) {
            Protocol::protocolCmdGet().append("[%d] %s: %s{}", i, val->name(), val->value());
        }
        else {
            Protocol::protocolCmdGet().append("[%d] is not a value{}", i);
        }
    }

    args.appendVal("this is result", "result");*/

    stringstream ss;

    for (int i = 0; i < args.count(); i++) {
        TcArg* arg = args.at(i);
        ss << "[" << i << "] ";
        ss << "name:" << arg->name() << "|";
        ss << "value:" << arg->value();
    }

    args.appendVal(ss.str().c_str(), "result");

    return 1;
}

//=============================================================================
void TcCmds_cmdEngine::_cmdlist()
{
    TcCmdEngine::engine().registerCmd("cmdlist",
    [](TcCmdContext* /*context*/, TcArgCol& args) -> int {
    std::list<std::string> cmds = TcCmdEngine::engine().list();

    bool no_tab_set = (args.get("no_tab_set") != nullptr);

    string msg;

    for ( std::list<std::string>::iterator it = cmds.begin(); it != cmds.end(); it++) {
        std::string cmdName = *it;

        if (no_tab_set && cmdName.substr(0,8)=="tab_set_") {
            continue;
        }

        TcArgCol args;
        args.appendVal(cmdName.c_str(), "");
        TcCmd* cmd = TcCmdEngine::engine().find(args);

        if (!msg.empty()) msg.append(" ");
        if (!msg.empty()) msg.append("[");
        msg.append(cmdName);
        if (!msg.empty()) msg.append("]");
    }

    args.appendMsg(msg.c_str());

    return 1;
    }, "cmdsys");

}

//=============================================================================
bool TcCmds_cmdEngine::registerCmds_()
{
    T2LOG << "REGISTER TcCmds_cmdEngine"; T2LOG.log("");

    TcCmdEngine::engine().registerCmd("voidcmd",  voidcmd,  "cmdsys");
    TcCmdEngine::engine().registerCmd("testcmd",  testcmd,  "cmdsys");
    TcCmdEngine::engine().registerCmd("log",  testcmd,  "log");
    TcCmds_cmdEngine::_cmdlist();
    return true;
}

//=============================================================================
//bool TcCmds_cmdEngine::registrator_ = TcCmds_cmdEngine::registerCmds_();

//=============================================================================

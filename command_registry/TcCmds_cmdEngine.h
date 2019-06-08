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

#include "./TcCmdEngine.h"

class TcCmdEngine;
class TcArgCol;
class TcCmd;

//=============================================================================
class TcCmds_cmdEngine {
//=============================================================================
//protected:
public:
//<CMDS>
    static int voidcmd  ( TcCmdContext* context, TcArgCol& args );
    static int testcmd  ( TcCmdContext* context, TcArgCol& args );
    static int cmdlist  ( TcCmdContext* context, TcArgCol& args );
    static int notfound ( TcCmdContext* context, TcArgCol& args );
//=============================================================================
//<REGISTRATOR>
    static bool registrator_;
    static bool registerCmds_()
    {   TcCmdEngine::engine().registerCmd("voidcmd",  voidcmd,  "cmdsys");
        TcCmdEngine::engine().registerCmd("testcmd",  testcmd,  "cmdsys");
        TcCmdEngine::engine().registerCmd("cmdlist",  cmdlist,  "cmdsys");
        TcCmdEngine::engine().registerCmd("notfound", notfound, "cmdsys");
        return true;
    }

    TcCmds_cmdEngine();
};

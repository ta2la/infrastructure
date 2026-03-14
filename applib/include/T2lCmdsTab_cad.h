//
// Copyright (C) 2013 Kinalisoft. [kinalisoft.eu]
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
// author: petr.talla@kinalisoft.eu
//   date: 2012-06-17
//purpose:
//=============================================================================
#pragma once

#include "./TcCmdEngine.h"
class TcArgCol;

#include <QString>

namespace T2l {

class CmdsTab_cad
{
//=============================================================================
public:
//<CMDS>
    CMD_FCE(tab_set_areaanalyzer);
    static int tab_set_toolbar ( TcCmdContext* context, TcArgCol& args );
    static int tab_set_toolbar1 ( TcCmdContext* context, TcArgCol& args );
    static int tab_set_acmd ( TcCmdContext* context, TcArgCol& args );
    static int tab_set_icmd ( TcCmdContext* context, TcArgCol& args );
    static int tab_set_ofiles(TcCmdContext* /*context*/, TcArgCol& /*args*/);
    static int tab_set_ofiles2(TcCmdContext* /*context*/, TcArgCol& /*args*/);
    static int tab_set_ofiles2_cmds(TcCmdContext* /*context*/, TcArgCol& /*args*/);
    static int tab_set_executed(TcCmdContext* /*context*/, TcArgCol& /*args*/);
    static int tab_set_debug(TcCmdContext* /*context*/, TcArgCol& /*args*/);

    static void setNoTentativeInterface() { noTentativeInterface_ = true; }
//=============================================================================
//<REGISTRATOR>
    static bool registerCmds_()
    {   TcCmd* cmd;

        cmd = TcCmdEngine::engine().registerCmd( "tab_set_toolbar", tab_set_toolbar,  "tab_toolbar");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_toolbar1", tab_set_toolbar1,  "tab_toolbar");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_acmd",    tab_set_acmd,     "tab_toolbar");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_icmd",    tab_set_icmd,     "tab_toolbar");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_ofiles",  tab_set_ofiles,   "tab_toolbar");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_ofiles2",  tab_set_ofiles2,   "tab_toolbar");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_ofiles2_cmds",  tab_set_ofiles2_cmds,   "tab_toolbar");
        cmd->frontControllExclude();
        /*cmd = TcCmdEngine::engine().registerCmd( "tab_set_exed",    tab_set_executed, "tab_toolbar");
        cmd->frontControllExclude();*/
        cmd = TcCmdEngine::engine().registerCmd( "tab_set_debug",    tab_set_debug, "tab_toolbar");
        cmd->frontControllExclude();

        return true;
    }
//=============================================================================
protected:
//<INTERNALS>
    CmdsTab_cad();
    static QString symbolTag(const QString& symbol);

    static bool noTentativeInterface_;
};

} //namespace T2l

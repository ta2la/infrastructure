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

#include <TcCmdEngine.h>
#include <QString>

//=============================================================================
class TcCmds_htmlView {
//=============================================================================
//protected:
public:
//<CMDS>
    static QString displayCmdLine(bool isCmd);
    static QString displayExecutedCmds();

    static int set_current_tab(TcCmdContext* context, TcArgCol& args);
    static int tab_set_commands(TcCmdContext* context, TcArgCol& args);
    static int tab_set_log(TcCmdContext* context, TcArgCol& args);
    static int tab_set_info(TcCmdContext* context, TcArgCol& args);
    static int tab_set_trace(TcCmdContext* context, TcArgCol& args);
    static int TRACE(TcCmdContext* context, TcArgCol& args);
    static int filesys_select_file(TcCmdContext* context, TcArgCol& args);
    static int filesys_select_dir(TcCmdContext* context, TcArgCol& args);
    static int html_view_tab_selector(TcCmdContext* context, TcArgCol& args);
    static int set_main_tab(TcCmdContext* context, TcArgCol& args);

//<REGISTRATOR>
    static bool registrator_;
    static bool registerCmds_()
    {   TcCmd* cmd;
        cmd = TcCmdEngine::engine().registerCmd("set_current_tab", set_current_tab, "tab_set");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd("tab_set_commands", tab_set_commands, "tab_set");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd("tab_set_log", tab_set_log, "tab_set");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd("tab_set_info", tab_set_info, "tab_set");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd("filesys_select_file", filesys_select_file, "filesys");
        cmd = TcCmdEngine::engine().registerCmd("filesys_select_dir",  filesys_select_dir,  "filesys");
        cmd = TcCmdEngine::engine().registerCmd("html_view_tab_selector",  html_view_tab_selector,  "tab_set");
        cmd->frontControllExclude();
        cmd = TcCmdEngine::engine().registerCmd("set_main_tab",  set_main_tab,  "tab_set");
        cmd->frontControllExclude();

        return true;
    }

    TcCmds_htmlView();
};

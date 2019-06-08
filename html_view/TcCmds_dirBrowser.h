//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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
class  TcCmds_dirBrowser {
//=============================================================================
public:
//<CMDS>
    static QString currentDir() { return currentDir_; }
    static void currentDirSet(const QString& dir);
//=============================================================================
    //<REGISTRATOR>
    static bool registerCmds_()
    {   TcCmd* cmd;
        cmd = TcCmdEngine::engine().registerCmd("tab_set_dir_browser", tab_set_dir_browser, "tab_set");
        cmd->frontControllExclude();

        TcCmdEngine::engine().registerCmd("show_image_ex",  show_image_ex,  "cvz_core");
        TcCmdEngine::engine().registerCmd("set_actual_dir", set_actual_dir, "cvz_core");

        return true;
    }
//<INTERNALS>
    TcCmds_dirBrowser();

    static int tab_set_dir_browser(TcCmdContext* context, TcArgCol& args);
    static int show_image_ex(TcCmdContext* context, TcArgCol& args);
    static int set_actual_dir(TcCmdContext* context, TcArgCol& args);

    static QString currentDir_;
};

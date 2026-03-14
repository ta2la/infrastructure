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
#include "./TcSysInfo.h"
#include "./TcArgCol.h"
#include "./TcCmdTransl.h"

using namespace std;

//=============================================================================
TcSysInfo::TcSysInfo() :
    changed_(true),
    commandName_("default"),
    commandHint_("enter point"),
    commandBase_("set_ann_samples_category $$$")
{
}

//=============================================================================
TcSysInfo& TcSysInfo::instance()
{
    static TcSysInfo info;
    return info;
}

//=============================================================================
void TcSysInfo::exeCommandBase( const char* variable )
{
    string cmd = commandBase_;
    if (cmd.find("$$$") == string::npos) cmd += " $$$";
    cmd.replace(cmd.find("$$$"), 3, variable);
    EXECUTE(cmd.c_str());
}

//=============================================================================

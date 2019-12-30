//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEasyViewCtrl_edit.h"
#include "TcCmdTransl.h"

#include <QString>

using namespace T2l;
using namespace std;

//=============================================================================
EasyViewCtrl_edit::EasyViewCtrl_edit( const char* cmd, QWidget* parent ) :
    QLineEdit("", parent),
    cmd_(cmd),
    entered_(false)
{
    connect(this, SIGNAL(returnPressed()), this, SLOT(onEnter()) );
}

//=============================================================================
EasyViewCtrl_edit::~EasyViewCtrl_edit()
{
}

//=============================================================================
void EasyViewCtrl_edit::onEnter()
{
    QString cmd(cmd_.c_str());
    if (cmd_.empty()) {
        cmd = text();
    }
    else {
        cmd = cmd.replace("$TEXT", text());
    }
    TcCmdTransl::xcall( cmd.toStdString().c_str(), true );
    entered_ = true;
}

//=============================================================================

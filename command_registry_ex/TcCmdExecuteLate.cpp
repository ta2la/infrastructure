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
#include "./TcCmdExecuteLate.h"
#include <TcCmdEngine.h>
#include <TcArgCol.h>
#include <TcLogger.h>
#include <assert.h>
#include <iostream>
#include <sstream>

using namespace std;

bool TcCmdExecuteLate::instanceExists_ = false;

//=============================================================================
TcCmdExecuteLate::TcCmdExecuteLate() :
    TcCmdProcess(&TcCmdEngine::engine())
{   if ( instanceExists_ ) { assert(0); return; }
    instanceExists_ = true;

    setSingleShot(true);
    start(30);
    connect(this, SIGNAL(timeout()), this, SLOT(processEvents_()) );

    TcCmdEngine::engine().append(this);
}

//=============================================================================
int TcCmdExecuteLate::execute(TcArgCol& args, bool isFrontController)
{
    if (isFrontController==false) return 0;

    stop();
    setSingleShot(true);
    start(30);

    string cmd;
    args.toString(cmd);
    TcLogger::instance() << "TIMER RESET ... " << cmd; T2LOG.log("");

    return 0;
}

//=============================================================================
void TcCmdExecuteLate::processEvents_(void)
{
    TcCmdEngine::engine().refreshReceivers();

    static int index = 0;
    stringstream ss;
    TcLogger::instance() << "<b>UPDATE ACTIVATED</b> " << index++; T2LOG.log("");
    T2LOG.log(); //extra newline
}

//=============================================================================

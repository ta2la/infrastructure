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
#include "T2lHtmlTabsRegistry.h"
//#include "TcHtmlViewTabbed.h"

#include "TcCmdEngine.h"

using namespace T2l;
using namespace std;

//=============================================================================
HtmlTabsRegistry::HtmlTabsRegistry()
{
    TcCmdEngine* engine = &TcCmdEngine::engine();
    TcCmdLog* log = new TcCmdLog(engine);
    log_ = log;
    TcCmdEngine::engine().append(log);
}

//=============================================================================
void HtmlTabsRegistry::tabAdd(const char* id, const char* name)
{
    HtmlTab* tab = tabGet_(id);
    tab->nameSet(name);
}

//=============================================================================
HtmlTab*  HtmlTabsRegistry::tabGet_(const char* id)
{   std::list<HtmlTab*>::iterator it;
    for ( it = tabs_.begin(); it != tabs_.end(); it++ )
    {   HtmlTab* tabi = *it;
        if ( strcmp(tabi->id(), id) == 0) return tabi;
    }

#ifndef NDEBUG
    std::string test(id);
#endif
    HtmlTab* result = new HtmlTab(id);
    tabs_.push_back(result);

    return result;
}

//=============================================================================

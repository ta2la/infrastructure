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
#include "TcHtmlViewTabbed.h"

using namespace T2l;
using namespace std;

//=============================================================================
HtmlTabsRegistry::HtmlTabsRegistry()
{
}

//=============================================================================
void HtmlTabsRegistry::tabAdd(const char* id, const char* name)
{   TcHtmlViewTab* tab = tabGet_(id);
    tab->nameSet(name);
    if ( tabs_.size() == 1 ) TcHtmlViewTabbed::mainView().currentTab_ = id;
}

//=============================================================================
TcHtmlViewTab*  HtmlTabsRegistry::tabGet_(const char* id)
{   std::list<TcHtmlViewTab*>::iterator it;
    for ( it = tabs_.begin(); it != tabs_.end(); it++ )
    {   TcHtmlViewTab* tabi = *it;
        if ( strcmp(tabi->id(), id) == 0) return tabi;
    }

#ifndef NDEBUG
    std::string test(id);
#endif
    TcHtmlViewTab* result = new TcHtmlViewTab(id);
    tabs_.push_back(result);

    return result;
}

//=============================================================================

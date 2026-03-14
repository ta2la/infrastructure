//
// Copyright (C) 2013, 2023 Petr Talla. [petr.talla@gmail.com]
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
#include "./TcArgCol.h"
#include "./TcArg.h"
#include "TcLogger.h"
#include <assert.h>
#include <string.h>
#include <cstdarg>
#include <cstdio>

//=============================================================================
TcArgCol::TcArgCol(/*const char* name*/)// :
//    TcArg(name)
{
}

//=============================================================================
TcArgCol::~TcArgCol()
{   std::list<TcArg*> ::iterator it;
    for ( it = items_.begin(); it != items_.end(); it++ )
    {   delete *it;
    }

}

//=============================================================================
TcArg* TcArgCol::appendVal(const char* value, const char* name)
{   TcArg* result = new TcArg(value, name);
    items_.push_back(result);
    return result;
}

//=============================================================================
TcArg* TcArgCol::appendVal(int value, const char* name)
{   char buffer[1000];
    sprintf(buffer, "%d", value);
    return appendVal(buffer, name);
}

//=============================================================================
/*TcArgCol* TcArgCol::appendCol(const char* name)
{   TcArgCol* result = new TcArgCol(name);
    items_.push_back(result);
    return result;
}*/

//=============================================================================
int TcArgCol::appendError(const char* value, ...)
{
    if ( strlen(value) > 1000 ) {
        assert(0);
        return 1;
    }
    char buffer[10000];
    va_list ap;
    va_start( ap, value );
    vsprintf( buffer, value, ap );
    va_end( ap );

    appendVal(buffer, "error");
    return 1;
}

//=============================================================================
int TcArgCol::appendMsg(const char* value, const char* name, ...)
{
    if ( strlen(value) > 1000 ) {
        assert(0);
        return 1;
    }
    char buffer[10000];
    va_list ap;
    va_start( ap, value );
    vsprintf( buffer, value, ap );
    va_end( ap );

    appendVal(buffer, name);
    return 1;
}

//=============================================================================
TcArg* TcArgCol::at(int index)
{   if ( ( index < 0 ) || ( index >= (int)items_.size() ) )
    {   assert(0);
        return nullptr;
    }

    std::list<TcArg*> ::iterator it;
    int i = 0;
    for ( it = items_.begin(); it != items_.end(); it++ )
    {   if ( i++ == index ) return *it;
    }

    assert(0);
    return nullptr;
}

//=============================================================================
TcArg* TcArgCol::get(const char* name, int index)
{    std::list<TcArg*>::iterator it;
     int i = 0;
     for ( it = items_.begin(); it != items_.end(); it++ )
     {   if ( strcmp((*it)->name(), name) != 0 ) continue;

         TcArg* val = *it;
         if ( val == nullptr ) continue;
         if ( i == index ) return val;
         i++;
     }

     return nullptr;
}

//=============================================================================
TcArg* TcArgCol::getVal(const char* name, int index)
{
    TcLogger::instance() << "Used obslolete TcArgCol::getVal method"; T2LOG.log("");
    return get(name, index);
}

//=============================================================================
const char* TcArgCol::value(const char* name, const char* defaultArg, int index)
{   if ( index < 0 ) { assert(0); return nullptr; }
    TcArg* val = TcArgCol::getVal(name, index);
    if ( val == nullptr ) return defaultArg;
    return val->value();
}

//=============================================================================
int TcArgCol::count(const char* name)
{
    std::list<TcArg*>::iterator it;
    int result = 0;
    for ( it = items_.begin(); it != items_.end(); it++ )
    {   if ( strcmp((*it)->name(), name) == 0 ) result++;
    }

    return result;
}

//=============================================================================
void TcArgCol::toString(std::string& result)
{   std::list<TcArg*>::iterator it;

    //bool toplevel = result.empty();

    //TcArg::toString(result);

    /*if (toplevel == false)
    {   result.append(" {");
    }*/

    bool first = true;

    for ( it = items_.begin(); it != items_.end(); it++ )
    {
        if (first) {
            result.push_back(' ');
            first = false;
        }
        (*it)->toString(result);

        //TcArgVal* vali = (*it);
        //if ( vali == nullptr ) continue;
        //if (vali->name()[0] != 0)
        //{   if ( result.size() != 0 ) result.push_back(' ');
        //    result.append("-");
        //    result.append(vali->name());
        //}
        //if ( result.size() != 0 ) result.push_back(' ');
        //result.append(vali->value());
    }

    //if (toplevel == false) result.append("}");
}

//=============================================================================
double TcArgCol::valueAsNumber(int index, int errorResult)
{
    if ( index<0 ) return errorResult;
    if (index >= count()) return errorResult;

    TcArg* argi = at(index);
    assert(argi!=nullptr);

    char* endPtr;
    double result = std::strtod(argi->value(), &endPtr);

    if (*endPtr != '\0') return errorResult;
    return result;
}

//=============================================================================



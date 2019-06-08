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
#include "./TcCmdTransl.h"
#include "./TcArgCol.h"
#include "./TcArgVal.h"
#include "./TcCmdEngine.h"

#include <string>

using namespace std;

//=============================================================================
TcCmdTransl::TcCmdTransl(const char* script)
{   parseLines_(script, &result_);
}

//=============================================================================
struct parseStruct
{   TcArgCol* result;

    const char* script;

    std::string line;
    int i;
    std::string word;
    bool wordNested;
    bool eocmd;
    bool order_section;
    TcArgCol* currentCol;
    TcArgVal* currentVal;

    parseStruct() :
        i(0),
        order_section(true)
    {;};

};

bool isWordNumeric(parseStruct& ps)
{
    bool dotUsed = false;

    for (int i = 0; i < ps.word.length(); i++) {
        if ( (i==0) && (ps.word[i]=='-') ) continue;
        if ( (dotUsed==false) && (ps.word[0]=='.') ) {
            dotUsed = true;
            continue;
        }

        if (isdigit(ps.word[i])) continue;
        return false;
    }

    return true;
}

//=============================================================================
void TcCmdTransl::parseLines_(const char* script, TcArgCol* result)
{   parseStruct ps;
    ps.script = script;
    ps.result = result;

    ps.currentCol = result->appendCol("");


    while ( passSeparators_(ps) == false ) ps.i++;

    while(script[ps.i] != 0)
    {   ps.eocmd = false;

        ps.word.clear();
        getWord_(ps);
        while ( passSeparators_(ps) == false ) ps.i++;

        if ( ps.wordNested )
        {   //TcArgCol* resultCol = ps.currentCol->appendCol();
            parseLines_(ps.word.c_str(), ps.currentCol);
        }
        else
        {
            if ( ps.word.size() == 0 ) return;
            if ( (ps.word[0]=='-') && (isWordNumeric(ps)==false) )
            {   ps.currentVal = ps.currentCol->appendVal("", ps.word.c_str()+1);
                ps.order_section = false;
                continue;
            }

            if ( ps.order_section )
            {   ps.currentVal = ps.currentCol->appendVal(ps.word.c_str());
            }
            else
            {   ps.currentVal->valueSet(ps.word.c_str()); //TODO
            }

            if (ps.eocmd)
            {   ps.currentCol = ps.result->appendCol("");
                ps.order_section = true;
            }
        }
    }
}

//=============================================================================
void TcCmdTransl::getWord_(parseStruct& ps)
{
    unsigned char end = 0;

    if (ps.script[ps.i] == '"') end = '"';
    if (ps.script[ps.i] == '{') end = '}';

    ps.wordNested = ( end == '}' ) ? true : false;

    if ( end != 0 ) ps.i++;

    while (true)

    {   unsigned char ch = ps.script[ps.i];

        if ( end == 0)
        {
            if ( isEoWord_(ch) == true ) break;
            if ( isEoCmd_(ch)  == true ) break;
        }
        else
        {
            if (ch == end)
            {   ps.i++;
                break;
            }
        }

        ps.word.push_back(ch);
        ps.i++;
    }
}

//=============================================================================
bool TcCmdTransl::passSeparators_(parseStruct& ps)
{   unsigned char ch = ps.script[ps.i];

    if ( ch == 0 ) return true;

    if (isEoCmd_(ch))
    {   ps.eocmd = true;
        return false;
    }

    if (isEoWord_(ch)) return false;

    return true;
}

//=============================================================================
bool TcCmdTransl::isEoWord_(unsigned char ch)
{   if ( ch == ' ' ) return true;
    if ( ch == '\t') return true;
    return false;
}

//=============================================================================
bool TcCmdTransl::isEoCmd_(unsigned char ch)
{   if ( ch == 0   ) return true;
    if ( ch == ';' ) return true;
    if ( ch == '\n') return true;
    return false;
}

//=============================================================================
void TcCmdTransl::xcall(const char* cmd, bool late)
{
    TcCmdTransl transl(cmd);

    while (transl.result_.items_.empty() == false)
    {
        TcArgCol* coli = transl.result_.items_.front()->getAsCol();
        transl.result_.items_.pop_front();
        if (coli == NULL) { assert(0); continue; }

        TcCmdEngine::engine().execute(coli, late);
    }
}

//=============================================================================

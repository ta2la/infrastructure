//
// Copyright (C) 2014 Petr Talla. [petr.talla@gmail.com]
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
#include "Protocol.h"
#include <cstdarg>
#include <cstdio>
#include <assert.h>
#include <string.h>

using namespace std;

//=============================================================================
Protocol Protocol::protocolCmd_;
time_t   Protocol::lastTime_;
bool     Protocol::useHtml_ = false;

//=============================================================================
void Protocol::appendTime(const char* value)
{
    string val(value);

    if ( val.empty() ) {
        lastTime_ = clock();
        return;
    }

    double diff = difftime( clock(), lastTime_)/CLOCKS_PER_SEC;
    char buff[10000];
    sprintf( buff, "%s [ ELAPSED: %f ]<br>", value, diff );

    protocolCmdGet().append(buff);

    lastTime_ = clock();
}

//=============================================================================
void Protocol::append(const char* value, ...)
{
    if ( strlen(value) > 150000 ) {
        assert(0);
        return;
    }

    char buffer[200000];
    va_list ap;
    va_start( ap, value );
    vsprintf( buffer, value, ap );
    va_end( ap );

    protocol_.append(buffer);
}

//=============================================================================

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
#pragma once


#include <string>
#include <time.h>

//=============================================================================
class  Protocol {
//=============================================================================
public:
    Protocol() {}
    ~Protocol() {}

    const char* get() { return protocol_.c_str(); }
    void clean() { protocol_.clear(); }
    void append(const char* value, ...);
    static void appendTime(const char* value);

    static Protocol& protocolCmdGet() { return protocolCmd_; }
    static void useHtmlSet(bool arg = true) { useHtml_ = arg; }
    static bool useHtml() { return useHtml_; }
    //=============================================================================
private:
    std::string protocol_;

    static Protocol protocolCmd_;
    static time_t   lastTime_;
    static bool     useHtml_;
};

#define PROTOCOL(MSG) Protocol::append(MSG)

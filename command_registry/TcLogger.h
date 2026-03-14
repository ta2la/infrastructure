//
// Copyright (C) 2023 Petr Talla. [petr.talla@gmail.com]
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
#include <iostream>
#include <sstream>
#include <assert.h>

class pushlog {
};

//=============================================================================
class  TcLogger {
//=============================================================================
public:
//<COMMANDS>
    TcLogger() {};
    static TcLogger& instance() { return *logger_; }
    static TcLogger* logger_;
    static void setLogger(TcLogger* logger) {
        //delete logger_;
        logger_ = logger;
    }
//<METHODS>
    virtual void log( const char* arg = "") {
        //std::cout << arg;
    };
//<OVERRIDES>
    template <typename T>
    TcLogger& operator<<(const T& value) {

        //stream_ << value; TODO_NOW
        return *this;
    }

/*    TcLogger& operator<<(const pushlog& value) {
        log("<b>br1</b><br/>");
        return *this;
    }*/
//=============================================================================
protected:
//<DATA>
    std::stringstream stream_;
};

//TcLogger& pushlog(TcLogger& log);

#define T2LOG TcLogger::instance()

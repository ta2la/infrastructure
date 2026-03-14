//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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

#include "TcRegistryObject.h"

#include <string>
#include <map>

//=============================================================================
class  TcRegistry {
//=============================================================================
public:
//<CONSTRUCTION>
    static TcRegistry& reg() { static TcRegistry r; return r; }
//<METHODS>
    TcRegistryObject* get( const std::string& id );
    bool insert( const std::string& id, TcRegistryObject& object );
    void remove( const std::string& id, bool del = false);
//=============================================================================
protected:
    TcRegistry() {}
//<DATA>
    std::map<std::string, TcRegistryObject*> items_;
};



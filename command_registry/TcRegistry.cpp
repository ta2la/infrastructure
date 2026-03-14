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
#include "TcRegistry.h"

//=============================================================================
TcRegistryObject* TcRegistry::get( const std::string& id )
{
    auto it = items_.find(id);
    if (it == items_.end()) return nullptr;
    return it->second;
}

//=============================================================================
bool TcRegistry::insert( const std::string& id, TcRegistryObject& object )
{
    auto it = items_.find(id);
    if (it != items_.end()) return false;
    items_[id] = &object;
    return true;
}

//=============================================================================
void TcRegistry::remove( const std::string& id, bool del)
{
    auto it = items_.find(id);
    if (it == items_.end()) return;

    if (del) delete it->second;
    items_.erase(it);
}

//=============================================================================

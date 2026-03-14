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
#include "./TcObject.h"
#include "./TcObjectRegistry.h"
#include <stddef.h>
#include <assert.h>

//=============================================================================
TcObject::TcObject() :
    id_(++TcObjectRegistry::registry().maxid_),
    state_(STATE_NEW)

{   TcObjectRegistry& registry = TcObjectRegistry::registry();

    registry.objects_.insert(std::pair<int, TcObject*>(id_,this));
    registry.outdated_.push_back(this);
}

//=============================================================================
TcObject::~TcObject()
{   //assert(state_ == STATE_UPTODATE); TODO
    TcObjectRegistry::registry().objects_.erase(id_);
}

//=============================================================================
void TcObject::changed_()
{   if ( state_ != STATE_UPTODATE ) return;
    TcObjectRegistry::registry().outdated_.push_back(this);
    state_ = STATE_CHANGED;
}

//=============================================================================
void TcObject::nameSet(const char* name)
{   TcObjectRegistry& registry = TcObjectRegistry::registry();
    registry.named_.insert(std::pair<std::string, TcObject*>(std::string(name),this));
}

//=============================================================================

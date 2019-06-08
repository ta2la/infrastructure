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
#include "./TcObserver.h"
#include <TcObject.h>
#include <assert.h>
#include <stddef.h>

//=============================================================================
TcObserver::TcObserver(TcObject* object)
{   objects_.push_back(object);
    object->observers_.push_back(this);
}

//=============================================================================
TcObject* TcObserver::get(int index)
{   if ( objects_.size() == 0 ) { assert(0); return NULL; }
    if ( index == 0 ) return objects_.front();

    if ( ( index < 0 ) || ( index >= (int)objects_.size() ) )
    {   assert(0);
        return NULL;
    }

    std::list<TcObject*>::iterator it = objects_.begin();
    while(true)
    {   assert(it != objects_.end());
        if ( index-- == 0 ) return *it;
        it++;
    }

    assert(0);
    return NULL;
}

//=============================================================================

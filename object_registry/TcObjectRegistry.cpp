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
#include "./TcObjectRegistry.h"
#include "./TcObject.h"
#include "./TcView.h"
#include <stddef.h>
#include <string>

//=============================================================================
TcObjectRegistry::TcObjectRegistry() :
    maxid_(0),
    lock_(0)
{
}

//=============================================================================
TcObjectRegistry& TcObjectRegistry::registry(void)
{   static TcObjectRegistry* registry = NULL;
    if ( registry == NULL )
    {   registry = new TcObjectRegistry();
    }
    return *registry;
}

//=============================================================================
TcObject* TcObjectRegistry::find(int id)
{   std::map<int,TcObject*>::iterator it = objects_.find(id);
    if ( it == objects_.end() ) return NULL;
    return it->second;
}

//=============================================================================
TcObject* TcObjectRegistry::find(const char* name)
{   std::string NAME(name);
    std::map<std::string,TcObject*>::iterator it = named_.find(NAME);
    if ( it == named_.end() ) return NULL;
    return it->second;
}

//=============================================================================
void TcObjectRegistry::lockDecrement_()
{   lock_--;
    if ( lock_ > 0) return;

    std::list<TcView*>::iterator itView;

    std::list<TcObject*>::iterator itObj;
    for ( itObj = outdated_.begin(); itObj != outdated_.end(); itObj++ )
    {   if ( (*itObj)->state_ == TcObject::STATE_NEW )
        {   for ( itView = views_.begin(); itView != views_.end(); itView++ )
            {   (*itView)->append(*itObj);
            }
        }

        (*itObj)->state_= TcObject::STATE_UPTODATE;
    }

    for ( itView = views_.begin(); itView != views_.end(); itView++ )
    {   (*itView)->refresh();
    }
}

//=============================================================================

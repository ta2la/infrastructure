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
#include "./TcView.h"
#include "./TcObjectRegistry.h"
#include "./TcObserver.h"

//=============================================================================
TcView::TcView()
{   TcObjectRegistry& r = TcObjectRegistry::registry();

    r.views_.push_back(this);

    std::map<int, TcObject*>::iterator it;
    it = r.objects_.begin();

    for (it = r.objects_.begin(); it != r.objects_.end(); it++ )
    {   append((*it).second);
    }
}

//=============================================================================
void TcView::append(TcObject* object)
{   items.push_back( new TcObserver(object) );
}

//=============================================================================

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
#pragma once

class TcObserver;
namespace T2l {
class GObjectPool;
}


#include <list>

//=============================================================================
class TcObject {
//=============================================================================
public:
//<CONSTRUCTION>
    TcObject();
    virtual ~TcObject();
//<METHODS>
    int id(void) { return id_; }
    void nameSet(const char* name);
//=============================================================================
protected:
//<ENUMS>
    enum EState { STATE_NEW, STATE_CHANGED, STATE_UPTODATE };
//<DATA>
    int     id_;
    EState state_;
    std::list<TcObserver*> observers_;
//<CHANGED>
    void changed_();
//<FRIENDS>
    friend class TcObjectRegistry;
    friend class TcObserver;
    friend class T2l::GObjectPool;
};


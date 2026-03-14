//
// Copyright (C) 2016 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lScale2.h"
#include "T2lVector2.h"

#include <QString>

namespace T2l {

//=============================================================================
class RefFilesItem {
//=============================================================================
public:
//<CONSTRUCTION>
    RefFilesItem( const QString& filePath, const Vector2F& offset = Vector2F(0, 0), double scale = 1.0,
                  bool flipX = false, bool flipY = false, double angle = 0);
    RefFilesItem( const QString& filePath, bool isThis );
//<METHODS>
    bool isThis() { return isThis_; }

    QString  filePath() { return filePath_; }
    double   scale()    { return scale_;    }
    Vector2F offset()   { return offset_;   }
    bool     flipX()    { return flipX_;    }
    bool     flipY()    { return flipY_;    }
    double   angle()    { return angle_;    }
//=============================================================================
    bool     isThis_;

    QString  filePath_;
    double   scale_;
    Vector2F offset_;
    bool     flipX_;
    bool     flipY_;
    double   angle_;
};

} //namespace T2l

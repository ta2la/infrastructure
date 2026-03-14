//
// Copyright (C) 2021 Petr Talla. [petr.talla@gmail.com]
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

// self
#include "T2lRefFilesItem.h"

#include <iostream>

using namespace std;
using namespace T2l;

//=============================================================================
RefFilesItem::RefFilesItem(const QString& filePath, const Vector2F& offset, double scale,
                           bool flipX, bool flipY, double angle ) :
    isThis_(false),
    filePath_(filePath),
    scale_(scale),
    offset_(offset),
    flipX_(flipX),
    flipY_(flipY),
    angle_(angle)
{
}

//=============================================================================
RefFilesItem::RefFilesItem(const QString& filePath, bool isThis ) :
    isThis_(isThis),
    filePath_(filePath),
    scale_(1.0),
    offset_(Vector2F(0, 0)),
    flipX_(false),
    flipY_(false),
    angle_(0.0)
{
}

//=============================================================================

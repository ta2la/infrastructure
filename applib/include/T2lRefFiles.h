//
// Copyright (C) 2020 Petr Talla. [petr.talla@gmail.com]
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

#include <T2lRefFilesItem.h>

#include <QString>
#include <QList>
#include <string>

namespace T2l {

//=============================================================================
class  RefFiles {
//=============================================================================
public:
//<CONSTRUCTION>
    RefFiles(const QString& filePath);
//<METHODS>
    int count() { return items_.count(); }
    RefFilesItem refItemGet(int index) { return items_[index]; }

    QString filePath() { return filePath_; }
    QString refFilePath();
//=============================================================================
//<DATA>
    QString             filePath_;
    QList<RefFilesItem> items_;
};

} //namespace T2l

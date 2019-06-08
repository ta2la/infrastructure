//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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

#include <QString>
#include <QStringList>

namespace T2l
{

//=============================================================================
class Filesystem {
//=============================================================================
public:
//<CONSTRUCTION>
    virtual ~Filesystem() {}
//<NEIGHBOURS>
    static Filesystem& instance();
    QString actualDir() { return actualDir_; }
    void setActualDir( const QString& dir);
    void selectsedFilesAdd( const QString& file, bool singleSelected );
    void selectedFilesClean() { selectedFiles_.clear(); }

    int selectedFilesCount() { return selectedFiles_.size(); }
    QString selectedFilesGet(int index);

    bool isSelected(const QString& file);

//<METHODS>
//=============================================================================
protected:
// <DATA>
    QString     actualDir_;
    QStringList selectedFiles_;
// <HIDDING>
    Filesystem(void);
};

} // namespace T2l

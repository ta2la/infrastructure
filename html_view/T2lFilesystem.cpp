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
//self
#include "T2lFilesystem.h"

//QT
#include <QDir>

//std
#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
Filesystem::Filesystem()
{
    QDir dir(QDir::currentPath());
    dir.cdUp();

    actualDir_ = dir.absolutePath();
    actualDir_.append("/representative");

    if ( QDir(actualDir_).exists() ) return;

    actualDir_ = QDir::currentPath();
}

//=============================================================================
Filesystem& Filesystem::instance()
{
    static Filesystem fs;
    return fs;
}

//=============================================================================
QString Filesystem::selectedFilesGet(int index)
{
    if ( index < 0 ) return "";
    if ( index >= selectedFilesCount() ) return "";

    return selectedFiles_.at(index);
}

//=============================================================================
void Filesystem::selectsedFilesAdd( const QString& file, bool singleSelected )
{
    if ( singleSelected ) selectedFilesClean();
    selectedFiles_.append(file);
}

//=============================================================================
bool Filesystem::isSelected(const QString& file)
{
    for ( int i = 0; i < selectedFiles_.count(); i++ ) {
        if ( file == selectedFiles_.at(i) ) return true;
    }

    return false;
}

void Filesystem::setActualDir( const QString& dir)
{
    actualDir_ = dir;
}

//=============================================================================

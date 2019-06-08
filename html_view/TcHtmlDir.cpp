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
#include "TcHtmlDir.h"
#include "T2lFilesystem.h"
#include <QDir>

using namespace T2l;

//=============================================================================
TcHtmlDir::TcHtmlDir(const QString& dir) :
    dir_(dir)
{
}

//=============================================================================
QString TcHtmlDir::getT2ls(const QString& wrapper)
{
    QDir dir(dir_);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.t2l" << "*.t2limgd" << "*.yaml";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dir_, list.at(i));

        QString resulti = wrapper;
        resulti.replace("$FILELINK", file.absoluteFilePath());

        QString fileName = file.absoluteFilePath();
        if (fileName.size() > 80) {
            fileName = fileName.right(80);
            fileName.prepend("...");
        }

        resulti.replace("$FILENAME", fileName);

        result += resulti;
    }

    return result;
}


//=============================================================================
QString TcHtmlDir::getImages(const QString& wrapper)
{
    QDir dir(dir_);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.JPG";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dir_, list.at(i));

        bool selected =  Filesystem::instance().isSelected(file.absoluteFilePath());

        QString resulti = wrapper;
        resulti.replace("$FILENAME", file.absoluteFilePath());

        if ( selected ) result += "<font size='230'>[</font>";
        result += resulti;
        if ( selected ) result += "<font size='230'>]</font>";
    }

    return result;
}

//=============================================================================

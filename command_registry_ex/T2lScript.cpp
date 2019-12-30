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
#include "T2lScript.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include "TcCmdTransl.h"
#include <iostream>
#include "T2lQueue.h"

using namespace T2l;
using namespace std;

//=============================================================================
bool Script::run(const char* dir, const char* id)
{
    //cout << fileName(dir, id).toStdString() << endl;

    QString filename = fileName(dir, id);
    if (filename.isEmpty()) return false;

    QFileInfo fileInfo(filename);
    if (fileInfo.exists() == false) return false;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    //cout << data.data();

    QStringList lines = QString(data).split("\n");

    for (int i = 0; i < lines.size(); i++) {
        QString line = lines.at(i);
        if (line.isEmpty()) continue;
        if ( Queue::instance()->offerText(line.toStdString().c_str()) == false ) {
            TcCmdTransl::xcall( line.toStdString().c_str(), true);
        }
    }

    //TcCmdTransl::xcall("cad_draw_line", true);
    //Queue::instance()->setConsumeText(false);

    return true;
}

//=============================================================================
QStringList Script::list(const char* dir)
{
    QStringList result;

    result.append("eniky");
    result.append("beniky");
    result.append("kiky");
    result.append("beee");

    return result;
}

//=============================================================================
QString Script::fileName(const char* dir, const char* id)
{
    QStringList path = QStandardPaths::standardLocations(QStandardPaths::HomeLocation );
    if (path.size() == 0) return "";

    QString result = path.at(0);
    result += "/.t2l/";
    result += dir;

    if (string(id) == "") return result;

    result += "/";
    result += id;
    result += ".t2lexe";

    return result;
}

//=============================================================================

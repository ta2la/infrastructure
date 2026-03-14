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

// self
#include "T2lRefFiles.h"
#include "T2lGLoadSave.h"
#include "T2lAfileRecord.h"
#include "T2lStoredAttrNUM.h"
#include "T2lAfile.h"

#include <QFileInfo>

using namespace std;
using namespace T2l;

QString RefFiles::refFilePath()
{
    QString refs = filePath_;
    refs.replace(".t2d", ".refs");
    return refs;
}

//=============================================================================
RefFiles::RefFiles(const QString& filePath) :
    filePath_(filePath)
{
    QString refs = refFilePath();

    if ( QFileInfo(refs).exists() ) {
        //GLoadSave loader(refs);
        Afile afile;
        afile.load(refs);

        bool refFile = false;

        for ( int i = 0; i < afile.recordCount(); i++) {
            AfileRecord* reci = afile.recordGet(i);

            QString reference = "";

            Vector2F           offset;
            double scale       = 1;
            bool transfFlipX   = false;
            bool transfFlipY   = false;
            double transfAngle = 0;

            for ( int ir = 0; ir < reci->attrCount(); ir++ ) {
                AfileAttr& attri = reci->attrGet(ir);

                if (string(attri.name()) == "reference") {
                    reference = attri.value();
                }
                else if (string(attri.name()) == "offset-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    double dx = attrNum.get(0);
                    double dy = attrNum.get(1);
                    offset = Vector2F(dx, dy);
                }
                else if (string(attri.name()) == "scale-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    scale = attrNum.get();
                }
                else if (string(attri.name()) == "flipx-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    if (attrNum.get() == 1) transfFlipX = true;
                }
                else if (string(attri.name()) == "flipy-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    if (attrNum.get() == 1) transfFlipY = true;
                }
                else if (string(attri.name()) == "angle-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    transfAngle = attrNum.get();
                }
            }

            if ( reference.isEmpty() ) {
                if ( refFile == false ) {
                    items_.append(RefFilesItem(filePath, true));
                    refFile = true;
                }
            }
            else {
                items_.append(RefFilesItem(reference, offset, scale,
                                           transfFlipX, transfFlipY, transfAngle));
            }
        }
    }
}

//=============================================================================

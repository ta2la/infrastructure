//
// Copyright (C) 2023 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEasyViewButtonEx.h"
#include "TcCmdTransl.h"
#include <QPainter>
#include <QStandardItem>
#include <QSize>
#include <QFile>

using namespace T2l;
using namespace std;

//=============================================================================
EasyViewButtonEx::EasyViewButtonEx( const char* cmd, QWidget* parent ) :
    QToolButton(parent),
    cmd_(cmd)
{
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(this, SIGNAL(clicked()), this, SLOT(onClick()) );
    if (QString(cmd).isEmpty()) {
        setEnabled(false);
    }
}

//=============================================================================
EasyViewButtonEx::~EasyViewButtonEx()
{
}

//=============================================================================
void EasyViewButtonEx::setImage( const QString& imagePath )
{
    int i = imagePath.indexOf("/resource");
    if ( i != -1) {
        QString resource = imagePath;
        resource.remove(0, i);
        resource.prepend(":/cad_icons");

        if (QFile::exists(resource)) {
            QPixmap pixmap(resource);
            pixmap = pixmap.scaled(150,140);
            QIcon icon(pixmap);
            setIcon(icon);
            setIconSize(QSize(150,150));
            return;
        }
    }

    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(150,140);
    QIcon icon(pixmap);
    setIcon(icon);
    setIconSize(QSize(150,150));
}

//=============================================================================
void EasyViewButtonEx::onClick()
{
    TcCmdTransl::xcall( cmd_.c_str()/*, true*/ );
}

//=============================================================================
void EasyViewButtonEx::setActiveOn()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, QColor(100, 0, 100));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

//=============================================================================

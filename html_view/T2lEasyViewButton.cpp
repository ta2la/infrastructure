//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEasyViewButton.h"
#include "TcCmdTransl.h"
#include <QPainter>

using namespace T2l;
using namespace std;

//=============================================================================
EasyViewButton::EasyViewButton( const char* cmd, QWidget* parent ) :
    QPushButton("", parent),
    cmd_(cmd)
{
    connect(this, SIGNAL(clicked()), this, SLOT(onClick()) );
}

//=============================================================================
EasyViewButton::~EasyViewButton()
{
}

//=============================================================================
void EasyViewButton::onClick()
{
    TcCmdTransl::xcall( cmd_.c_str(), true );
}

//=============================================================================
void EasyViewButton::setImage( const QString& imagePath )
{
    QPixmap pixmap(imagePath);
    QIcon icon(pixmap);
    setIcon(icon);
}

//=============================================================================
void EasyViewButton::setActiveOn()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Button, QColor(100, 0, 100));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

//=============================================================================
void EasyViewButton::setColorBack( const QColor& color, bool mark)
{
    QPixmap pixmap(50, 50);
    pixmap.fill(color);

    if (mark) {
        int x = pixmap.width()-30;
        int y = pixmap.height()-30;

        QPainter paint(&pixmap);
        QBrush brush(QColor(255, 255, 255));
        QPen pen((QColor(255, 255, 255)));
        paint.setBrush(brush);
        paint.setPen(pen);
        paint.drawEllipse(x, y, 60, 60);
    }

    QIcon icon(pixmap);
    setIcon(icon);
}

//=============================================================================

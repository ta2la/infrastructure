//
// Copyright (C) 2022 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lFlow.h"
#include <QPushButton>
#include "T2lLayoutFlow.h"
#include "T2lEasyViewSpacer.h"
#include <QRandomGenerator>

#include <QLabel>

using namespace T2l;

//=============================================================================
Flow::Flow()
{
}

//=============================================================================
void Flow::loadTest(const LayoutFlow* lf)
{
    LayoutFlow* LF = const_cast<LayoutFlow*>(lf);

    for ( int ri = 0; ri < 10; ri++ ) {
        add();
        for ( int i = 0; i < 3; i++ ) {
            if (ri*3+i >= lf->count()) return;
            last().add(LF->items_[ri*3+i], i*100, ri*50);
        }
    }
}

//=============================================================================
void Flow::load(const LayoutFlow* lf, int width)
{
    LayoutFlow* LF = const_cast<LayoutFlow*>(lf);
    add();

    int offsetX = 0;
    int relativeY = 0;
    int minX = 0;
    //if ( lf->veral() == LayoutFlow::VERAL_ORIG) offsetX = lf->offsetH();

    for (int i = 0; i < LF->count(); i++) {
        int nextX = 0;

        QLayoutItem* itemi = LF->items_[i];
        EasyViewSpacer* spacer = dynamic_cast<EasyViewSpacer*>(itemi);
        if ( spacer ) {
            switch(spacer->type()) {
            case EasyViewSpacer::SPACER_NEWLINE:
                add();
                offsetX = 0;
                continue;
            case EasyViewSpacer::SPACER_OFFSET_X:
                offsetX += spacer->value();
                continue;
            case EasyViewSpacer::SPACER_RELATIVE_Y:
                relativeY += spacer->value();
                continue;
            case EasyViewSpacer::SPACER_MINX:
                minX = spacer->value();
                continue;
            }
        }

        /*if ( lf->veral() == LayoutFlow::VERAL_ORIG) {
            QWidgetItem* witem = dynamic_cast<QWidgetItem*>(LF->items_[i]);
            if ( witem != nullptr) {
                QLabel* label = dynamic_cast<QLabel*>(witem->widget());
                if ( label != nullptr) {
                    if ( label->text() == "<hup>" ) {
                        add();
                        continue;
                    }

                    if ( label->text() == "<space>" ) {
                        if (last().count() > 0) {
                            FlowItem& li = lastItem();
                            QLayoutItem* item = li.item();
                            nextX = li.x()+item->sizeHint().width()+offsetX;
                        }
                        last().add(LF->items_[i], nextX, count()*35);
                        continue;
                    }
                }
            }
        }*/

        if (last().count() > 0) {
            FlowItem& li = lastItem();
            QLayoutItem* item = li.item();
            nextX = li.x()+item->sizeHint().width()+offsetX;

            int wi = LF->items_[i]->sizeHint().width();
            if ( nextX+wi > width ) {
                add();
                nextX = 0;
            }
        }

        if (nextX < minX) nextX = minX;

        last().add(LF->items_[i], nextX, relativeY);
        offsetX = 0;
        relativeY = 0;
        minX = 0;
    }

    static QRandomGenerator g;

    int Y = 0;

    for ( int ri = 0; ri < count(); ri++ ) {
        FlowRow& row = item(ri);
        int h = row.height();
        for ( int i = 0; i < row.count(); i++ ) {
            FlowItem& it = row.item(i);

            switch (lf->veral() ) {
            case LayoutFlow::VERAL_TOP:
            default:
                it.setY(Y+it.y());
                break;
            /*case LayoutFlow::VERAL_ORIG:
                {
                int delta = 0;

                if ( lf->veral() == LayoutFlow::VERAL_ORIG) {
                    QWidgetItem* witem = dynamic_cast<QWidgetItem*>(LF->items_[i]);
                    if ( witem != nullptr) {
                        QLabel* label = dynamic_cast<QLabel*>(witem->widget());
                        if (label != nullptr) {
                            delta = 5;
                        }
                    }
                }

                it.setY(Y+delta+it.y());
                }
                break;*/
            case LayoutFlow::VERAL_BOT:
                it.setY(Y+h-it.item()->sizeHint().height()+it.y());
                break;
            case LayoutFlow::VERAL_MID:
                it.setY(Y+(h-it.item()->sizeHint().height())/2+it.y());
                break;
            }

            //it.setX(it.x()+g.bounded(-5,5));
            //it.setY(it.y()+g.bounded(-5,5));

        }
        Y += h;
    }
}

//=============================================================================
QList<FlowItem> Flow::itemsAll()
{
    QList<FlowItem> result;

    for (int ri = 0; ri < count(); ri++) {
        FlowRow& row = item(ri);

        for (int i = 0; i < row.count(); i++) {
            result.append(row.item(i));
        }
    }

    return result;
}

//=============================================================================

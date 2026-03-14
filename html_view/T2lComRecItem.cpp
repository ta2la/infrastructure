//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lComRecItem.h"

using namespace T2l;
using namespace std;

//=============================================================================
ComRecItem::ComRecItem(const QString& value) :
    value_(value)
{
}

//=============================================================================
/*QStringList ComRecItem::commands()
{
    QStringList lines = response().split("\n");
    QStringList result;

    for (int i = 0; i < lines.count(); i++) {
        QString line = lines.at(i);
        //if (line.startsWith(CHAT_SYS.prefix()) == false) continue;
        result.append(line);
    }

    return result;
}*/

//=============================================================================

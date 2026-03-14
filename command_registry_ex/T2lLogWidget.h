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
#pragma once

#include <QString>
#include <QStringList>

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QStringListModel>

#include "TcLogger.h"

namespace T2l
{

class LogWidget : public QTextEdit, public TcLogger
{
    Q_OBJECT
public:
    LogWidget();

    static LogWidget& instance() {
        static LogWidget* i = nullptr;
        if (i == nullptr) {
            i = new LogWidget;
            i->resize(600, 800);
        }
        return *i;
    }

public:
    virtual void log( const char* arg)
    {
        stream_ << arg << "<br/>";
        std::string str = stream_.str();
        logMessage(str.c_str());
        stream_.str("");
    };

    virtual void logMessage(const QString &message)
    {
        // Append the log message to the text
        append(message);

        // Scroll to the bottom to show the latest message
        //verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    }

private:
    //QStringListModel *logModel;
};
} //namespace T2l

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
#pragma once

#ifndef FULLHTML
#elif WINDOWS
#include <QWebEngineView>
#else
#include <QWebView>
#endif

#include <QVariant>
#include <QTextBrowser>

//=============================================================================
#ifndef FULLHTML
class TcHtmlView : public QTextBrowser {
    virtual QVariant loadResource(int type, const QUrl &name);
#elif WINDOWS
class TcHtmlView : public QWebEngineView {
#else
class TcHtmlView : public QWebView {
#endif
//=============================================================================
public:
//<CONSTRUCTION>
    TcHtmlView();
    virtual ~TcHtmlView() {}
//<METHOD>
    //void contentSet();
Q_OBJECT
public slots:
    void execute(QVariant cmd);
//=============================================================================
//<QT>

    void urlHandler_(const QUrl& url);
protected:
    class HtmlPage;
//<DATA>
    bool forceChanged_;
};

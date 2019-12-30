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
#include "TcHtmlViewTabbed.h"

// infrastructure
#include "T2lHtmlTabsRegistry.h"
#include "TcHtmlViewTab.h"
#include <TcCmdLog.h>
#include <TcCmdTransl.h>
#include <TcCmdEngine.h>
#include <TcSysInfo.h>

// qt
#include <QByteArray>
#include <QFile>
#include <QTime>

#ifdef FULLHTML
#elifndef WINDOWS
#include <QWebFrame>
#endif


// std
#include <iostream>

bool TcHtmlViewTabbed::noview_ = false;

using namespace T2l;

//=============================================================================
TcHtmlViewTabbed::TcHtmlViewTabbed() :
    contentBody_(""),
    showSysinfo_(false),
    appName_("?????")
{
}

//=============================================================================
TcHtmlViewTabbed::~TcHtmlViewTabbed()
{
}

//=============================================================================
void TcHtmlViewTabbed::tabSet(const char* id, const char* content)
{
    TcHtmlViewTab* tab = HtmlTabsRegistry::instance().tabGet_(id);
    tab->contentSet(content);
    currentTab_ = id;
}

//=============================================================================
TcHtmlViewTabbed& TcHtmlViewTabbed::mainView()
{
    static TcHtmlViewTabbed* view = NULL;
    if ( view == NULL )
    {   view = new TcHtmlViewTabbed();

        TcCmdEngine* engine = &TcCmdEngine::engine();
        TcCmdLog* log = new TcCmdLog(engine);
        view->log_ = log;
        TcCmdEngine::engine().append(log);

        view->resize(830,600);
        view->move(150,50);
        if ( noview_ == false ) view->show();
    }
    return *view;
}

//=============================================================================
void TcHtmlViewTabbed::onEmptyQueue()
{
    //<STEP> refreshing the content
    std::string cmd("tab_set_");
    cmd += currentTab_;
    EXECUTE(cmd.c_str());

    QString contentBody = HtmlTabsRegistry::instance().tabGet_(currentTab_.c_str())->content();

    bool nothingChanged = true;

    if ( forceChanged_ ) {
        nothingChanged = false;
        forceChanged_  = true;
    }
    else {
        if (contentBody_ != contentBody)     nothingChanged = false;
        if (TcSysInfo::instance().changed()) nothingChanged = false;
    }

    if (nothingChanged == true) return;

    contentBody_ = contentBody;

    //<STEP> refreshing the content in html
    QByteArray content;

    content.append(
    "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>\n"
    "<html><head>\n"
    "<meta content='text/html'; charset=UTF-8'/>\n"
    "<title>TODO</title>"

    "<style type'text/css'>\n"

    "div.tab      { left:      0px; height: 30px; background: lightgray; margin: 0px; }\n"
    "div.dir_file { width:     120px; height: 90px  }"
    "div.cmdblock { float: left; margin-right: 10px; }"

    "div.tab      { border-bottom: 1px solid black; padding-bottom:50px;} "

    "div.toolbar { position: relative; overflow: hidden; margin-bottom: 10px; } "

    "div.active_command { background: #EEF; border: 1px solid #999; padding: 10px}"
    "div.active_command { margin-bottom: 10px; }"

    "div.tab,"
    "div.dir_part1,"
    "div.dir_file, "
    "div.toolbar, "
    "div.active_command, "
    "a.content "
        "{ font-family: Arial, Helvetica, sans-serif;"
        "  text-color:  black;"
        "  font-size:   12px; }"

    "div.tab"
        "{ "
        "  font-size:    14px;"
        "  font-weight:  bolder;"
        "}"

    "div.dir_file { float:     left; clear: right; }"
    "div.dir_file { border:    0px solid black }"
    "div.dir_file { margin:    10px; margin-right: 30px;} "

    "div.dir_file{ background-color: lightgray; text-align: center; vertical-align: middle;  } "
    "div.dir_file{ word-break: break-all; } "
    "div.dir_file{ display:    block; vertical-align: middle; text-baxkground: yellow;} "

    "div.dir_part1{ width:95%;border:0px solid black; margin: 10px; margin-right: 40px; }"

    "div.content, div.separator {position: absolute; top: 50px; bottom: 0px;}\n"
    "div.content, div.separator, dhttp://neviditelnypes.lidovky.cz/iv.input, form, div#active, a.content:hover {background: #EEF;}\n"

    "div.content   { left: 10px; right: 10px;}\n"
    "a.content:link, a.content:visited, a.content:hover, a.content:active {text-decoration: none; color: #000;}"

    "div.input {height: 65px; bottom: 0px; left: 0px; right: 0px;}\n"
    "form { left: 10px; right: 2px; top: 2px; bottom: 2px;};\n"
    "form, input, div.input { background: #F00;}\n"

    "body { position: absolute; left: -8px; top: -8px; right: -8px; bottom: -8px; }"
    "div#active {background-color: #FFF; height: 30px; }"

    "div.APP_NAME { float: left; } "

    "div.contenti, div#active  { float:left; margin-left: 6px; margin-right: 6px; padding-left: 6px; padding-right: 12px; padding-top: 4px; padding-bottom: 4px;}"
    "div#active, div.contenti, a.content {text-color: #00F; margin-top: 5px; }"

    "div.APP_NAME { float: right; margin-top: 5px; margin-right: 50px; padding-left: 10px; padding-right: 10px; }"
    "div.APP_NAME { background: #DDA; color: #886 }"

    "div.gallery { margin: 5px; border: 1px solid #ccc; float: left; width: 150px; height 130px; }"
    "div.gallery:hover { border: 1px solid #777; }"
    "div.gallery img { width: 150px; height: 100px; }"
    "div.desc { padding: 15px; text-align: center; }"
    );

    content.append(styles_);

    content.append(
    "</style>\n"

    "</head>\n"

    "<body>"
    );

    content.append("<div class='tab' style='background-color:'blue'; padding-bottom:50px;'>");
        std::list<TcHtmlViewTab*>::iterator it;
        for ( it = HtmlTabsRegistry::instance().tabs_.begin(); it != HtmlTabsRegistry::instance().tabs_.end(); it++ )
        {   TcHtmlViewTab* tabi = *it;

            if ( currentTab_ == tabi->id() )
            {
#ifdef FULLHTML
                content.append("<div id='active'>");
#endif
                    content.append("<b>");
                    content.append(tabi->name());
                    content.append("</b>");
#ifdef FULLHTML
                content.append("</div>");
#endif

            }
            else
            {
#ifdef FULLHTML
                content.append("<div class='contenti'>");
#endif
                    content.append("<a class='content' href='tcview://#set_current_tab ");
                    content.append(tabi->id());
                    content.append("'>");
                    content.append(tabi->name());
                    content.append("</a>");
#ifdef FULLHTML
                content.append("</div>\n");
#endif
            }

#ifndef FULLHTML
            content.append("&nbsp;&nbsp;&nbsp;");
#endif
        }
#ifndef FULLHTML
        for (int i = 0; i < 50; i++) content.append("&nbsp;");
#else
        content.append("<div class='APP_NAME'>");
#endif
            content.append(appName_);
#ifdef FULLHTML
        content.append("</div>");
#else
        //content.append("<hr/>");
#endif
    content.append("</div>");

    content.append("<div class='content'>");
        content.append(contentBody);
    content.append("</div>");

    content.append("</body></html>");

#ifndef FULLHTML
    setText(content);
#elif WINDOWS
    setHtml(content, QUrl("C:/HOME"));
#else
    setContent(content, "", QUrl("/home"));
#endif

#ifndef NDEBUG
    QFile log("C:\\TEMP\\t2l\\log.html");
    log.open(QIODevice::Truncate | QIODevice::WriteOnly);
    log.write(content.data(), content.count());
    log.flush();
    log.close();
#endif

/*#ifndef FULLHTML
#elifndef WINDOWS
    page()->mainFrame()->addToJavaScriptWindowObject("viewxx", this);
#endif*/
}

//=============================================================================

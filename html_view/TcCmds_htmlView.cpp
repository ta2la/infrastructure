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
#include "TcCmds_htmlView.h"
#include "T2lEasyViewHtml.h"
#include "T2lEasyView.h"

#include "T2lFilesystem.h"
#include "TcHtmlViewTabbed.h"
#include "TcCmdLog.h"
#include "TcArgCol.h"
#include "TcArgVal.h"

#include <QDir>
#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
bool TcCmds_htmlView::registrator_ = TcCmds_htmlView::registerCmds_();

//=============================================================================
TcCmds_htmlView::TcCmds_htmlView()
{
}

//=============================================================================
int TcCmds_htmlView::set_current_tab(TcCmdContext* /*context*/, TcArgCol& args)
{   if (args.count() < 1) return args.appendError("tab name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();
    if (val == NULL) return args.appendError("tab name must be value");
    TcHtmlViewTabbed::mainView().tabSetCurrent(val->value());
    return 0;
}

//=============================================================================
QString TcCmds_htmlView::displayCmdLine(bool isCmd)
{
    QString result;

    result.append(

    "<script type='text/javascript'>"


    "function cmd_request() {"
    "    var cmd = document['cmd_form'].elements['cmd'].value;"
    "    window.viewxx.execute(cmd);"
    "    document['cmd_form'].elements['cmd'].value = '';"
    "}"

    "</script>"

    "<div class='input'>"
    "    <form  name='cmd_form' action='' method='get'>"
    );
/*    if (isCmd) {
        result.append("cmd: ");
    }
    else {
        result.append("text: ");
    }
    result.append(
#ifdef WINDOWS
    "        <input size='70'  type='ttab_set_commandsext' name='cmd' onKeyPress='{if (event.keyCode==13)cmd_request()}'>"
#else
    "        <input size='70'  type='ttab_set_commandsext' name='cmd' onKeyPress='{if (event.keyCode==13)cmd_request()}'>"
#endif
    "    </form>"
         "<a href='tcview:://#cmdlist'>available commands</a><br><hr>"
    "</div>"
    );*/

    //result.append("<br><hr>");
    result.append(displayExecutedCmds());

    return result;
}

//=============================================================================
QString TcCmds_htmlView::displayExecutedCmds()
{
    QString result;

    result.append("<div>");

    TcCmdLog* log = TcHtmlViewTabbed::mainView().log_;

    for ( long i = log->count()-1; ( (i > log->count()-9) && (i >=0) ) ; i-- )
    {
        result.append("<b>");
        result.append(QString("[%0] ").arg(i));
        result.append(log->at(i).cmdRecord());
        result.append("</b><br>");

        if (i > log->count()-3) {
            //const char* protocol = log->at(i).cmdProtocol();
            result.append(log->at(i).cmdProtocol());
            result.append("<br>");
        }
    }

    result.append("</div>");

    return result;
}

//=============================================================================
int TcCmds_htmlView::tab_set_commands(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    TcHtmlViewTabbed::mainView().tabSet("commands", displayCmdLine(false).toLatin1().data());
    return 0;
}

//=============================================================================
int TcCmds_htmlView::tab_set_log(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{   QString LOG;
    TcCmdLog* log = TcHtmlViewTabbed::mainView().log_;

    for ( long i = 0; i < log->count(); i++ )
    {   if ( log->at(i).isFrontController() == false ) continue;
        LOG.append(QString("[%0]").arg(i));
        LOG.append(log->at(i).cmdRecord());
        LOG.append("<br>");
    }

    TcHtmlViewTabbed::mainView().tabSet("log", LOG.toLatin1().data());

    return 0;
}

//=============================================================================
int TcCmds_htmlView::tab_set_info(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{   QString result;

    result.append("Current path: ");
    result.append(QDir::currentPath());
    result.append("<br>");

    TcHtmlViewTabbed::mainView().tabSet("info", result.toLatin1().data());

    return 0;
}

//=============================================================================
int TcCmds_htmlView::filesys_select_file(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 1) return args.appendError("file name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();

    Filesystem::instance().selectsedFilesAdd(val->value(), true);

    return 1;
}

//=============================================================================
int TcCmds_htmlView::filesys_select_dir(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 1) return args.appendError("directory name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();

    Filesystem::instance().setActualDir(val->value());

    return 1;
}

//=============================================================================
int TcCmds_htmlView::html_view_tab_selector(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 1) return args.appendError("directory name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();

    EasyViewHtml::activeSingleSet(val->value());

    return 1;
}

//=============================================================================
int TcCmds_htmlView::set_main_tab(TcCmdContext* context, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("tab id must be entered");
    TcArgVal* val = args.at(1)->getAsVal();

    EasyView::activeSet(val->value());

    return 1;
}

//=============================================================================


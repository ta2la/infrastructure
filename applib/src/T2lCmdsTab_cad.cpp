//
// Copyright (C) 2013 Kinalisoft. [kinalisoft.eu]
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
// author: petr.talla@kinalisoft.eu
//   date: 2012-06-17
//purpose:
//=============================================================================
//self
#include "T2lCmdsTab_cad.h"

//cad
#include "T2lActiveFile.h"
#include "T2lStoredFileNames.h"
#include "T2lCadSettings.h"
#include "T2lGFile.h"
#include "T2lGFileCol.h"

// infrastructure
#include "TcArgCol.h"
#include "TcArgVal.h"
#include "TcCmdLog.h"

// hg
#include "T2lWidgetInteract.h"
#include "T2lFilter.h"
#include "T2lCmdQueue.h"
#include "T2lCmd.h"

#ifndef Q_OS_WASM
//#include "T2lCmds_htmlView.h"
#include "T2lHtmlTabsRegistry.h"
//#include "TcHtmlViewTabbed.h"
//#include "TcHtmlDir.h"
#include "T2lHtmlTab.h"
//#include "T2lCadExeSettings.h"
#include "T2lEasyViewTml.h"
#include "T2lEasyApp.h"
#endif


#include <QString>
#include <QDir>
#include <QCoreApplication>
#include <QTextStream>

using namespace T2l;

//=============================================================================
bool CmdsTab_cad::noTentativeInterface_ = false;

//=============================================================================
CmdsTab_cad::CmdsTab_cad()
{
}

//=============================================================================
QString CmdsTab_cad::symbolTag(const QString& symbol)
{
    QString result;
    result += "<img width='30' height='30' src='qrc:/cad_icons/resource/icons";
    result += symbol;
    result += ".png";
    result += "'/>";

    return result;
}

//=============================================================================
int CmdsTab_cad::tab_set_ofiles(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    if ( GFileCol::instance().count() == 0 ) {
        result.append("<br>No files opened<br>");
    }
    else {
        result.append("<div class='toolbar'>");
        result.append("opened files:<br> ");

    result.append("<table>");

    for ( int i = 0; i < GFileCol::instance().count(); i++ ) {
        result.append("<tr>");
        result.append("<td style='text-align: left;'>");

        GFile* file = GFileCol::instance().get(i);
        bool active = false;

        char index[100];
        sprintf(index, " %d ", i);

        if (file == ActiveFile::activeGet()->file()) active = true;

        if (active == false) {
            result.append("<a href='tcview:://#cmd_cad_file_activate ");
            result.append(file->filePath());
            result.append("'>[a]</a>");
        }

        if (active==false || GFileCol::instance().count()==1) {
            result.append("<a href='tcview:://#cmd_cad_file_close ");
            result.append(file->filePath());
            result.append("'>[close]</a>");
        }

        if (active) {
            result.append(" <b>");
        }
        else {
            result += "&nbsp;";
        }
        result.append(file->fileName());
        char count[100];
        if (active) result.append("</b>");

        if ( file->changeRegistry()>0 ) {
            sprintf(count, "[&nbsp;%d changes] ", file->changeRegistry());
            result.append(count);
        }

        result.append("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
        result.append("</th>");
        result.append("<td style='text-align: left;'>");
        result += "&nbsp;";
        if (i != 0) {
            result.append("<a href='tcview:://#cad_file_shift");
            result.append(index);
            result.append("up");
            result.append("'>[up]</a>");
        }

        if (i != GFileCol::instance().count()-1) {
            result.append("<a href='tcview:://#cad_file_shift");
            result.append(index);
            result.append("down");
            result.append("'>[down]</a>");
        }

        result.append("</th>");
        result.append("<td style='text-align: left;'>");
        result.append("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;offset: ");
        result.append(QString::number(file->getOffset().x()));
        result.append(",");
        result.append(QString::number(file->getOffset().y()));

        result.append(" scale: ");
        result.append(QString::number(file->getScale()));


        //result.append("<br>");
        result.append("</th>");
        result.append("</tr>");
    }
    result.append("</table>");
    result.append("</div><br/><br/>");

    result += "<a href='tcview:://#cad_repaint'>[REPAINT]</a>&nbsp;&nbsp;";

    result += "<a href='tcview:://#cad_set_nonactive_display'>";
    if ( CAD_SETTINGS.nonActiveDisplayGray() ) {
        result += "[GRAY referance drawing];";
    }
    else {
        result += "[COLOR reference drawing];";
    }
    result += "</a>";
    result += "<br><br>";


    result.append("<a href='tcview:://#cad_save_reference'>[save references]</a>");
    }

    assert(0);
    /*HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("ofiles");
    tab->contentSetEx(result.toStdString());*/
    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_ofiles2(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
#ifdef Q_OS_WASM
    assert(0);
#else
    QString result;
    QTextStream str(&result);

    if ( GFileCol::instance().count() == 0 ) {
        str << "TEXT:No files opened.;;";
        str << "NEWLINE:;;";
    }
    else {

    for ( int i = 0; i < GFileCol::instance().count(); i++ ) {
        GFile* file = GFileCol::instance().get(i);

        bool active = false;
        if (file == ActiveFile::activeGet()->file()) active = true;

        //FILE-ICON
        QString ip = EasyApp::instance().iconPath("icons/file");

        //str << "type:control;control:spacer;spacer:relative_y;value:-12;;";
        //str << "TEXT:<img src='" << ip << "' height='20'/>;;";
        //str << "SPACE:;;";

        QString cp = EasyApp::instance().iconPath("controls/close");
        QString ap = EasyApp::instance().iconPath("controls/active");
        if (active==false || GFileCol::instance().count()==1) {
            str << "BUTTON:cmd_cad_file_close " << file->filePath()
                << ";icon:" << cp << ";iconsize:16;;";
        }
        if (active || GFileCol::instance().count()==1) {
            str << "BUTTON:cmd_cad_file_close " << file->filePath()
                << ";icon:" << ap << ";iconsize:20;;";
            str << "type:control;control:spacer;spacer:relative_y;value:-5;;";
            str << "TEXT:<img src='" << ap << "' height='24'/>;;";
        }

        //FILENAME
        if (!active) str << "SPACE:;;";
        str << "TEXT:";
        if (active) str << "<b>";
        str << file->fileName();
        if (active) {
            str << "</b>";
        }
        else {
            str << ";cmd:cmd_cad_file_activate \"" << file->filePath() << "\"";
        }
        str << ";;";

        //UP-DOWN
        str << "TAB:160;;";
        if (i != 0) {
            //str << "type:control;control:spacer;spacer:relative_y;value:4;;";
            str << "BUTTON:" << "cad_file_shift " << i << " up;icon:"
                << EasyApp::instance().iconPath("controls/arr_up")
                << ";iconsize:8;;";
        }

        if (i != GFileCol::instance().count()-1) {
            //str << "type:control;control:spacer;spacer:relative_y;value:4;;";
            str << "BUTTON:" << "cad_file_shift " << i << " down;icon:"
                << EasyApp::instance().iconPath("controls/arr_down")
                << ";iconsize:8;;";
        }

        //TRANSFORMATION
        str << "TAB:210;;";
        str << "TEXT:offset: " << file->getOffset().x() << "," << file->getOffset().y()
            << " scale: " << file->getScale() << ";;";

        str << "NEWLINE:;;";
    }

    }

    str.flush();

    EasyViewTml::substituteEx(result);

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("ofiles2");
    tab->contentSetEx(result.toStdString());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_ofiles2_cmds(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
#ifdef Q_OS_WASM
    assert(0);
#else

    QString result;
    QTextStream str(&result);

    if ( GFileCol::instance().count() > 0 ) {

    //BOTTOM
    str << "BUTTON:cad_repaint;text:Repaint;;";
    str << "SPACE:;;";
    str << "BUTTON:cad_set_nonactive_display;width:200;text:";
    if ( CAD_SETTINGS.nonActiveDisplayGray() ) {
        str << "GRAY ref. drawings;;";
    }
    else {
        str << "COLOR ref. drawings;;";
    }
    str << "NEWLINE:;;";

    str << "BUTTON:cad_save_reference;text:Save references;;";

    str.flush();

    //EasyViewTml::substituteEx(result);

    //HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("ofiles2_cmds");
    //tab->contentSet(result.toLatin1().data());

    }

    str.flush();

    EasyViewTml::substituteEx(result);

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("ofiles2_cmds");
    tab->contentSetEx(result.toStdString());
#endif

    return 0;
}


//=============================================================================
//int CmdsTab_cad::tab_set_executed(TcCmdContext* /*context*/, TcArgCol& /*args*/)
/*{
    QString result;

    result.append("<div class='toolbar'>");
    result.append(Cmds_htmlView::displayCmdLine(!Queue::instance()->consumeText()));
    result.append("</div>");

    //APTA2 TcHtmlViewTabbed::mainView().tabSet("exed", result.toLatin1().data());
    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("exed");
    tab->contentSetEx(result.toStdString());

    return 0;
}*/

//=============================================================================
QString button(const QString& symbol, const QString& cmd = "")
{
    QString acmd = cmd;
    if (acmd.isEmpty()) acmd = symbol;

    QString result = "TC;CB;cmd: ";
    result += acmd + ";icon: ";
    result += "qrc:/cad_icons/resource/icons/";
    result += symbol;
    result += ".png;;";

    return result;
}

//=============================================================================
int CmdsTab_cad::tab_set_acmd(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
#ifdef Q_OS_WASM
    assert(0);
#else
    QString result;
    if ( ActiveFile::activeGet() == nullptr ) {
        result += "TC;CT;text: <b>No file opened.</b>";
    }
    else {
        result += "TC;CT;text: <b>";
        result.append(CmdQueue::queue().activeCommand()->name());
        result.append("</b>: ");
        result.append(CmdQueue::queue().activeCommand()->hint());
        result += ";;";
    }

    //===================================================
    result = result.replace("TC", "type: control");
    result = result.replace("CT", "control: text");
    result = result.replace("CB", "control: button");
    result = result.replace(";", "\n");

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("acmd");
    tab->contentSet(result.toStdString().c_str());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_icmd(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
#ifdef Q_OS_WASM
    assert(0);
#else
    QString result = "";

    if ( ActiveFile::activeGet() != nullptr ) {
        result = CmdQueue::queue().activeCommand()->dialogTml();
        EasyViewTml::substituteEx(result);
    }

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("icmd");
    tab->contentSet(result.toStdString().c_str());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_toolbar1(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    //<STEP> ortho
    if ( CAD_SETTINGS.ortho() ) {
        result += "TC;CT;text: ortho:;;";
    }
    else {
        result += "TC;CT;text: not ortho:;;";
    }

    result += "TC;CB;icon: ";
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    result += "qrc:/cad_icons/resource/icons/sett_ortho";
    if ( !CAD_SETTINGS.ortho() ) result += "_not";
    result += ".png;";
    result += "cmd: cad_set_ortho;;";

    // <STEP> file
    ActiveFile* activeFile = ActiveFile::activeGet();
    if ( activeFile != nullptr ) {
        result += "TC;CT;text: <space>;;";

        result += "TC;CT;text: file:;;";
        bool canBeSaved = true;
        if (activeFile->file()->getScale() != 1.0)      canBeSaved = false;
        if (activeFile->file()->getOffset().x() != 0.0) canBeSaved = false;
        if (activeFile->file()->getOffset().y() != 0.0) canBeSaved = false;

        if (canBeSaved) {
            result += button("cmd_cad_save", "cmd_cad_save");
        }
        else {
            result += "TC;CT;text: <b>transformed</b>;;";
        }

        QString count;
        QTextStream countStream(&count);
        countStream << activeFile->file()->changeRegistry() << " changes";
        result += "TC;CT;text: ";
        result += count + ";;";
    }
    else {
        //result += "TC;CT;text: <b>not loaded</b>;;";
    }

    // new view -----------------------------
    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: <space><space><space><space>new view:;;";
    result += button("view_new");
//result += button("view_new_ex");
//result += button("view_new_simple");

    // command -----------------------------
    result += "NEWLINE:;;";
    result += "TC;CT;text: <space>;;";
    result +=
    "TC;CT;text: command:;;"
    //"TC;CT;text: <space>;;"
    "TC;control: edit;"
    "width: 350;;"
    ";;";

    if (noTentativeInterface_ == false) {

        result += "NEWLINE:;;";
        int grid = static_cast<int>(CAD_SETTINGS.grid());
        /*if ( grid == -1 ) {
            result += "TEXT: true snap - ;;";
        }
        else if (grid < -1 ) {
            result += "TEXT: true snap ofsetted - ;;";
        }
        else if (grid == 0 ) {
            result += "TEXT: virtual snap - ;;";
        }
        else {
            result += "TEXT: grid ";
            result += QString::number(CAD_SETTINGS.grid());
            result += " - ;;";
        }
        if (grid != 0)   result += "TEXT: [virtual snap];cmd: cad_set_grid 0;;";
        if (grid != -1)  result += "TEXT: [true snap];cmd: cad_set_grid -1;;";
        if (grid >= -1)  result += "TEXT: [true snap ofsetted];cmd: cad_set_grid -2;;";
        if (grid != 5)   result += "TEXT: [5];cmd: cad_set_grid 5;;";
        if (grid != 10)  result += "TEXT: [10];cmd: cad_set_grid 10;;";
        if (grid != 20)  result += "TEXT: [20];cmd: cad_set_grid 20;;";
        if (grid != 30)  result += "TEXT: [50];cmd: cad_set_grid 50;;";

        result += "TEXT: ... ";
        result += QString::number(CAD_SETTINGS.grid());
        result += ";;";*/
/*
result += "SPACE:;;SPACE:;;SPACE:;;";
if (grid == -1) {
    result += "TEXT: <b>[glue snap]</b>;;";
}
else {
    result += "TEXT: [glue snap];cmd: cad_set_grid -1;;";
}
if (grid < -1) {
    result += "TEXT: <b>[ofsetted]</b>;;";
}
else {
    result += "TEXT: [ofsetted];cmd: cad_set_grid -2;;";
}
result += "SPACE:;;";
if (grid == 0) {
    result += "TEXT: <b>[basic snap]</b>;;";
}
else {
    result += "TEXT: [basic snap];cmd: cad_set_grid 0;;";
}
result += "SPACE:;;TEXT:grid: ;;";
if (grid == 5) {
    result += "TEXT: <b>[5]</b>;;";
}
else {
    result += "TEXT: [5];cmd: cad_set_grid 5;;";
}
if (grid == 10) {
    result += "TEXT: <b>[10]</b>;;";
}
else {
    result += "TEXT: [10];cmd: cad_set_grid 10;;";
}
if (grid == 50) {
    result += "TEXT: <b>[50]</b>;;";
}
else {
    result += "TEXT: [50];cmd: cad_set_grid 50;;";
}*/
    }

    //===================================================
#ifdef Q_OS_WASM
    assert(0);
#else
    EasyViewTml::substituteEx(result);

    result = result.replace("TC", "type: control");
    result = result.replace("CT", "control: text");
    result = result.replace("CB", "control: button");
    result = result.replace(";", "\n");

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("toolbar1");
    tab->contentSet(result.toStdString().c_str());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_toolbar(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    result += "TC;CT;text: select:;;";
    result += button( "edit_select",      "cmd_object_select" );
    result += "TC;CT;text: <space>;;";

    result += "TC;CT;text: create:;;";
    result += button("create_line",   "cad_draw_line_pro" );
    //result += button("create_area",   "cmd_cad_draw_area" );
    //result += button("create_symbol", "cmd_object_enter");
    //result += button("create_image",  "cmd_cad_draw_image");
    //result += button("create_text",   "cmd_cad_draw_text");
    //result += button("create_dimm",   "cmd_cad_draw_dimm");
    result += button("cad_draw_cube1",   "cad_draw_cube1" );

    //result += "TC;CT;text: 3d:;;";
    //result += button("cad_draw_line3",   "cad_draw_line3" );



    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: copy:;;";
    result += button("copy",              "cmd_object_copy");
    result += button("copy_parallel",     "cmd_object_mocopy_parallel");

    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: edit:;;";
    result += button( "edit_move",        "cmd_object_move"          );
    result += button( "edit_move_points", "cmd_object_movepoints"    );
    result += button( "edit_trim",        "cmd_object_trim"          );
    result += button( "edit_trimto",      "cmd_object_trimtoother"   );
    result += button( "edit_split",       "cmd_object_split"   );
    //result += button( "transform_image",  "cmd_cad_transform_image"   );
    //result += button( "image_properties", "cmd_cad_image_properties"   );
    result += button( "edit_symbology",   "cmd_object_set_symbology" );
    //result += button( "change_text",      "change_text" );
    result += button( "delete",           "cmd_object_delete"        );
    result += button( "delete_cube1",           "cad_cube1_delete"        );

    //result += "TC;CT;text: <space>;;";
    //result += "TC;CT;text: info:;;";
    //result += button("info_measure",     "cmd_cad_measure");
    //result += button("cad_follow_link",  "cad_follow_link");

    result += "TC;CT;text: <space>;;";
    result += "TC;CT;text: view:;;";
    result += button("view_pan",         "cmd_view_pan");
    result += button("view_zoomrect",    "cmd_view_zoomrect");
    result += button("view_fit",         "cmd_cad_view_fit");
    result += button("cad_navigate3",   "cad_navigate3" );

    //result += "TC;CT;text: <space>;;";
    //result += "TC;CT;text: completion:;;";
    //result += button("cmd_cad_active_file_move", "cmd_cad_active_file_move");
    //result += button("cad_draw_papper", "cad_draw_papper");
    //result += button("cad_print", "cad_print");

    //===================================================
    result = result.replace("TC", "type: control");
    result = result.replace("CT", "control: text");
    result = result.replace("CB", "control: button");
    result = result.replace(";", "\n");

#ifdef Q_OS_WASM
    assert(0);
#else
    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("toolbar");
    tab->contentSet(result.toStdString().c_str());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_cad::tab_set_debug(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    static int i = 0;
    result += QString("TEXT:Refresh number: ") + QString::number(i++) + ";;";

    result += "BUTTON:cad_draw_line3;text: 3d drawing;;";
    result += "NEWLINE:;;";

    result += "BUTTON: cmd_cad_draw_refbox_develop;text: draw refbox;;";
    result += "BUTTON:cmd_cad_draw_refline;text: draw refline;;";
    result += "NEWLINE:;;";

    int grid = static_cast<int>(CAD_SETTINGS.grid());
    if ( grid == -1 ) {
        result += "TEXT: true snap - ;;";
    }
    else if (grid < -1 ) {
        result += "TEXT: true snap ofsetted - ;;";
    }
    else if (grid == 0 ) {
        result += "TEXT: virtual snap - ;;";
    }
    else {
        result += "TEXT: grid ";
        result += QString::number(CAD_SETTINGS.grid());
        result += " - ;;";
    }
    if (grid != 0)   result += "TEXT: [virtual snap];cmd: cad_set_grid 0;;";
    if (grid != -1)  result += "TEXT: [true snap];cmd: cad_set_grid -1;;";
    if (grid >= -1)  result += "TEXT: [true snap ofsetted];cmd: cad_set_grid -2;;";
    if (grid != 5)   result += "TEXT: [5];cmd: cad_set_grid 5;;";
    if (grid != 10)  result += "TEXT: [10];cmd: cad_set_grid 10;;";
    if (grid != 20)  result += "TEXT: [20];cmd: cad_set_grid 20;;";
    if (grid != 30)  result += "TEXT: [50];cmd: cad_set_grid 50;;";

    result += "TEXT: ... ";
    result += QString::number(CAD_SETTINGS.grid());
    result += ";;";
    result += "NEWLINE:;;";

    /*if (CAD_SETTINGS.text2points()) {
        result += "TEXT: text is 2 points entry;cmd: cad_set_text_2points;;";
    }
    else {
        result += "TEXT: text is 1 point entry;cmd: cad_set_text_2points;;";
    }
    result += "NEWLINE:;;";*/

    result += "BUTTON:cad_print_test;text:test PRINT;;";
    result += "BUTTON:cad_export_dxf;text:export dxf;;";
    result += "BUTTON:cmd_cad_export_svg;text:svg;;";
    result += "NEWLINE:;;";

    result += "BUTTON:cad_draw_reference;text:create reference;;";
    result += "NEWLINE:;;";
    result += "BUTTON:cad_draw_arc;text:DRAW ARC;width:150;;";
    result += "BUTTON:cad_draw_arc2;text:DRAW ARC2;width:150;;";
    result += "NEWLINE:;;";

    result += "BUTTON:cmd_cad_draw_line;text:DRAW LINE;width:150;;";
    result += "NEWLINE:;;";

    result += "BUTTON:cmd_clipboard;text:CLIPBOARD;width:150;;";

    result += "NEWLINE:;;";
    result += "BUTTON:cmd_cad_draw_text2;text:create_text2;width:150;;";
    result += "BUTTON:cmd_cad_draw_refbox_develop;text:draw_refbox_develop;width:150;;";
    result += "BUTTON:cmd_cad_draw_refline;text:draw_refline;width:150;;";
    result += "BUTTON:cmd_draw_box;text:draw_box;width:150;;";

    //===================================================
#ifdef Q_OS_WASM
    assert(0);
#else
    EasyViewTml::substituteEx(result);

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("debug");
    tab->contentSetEx(result.toStdString());
#endif

    return 0;
}

//=============================================================================

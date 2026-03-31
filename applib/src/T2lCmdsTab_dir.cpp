//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lCmdsTab_dir.h"
#ifndef Q_OS_WASM
#include "T2lHtmlTabsRegistry.h"
#include "T2lHtmlTab.h"

//#include "T2lCadExeSettings.h"
#include "T2lEasyViewTml.h"

// infrastructure
//#include "TcHtmlDir.h"
//#include "TcHtmlViewTabbed.h"
#endif
#include "TcArgCol.h"
#include "TcArgVal.h"
#include "T2lGFileCol.h"
#include "T2lStoredFileNames.h"
#include "T2lWidgetInteractCol.h"
#include "T2lRefFiles.h"

// qt
#include <QDir>
#include <QDirIterator>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include <QUrl>

#include <iostream>

using namespace std;
using namespace T2l;

//=============================================================================
QString CmdsTab_dir::currentDir_ = "";
QString CmdsTab_dir::subdir_ = "";

//=============================================================================
QString CmdsTab_dir::drawingsDirGet()
{
    QString dirPath = QDir::homePath() + "/t2ls";
    if (!QDir(dirPath).exists()) QDir(QDir::homePath()).mkdir("t2ls");

    if ( subdir_.isEmpty() ) return dirPath;

    QString dirPath2 = dirPath + "/" + subdir_;
    if (!QDir(dirPath2).exists()) QDir(dirPath).mkdir(subdir_);

    return dirPath2;
}

//=============================================================================
QString CmdsTab_dir::examplesDirGet()
{
    QString dirPath = StoredFileNames::getExeUpDir() + "/examples";
    if (!QDir(dirPath).exists()) QDir(StoredFileNames::getExeUpDir()).mkdir("examples");
    return dirPath;
}

//=============================================================================
QString CmdsTab_dir::currentDirGet()
{
    if (currentDir_.isEmpty()) currentDir_ = examplesDirGet();
    return currentDir_;
}

//=============================================================================
bool CmdsTab_dir::alreadyUsed_(const QString& filePath)
{
    QFileInfo fi(filePath);
    QDir dir = fi.dir();

    GFileCol& files = GFileCol::instance();
    for ( int i = 0; i < files.count(); i++ ) {
        QFileInfo fii(files.get(i)->filePath());
        if ( fii.dir() != dir) continue;
        if ( fii.baseName() != fi.baseName() ) continue;
        return true;
    }

    return false;
}

//=============================================================================
QString CmdsTab_dir::getT2ls_(const QString& dirStr)
{
    QString wrapper( "<a href='tcview:://#cmd_cad_file_open $FILELINK show'>$FILENAME</a>&nbsp;&nbsp; " );

    QDir dir(dirStr);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.t2l";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dirStr, list.at(i));

        if ( alreadyUsed_(file.absoluteFilePath()) ) continue;

        QString resulti = wrapper;
        resulti.replace("$FILELINK", file.absoluteFilePath());
        QString fileName = file.fileName();
        resulti.replace("$FILENAME", fileName);
        result += resulti;
    }

    return result;
}

//=============================================================================
QString CmdsTab_dir::getT2lsThumbs_(const QString& dirStr)
{
    //WidgetInteractCol& widgets = WidgetInteractCol::instance();

    QString wrapper( "<p>$IMAGE<br/>$BOLD_BEG<a href='tcview:://#cmd_cad_file_open $FILELINK show'>");
    wrapper += "$FILENAME</a>$BOLD_END";
    wrapper += "$REFSTR";
    wrapper += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br><br></p>";

    QDir dir(dirStr);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.t2d";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    result += "<table style='width:100%;text-align:left;vertical-align: bottom;'>";
    result += "<tr>";

    for (int i = 0; i < list.size(); i++) {
        if ( i!=0 && i%3==0 ) {
            result += "</tr><tr>";
        }

        result += "<th style='text-align: left;'>";

        QFileInfo file(dirStr, list.at(i));

        QString resulti = wrapper;
        RefFiles reffiles(file.absoluteFilePath());

        if ( alreadyUsed_(file.absoluteFilePath()) ) {
            resulti = "<p>$IMAGE<br/><b>$FILENAME</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br><br></p>";
        }
        else if (reffiles.count() > 0) {
            QString subst = "&nbsp;<a href='tcview:://#cmd_cad_file_open $FILELINK show refless'>[refless]</a>";
            resulti.replace("$REFSTR", subst);
            resulti.replace("$BOLD_BEG", "<b>");
            resulti.replace("$BOLD_END", "</b>");
        }
        else {
            resulti.replace("$REFSTR", "");
            resulti.replace("$BOLD_BEG", "");
            resulti.replace("$BOLD_END", "");
        }
        resulti.replace("$FILELINK", file.absoluteFilePath());
        QString fileName = file.fileName();
        resulti.replace("$FILENAME", fileName);

        QString fileImage(list.at(i));
        fileImage.replace("t2d", "png");
        QFileInfo fi(fileImage);
        fileImage = fi.dir().path() + "/thumbnails/" + fi.fileName();
        QFileInfo image(dirStr, fileImage);
        if (image.exists() == false) {
            QDir dir(QCoreApplication::applicationDirPath());
            dir.cdUp();
            image = QFileInfo(dir.path() + "/resource/icons/file.png");
        }
        QString link = "<img src='";
        link += image.filePath() + "' width='180' height='180'></img>";
        resulti.replace("$IMAGE", link);

        result += resulti;

        result += "</th>";
    }

    result += "</tr>";
    result += "</table>";

    return result;
}


//=============================================================================
QString CmdsTab_dir::getImages_(const QString& dirStr)
{
    QString wrapper( "<a href='tcview:://#cmd_cad_file_open $FILENAME show'>"
                     "<img width='50' height='45' src='file://$FILENAME'/>"
                     "</a>&nbsp;&nbsp; " );

    QDir dir(dirStr);
    if ( dir.exists() == false ) return "No files found";

    QStringList nameFilter;
    nameFilter << "*.jpg" << "*.jpeg" << "*.png" << ".bmp";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    QString result;

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dirStr, list.at(i));

        if ( alreadyUsed_(file.absoluteFilePath()) ) continue;

        //APTA2 bool selected =  Filesystem::instance().isSelected(file.absoluteFilePath());
        bool selected = false;

        QString resulti = wrapper;
        resulti.replace("$FILENAME", file.absoluteFilePath());

        if ( selected ) result += "<font size='230'>[</font>";
        result += resulti;
        if ( selected ) result += "<font size='230'>]</font>";
    }

    return result;
}

//=============================================================================
int CmdsTab_dir::tab_set_dir_browser2_header(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
#ifdef Q_OS_WASM
    assert(0);
#else
    QString result;
    QTextStream str(&result);

    QDir dir(currentDirGet());

    str << "TEXT:HOME;cmd:cad_set_actual_dir \"" + drawingsDirGet() + "\";;";
    str << "SPACE:;;SPACE:;;";
    str << "TEXT:EXAMPLES;cmd:cad_set_actual_dir \"" + examplesDirGet() + "\";;";
    str << "SPACE:;;SPACE:;;";
    str << "TEXT:PROJEKTY;cmd:cad_set_actual_dir \"" + StoredFileNames::getExeUpDir() + "/../../PROJEKTY_UKAZKY\";;";
    str << "NEWLINE:;;";

    str << "TEXT:Current directory: <b>";
    QStringList dirs = currentDirGet().split("/");
    for ( int i = 0; i < dirs.count()-1; i++) {
        str << dirs[i] << "/";
    }
    str << "</b>;;";
    str << "TEXT:<b>" << dirs.last() << "</b>;cmd:external_open_actual_dir;;";
    str << "SPACE:;;";str << "SPACE:;;";str << "SPACE:;;";str << "SPACE:;;";

    str << "BUTTON:cad_create_file \"" << currentDirGet() << "\";text:New file;;";

    str << "NEWLINE:;;";
    str << "TEXT:Subdirectories:;;";
    QDirIterator dirIt(dir.absolutePath(), QDir::AllDirs | QDir::Dirs);
    while( dirIt.hasNext() ) {
        dirIt.next();

        if ( dirIt.fileInfo().fileName() == "." ) continue;
        if ( dirIt.fileInfo().fileName() == "t2d" ) continue;

        str << "SPACE:;;";
        str << "TEXT:" << dirIt.fileInfo().fileName()
            << ";cmd:cad_set_actual_dir \"" + dirIt.fileInfo().canonicalFilePath() + "\";;";
    }

    str.flush();

    //QString test = result.right(250);

    EasyViewTml::substituteEx(result);

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("dir2_header");
    //tab->contentSet(result.toLatin1().data());
    //std::cout << "==================================\n" << result.toStdString();
    tab->contentSetEx(result.toStdString());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_dir::tab_set_dir_browser2(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
#ifdef Q_OS_WASM
    assert(0);
#else
    QString result;
    QTextStream str(&result);

    QDir dir(currentDirGet());

    QStringList nameFilter;
    nameFilter << "*.t2d";
    QStringList list = dir.entryList(nameFilter, QDir::Files);

    for (int i = 0; i < list.size(); i++) {
        QFileInfo file(dir.absolutePath(), list.at(i));

        QString fileName = file.absoluteFilePath();
        QFileInfo fi(fileName);
        QString imageName = fi.absolutePath() + "/thumbnails/" + fi.baseName() + ".png";

        QFileInfo ifi(imageName);
        if (ifi.exists() == false) {
            QDir dir(QCoreApplication::applicationDirPath());
            dir.cdUp();
            imageName = dir.path() + "/resource/icons/file.png";
            ifi.setFile(imageName);
        }
        QString fileOpen = QString("cmd_cad_file_open \"") + fileName + "\" show";
        if (ifi.exists()) {
            str << "BUTTONEX:";
            if (alreadyUsed_(fileName)) {
                str << ";";
            }
            else {
                str << fileOpen << ";";
            }
            str << "icon:" << imageName << ";text:" << file.baseName() << ";;";
        }

        str << "SPACE:;;";
    }

    str.flush();

    EasyViewTml::substituteEx(result);

    HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("dir2");
    //tab->contentSet(result.toLatin1().data());
    tab->contentSetEx(result.toStdString());
#endif

    return 0;
}

//=============================================================================
int CmdsTab_dir::tab_set_dir_browser(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    //QDir dir(Cmd_refed_file_list::currentDir());
    QDir dir(currentDirGet());

    result.append("<div class='dir_part1'>");
    result.append("<p>Current directory: <b>");
    QStringList dirs = currentDirGet().split("/");
    for ( int i = 0; i < dirs.count()-1; i++) {
        result.append(dirs[i]);
        result.append("/");
    }
    result.append("<a href='tcview:://#external_open_actual_dir'>");
    result.append(dirs.last());
    result.append("</a>");
    result.append("</b>");
    //result.append("&nbsp;&nbsp;&nbsp;&nbsp;<a href='tcview:://#cad_set_show_thumbs'>[VIEW]</a>");
    result.append("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
    result.append("<a href='tcview:://#cad_create_file \"");
    result.append(currentDirGet() + "\"'>[new file]</a>");
    result.append("</p>");

    result.append("<p>Subdirectories: ");
    QDirIterator dirIt(dir.absolutePath(), QDir::AllDirs | QDir::Dirs);
    while( dirIt.hasNext() ) {
        dirIt.next();

        if ( dirIt.fileInfo().fileName() == "." ) continue;
        if ( dirIt.fileInfo().fileName() == "t2d" ) continue;

        result.append("<a href='tcview:://#cad_set_actual_dir ");
        result.append(dirIt.fileInfo().canonicalFilePath());
        result.append("'>");
        result.append(dirIt.fileInfo().fileName());
        result.append("</a>");
        result.append("&nbsp; &nbsp;");
    }
    result.append("</p></div>");

    result.append("<div>");
    //if (CadExeSettings::instance().showThumbnails())
    //{
        result.append(getT2lsThumbs_(currentDirGet()));
    /*}
    else {
        result.append(getT2ls_(currentDirGet()));
        result.append("<br></div><div>");
        result.append(getImages_(currentDirGet()));
        result.append("</div>");
    }*/

    //APTA2 TcHtmlViewTabbed::mainView().tabSet("dir", result.toLatin1().data());

        assert(0);
    /*HtmlTab* tab = HtmlTabsRegistry::instance().tabGet_("dir");
    tab->contentSetEx(result.toStdString());*/

    return 0;
}

//=============================================================================
int CmdsTab_dir::cad_set_actual_dir(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("dir name must be entered");
    TcArgVal* val = args.at(1);
    if (val == nullptr) return args.appendError("dirname name must be entered");

    currentDir_ = QString(val->value());

    return 0;
}

//=============================================================================
int CmdsTab_dir::cmd_external_open_actual_dir(TcCmdContext* context, TcArgCol& args)
{
    QDir dir(currentDirGet());
    if ( dir.exists() == false ) return args.appendError("active directory does not exist");

    QDesktopServices::openUrl(QUrl::fromLocalFile(dir.absolutePath()));

    return 0;
}

//=============================================================================
int CmdsTab_dir::cmd_open_file_external(TcCmdContext* context, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("file path must be entered");
    TcArg* val = args.at(1);

    QString file = QString(val->value());

    //TODO check existence
    //QDir dir(currentDirGet());
    //if ( dir.exists() == false ) return args.appendError("active directory does not exist");

    QDesktopServices::openUrl(QUrl::fromLocalFile(file));

    return 0;
}

//=============================================================================

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
#include "./TcCmds_dirBrowser.h"

// infrastructure
#include "TcHtmlDir.h"
#include "TcHtmlViewTabbed.h"
#include "TcArgCol.h"
#include "TcArgVal.h"

// qt
#include <QDir>
#include <QDirIterator>

using namespace std;

QString TcCmds_dirBrowser::currentDir_ = "g:/home/KADLUB/test";

//=============================================================================
int TcCmds_dirBrowser::tab_set_dir_browser(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QString result;

    QDir dir(currentDir());

    result.append(
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        );
    result.append("<p><b>");
    result.append(currentDir().toStdString().c_str());
    result.append("</b></p>");

    result.append("<p>favourites:<br>");
    result.append("<a href='tcview:://#set_actual_dir /home/petrtalla/Development/P4/pia/test/regression/test_cornertestengine/image'>");
    result.append("regression/test_cornertestengine</a><br>");
    result.append("<a href='tcview:://#set_actual_dir /home/petrtalla/Development/P4/imagecol_corners'>");
    result.append("imagecol_corners</a><br>");
    result.append("</p>");

    result.append("<p>");
    QDirIterator dirIt(dir.absolutePath(), QDir::AllDirs | QDir::Dirs);
    while( dirIt.hasNext() ) {
        dirIt.next();

        if ( dirIt.fileInfo().fileName() == "." ) continue;

        result.append("<a href='tcview:://#set_actual_dir ");
        result.append(dirIt.fileInfo().canonicalFilePath());
        result.append("'>");
        result.append(dirIt.fileInfo().fileName());
        result.append("</a>");
        result.append("<br>");
    }
    result.append("</p>");

    TcHtmlDir dira(currentDir());
    QString wrapperT2l( "<a href='tcview:://#cmd_cad_file_open $FILELINK'>"
                     "$FILENAME"
                     "</a><br>" );
    result.append(dira.getT2ls(wrapperT2l));
    QString wrapper( "<a href='tcview:://#cmd_cad_file_open $FILENAME'>"
                     "<img width='100' height='90' src='file://$FILENAME'/>"
                     "</a><br>" );
    result.append(dira.getImages(wrapper));
    result.append(
    "</body>"
    "</html>"
    );

    TcHtmlViewTabbed::mainView().tabSet("dir_browser", result.toLatin1().data());

    return 0;
}

//=============================================================================
void TcCmds_dirBrowser::currentDirSet(const QString& dir)
{
    currentDir_ = dir;
}

//=============================================================================
int TcCmds_dirBrowser::set_actual_dir(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("dir name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();
    if (val == NULL) return args.appendError("dirname name must be entered");
    //currentDir_ = val->value();
    currentDirSet(val->value());

    return 0;
}

//=============================================================================
int TcCmds_dirBrowser::show_image_ex(TcCmdContext* /*context*/, TcArgCol& args)
{
    // @@@ mining arguments
    if (args.count() < 2) return args.appendError("image name must be entered");
    TcArgVal* val = args.at(1)->getAsVal();
    if (val == NULL) return args.appendError("image name must be entered");
    QString filename = val->value();

    return 0;
}

//=============================================================================

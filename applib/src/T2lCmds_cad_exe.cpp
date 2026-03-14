//
// Copyright (C) 2014 Petr Talla. [petr.talla@gmail.com]
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
//self
#include "T2lCmds_cad_exe.h"

#include "T2lGFileCol.h"
#include "T2lGFile.h"
#include "T2lGFileObjects.h"
#include "T2lGFileImage.h"
#include "T2lGFileImgDescr.h"
#include "T2lCmd_active_file_move.h"
#include "T2lCmdQueue.h"
#include "T2lDisplayCol.h"
#include "T2lActiveFile.h"
#include "T2lFilterFile.h"
#include "T2lActiveFile.h"
#include "T2lWidgetFile.h"
#include "T2lCmd_draw_refLine.h"
#include "T2lCmd_draw_refBoxDevelop.h"
#include "T2lCmd_draw_textBox.h"
#include "T2lUpdateLock.h"
#include "T2lCmd_draw_papper.h"
#include "T2lCmd_draw_papperSpace.h"
#include "T2lCmd_draw_reference.h"
#include "T2lCadObject_papper.h"
#include "T2lWidgetFileCol.h"

#include "T2lRefFiles.h"
#include "T2lPapperEx.h"
#include "T2lCmd_transform_image.h"
#include "T2lCmd_image_properties.h"

#include "T2lCmd_draw_routeSegment.h"

//geogebra
#include "T2lGFile.h"
#include "T2lCmd_draw_line.h"
#include "T2lCmd_draw_dimm.h"
#include "T2lCmd_draw_area.h"
#include "T2lCmd_draw_image.h"
#include "T2lCmd_draw_text.h"
#include "T2lCmd_draw2_text.h"
#include "T2lCmd_view_fit.h"
#include "T2lCmd_measure.h"
#include "T2lCmd_draw_area.h"
#include "T2lCmd_settings.h"
#include "T2lCmd_route_connect.h"
#include "T2lCmd_generator_connect.h"
#include "T2lCmd_draw_trafficGenerator.h"
#include "T2lCmd_draw_registrationLine.h".h"
#include "T2lCmd_move_point.h"
#include "T2lCmd_route_export.h"
#include "T2lCmd_route_run.h"
#include "T2lCmd_regline_connect.h"
#include "T2lCmd_draw_trafficCounter.h"

#include "TcArg.h"
#include "TcArgVal.h"
#include "TcArgCol.h"

#include "T2lFilter.h"
#include "T2lScene.h"
#include "T2lGObjectPool.h"

#include "T2lDisplayBmp.h"
#include <QPainter>
#include "T2lCanvasPainter.h"

//hg
#include "T2lCmdQueue.h"

#include "T2lGLoadSave.h"
#include "T2lAfile.h"
#include "T2lAfileAttr.h"
#include "T2lAfileRecord.h"
#include "T2lStoredAttrNUM.h"

#include "TcCmdTransl.h"

#include "T2lEntityPoint.h"

#include "T2lGFileString.h"

#ifndef Q_OS_WASM
#include "T2lEasyView.h"
//#include "T2lEasyViewCad.h"

#endif


//qt
#include <QFileInfo>
#include <QString>
#include <QTextStream>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>

#include <QSettings>
#include <QFileDialog>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/threading.h>
#endif

//std
#include <sstream>

using namespace std;
using namespace T2l;

int Cmds_cad_exe::cmd_cad_download_file(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    ActiveFile* af = ActiveFile::activeGet();
    QString content;
    QTextStream stream(&content);
    af->file()->saveStream(stream);

    QFileDialog::saveFileContent(content.toUtf8(), "ua.t2d");

    return 0;
}

int Cmds_cad_exe::cmd_cad_upload_file(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    QFileDialog::getOpenFileContent("All files (*)",
        [](const QString &fileName, const QByteArray &fileContent) {
            if (fileName.isEmpty()) {
                qDebug() << "User canceled file dialog.";
                return;
            }

            /*qDebug() << "Selected file:" << fileName;
            qDebug() << "File size:" << fileContent.size() << "bytes";

            // Example: interpret as text
            QTextStream stream(fileContent);
            QString firstLine = stream.readLine();
            qDebug() << "First line:" << firstLine;

            // Or call a static processing function
            // Cmds_cad_exe::processFile(fileName, fileContent);

            ActiveFile* af = ActiveFile::activeGet();
            GFileString* file = new GFileString(fileName, fileContent);
            GFileCol::instance().add(file);
            file->load();
            ActiveFile::changeActiveFile(file, false, true);*/

            QDir().mkpath("/data");

            QFile file(QString("/data/") + "file.t2d");
            file.open(QIODevice::WriteOnly);
            //file.write(fileContent);
            //file.close();

            QString cmd = QString("cmd_cad_file_open \"/data/") + "file.t2d" + "\" show";
            XCALL(cmd.toStdString().c_str());

            ActiveFile* af = ActiveFile::activeGet();
            QString con = QString::fromUtf8(fileContent);
            QTextStream ts(&con);
            af->file()->loadStream_(ts);
        });

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_move_point(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_move_point(), false );

    string result ( "<br><a href='tcview:://#cad_set_ortho'>[ortho]</a>" );
    args.appendVal(result.c_str(), "result");

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_line(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_line(), false );

    string result ( "<br><a href='tcview:://#cad_set_ortho'>[ortho]</a>" );
    args.appendVal(result.c_str(), "result");

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_refline(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_refLine(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_refbox_develop(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_refBoxDevelop(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_textbox(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_textBox(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_area(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_area(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_papper(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_papper(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_papper_space(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_papperSpace(), false );
    return 0;
}


//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_reference(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_reference(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_transform_image(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_transform_image(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_image_properties(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_image_properties(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_settings(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_settings(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_dimm(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_dimm(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_view_fit(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    CmdQueue::queue().add( new Cmd_view_fit(), true );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_image(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    CmdQueue::queue().add( new Cmd_draw_image(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_text(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw_text(), false );

    /*string result ( "<br>text: "
                    " <a href='tcview:://#text ahoj'> [ahoj]</a>"
                    " <a href='tcview:://#text sbohem'> [sbohem]</a>"
                  );

    args.appendVal(result.c_str(), "result");*/

    return 1;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_draw_text2(TcCmdContext* /*context*/, TcArgCol& args)
{
    CmdQueue::queue().add( new Cmd_draw2_text(), false );
    return 1;
}

//=============================================================================
int Cmds_cad_exe::alias(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*TODOM if ( args.count() < 2 ) return args.appendError("you must enter alias name");
    TcArg* arg1 = args.at(1);

    CmdQueue::queue().add( new Cmd_alias(arg1->value()), false );*/
    return 0;
}

//=============================================================================
int Cmds_cad_exe::alias_print(TcCmdContext* /*context*/, TcArgCol& args)
{
    /*TODOS stringstream ss;

    if ( args.count() < 2 ) {
        for (int i = 0; i < CmdAliasCol::instance().count(); i++ ) {
            if (i != 0) ss << endl;
            string id = CmdAliasCol::instance().get(i)->id();
            ss << "<a href='tcview:://#alias_print " << id << "'>";
            ss << id;
            ss << "</a> ";
        }
    }
    else {
        TcArg* arg1 = args.at(1);
        string alias = arg1->value();

        ss << alias << ":" << "<br>";

        CmdAlias* cmdAlias = CmdAliasCol::instance().get(alias.c_str());
        if (cmdAlias == nullptr) {
            ss << "NOT FOUND";
        }
        else {
            QString content = cmdAlias->content();
            QStringList list = content.split("\n");
            for (int i = 0; i < list.size(); i++) {
                ss << list.at(i).toStdString().c_str() << "<br>";
            }
        }
    }

    args.appendVal(ss.str().c_str(), "result");*/
    return 1;
}


//=============================================================================
int Cmds_cad_exe::cmd_cad_active_file_move(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    CmdQueue::queue().add( new Cmd_active_file_move(), false );
    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_load(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 2 ) return args.appendError("you must enter the text");
    TcArg* arg1 = args.at(1);

    TcArg* arg2 = args.at(2);
    QString fullFileName = arg2->value();

    GFile* file = GFileCol::instance().getByFileName(fullFileName);
    if (file == nullptr) return args.appendError("wrong file name");

    if ( string("load") == arg1->value() ) {
        if (file->loaded()) return args.appendError("file is already loaded");
        file->load();
    }
    else {
        if (file->loaded() == false) return args.appendError("file is already unloaded");
        file->unload();
    }

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_shift(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 2 ) return args.appendError("you must enter the arguments");

    TcArg* arg1 = args.at(1);
    TcArg* arg2 = args.at(2);

    int index = atoi(arg1->value());

    bool down = false;
    if ( string(arg2->value()) != "up" ) {
        down = true;
    }

    GFileCol::instance().shift(index, down);

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_set_afile_x(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter the offset");
    TcArg* arg1 = args.at(1);

    double offset = atof(arg1->value());

    GFile* file = ActiveFile::activeGet()->file();
    if ( file == nullptr ) return 0;

    UpdateLock l;

    file->setOffset(Vector2F(offset, file->getOffset().y()));
    file->refresh();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_set_afile_y(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter the offset");
    TcArg* arg1 = args.at(1);

    double offset = atof(arg1->value());

    GFile* file = ActiveFile::activeGet()->file();
    if ( file == nullptr ) return 0;

    UpdateLock l;

    file->setOffset(Vector2F(file->getOffset().x(), offset));
    file->refresh();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_set_afile_scale(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter the scale");
    TcArg* arg1 = args.at(1);

    double scale = atof(arg1->value());

    GFile* file = ActiveFile::activeGet()->file();
    if ( file == nullptr ) return 0;

    UpdateLock l;

    file->setScale(scale);
    file->refresh();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_set_afile_transf_angle(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter the angle");
    TcArg* arg1 = args.at(1);

    double angle = atof(arg1->value());

    GFile* file = ActiveFile::activeGet()->file();
    if ( file == nullptr ) return 0;

    UpdateLock l;

    file->setTransfAngle(Angle(angle));
    file->refresh();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_set_afile_transf_flipx(TcCmdContext* /*context*/, TcArgCol& args)
{
    GFile* file = ActiveFile::activeGet()->file();
    if ( file == nullptr ) return 0;

    UpdateLock l;

    file->setTransfFlipX(!file->getTransfFlipX());
    file->refresh();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_set_afile_transf_flipy(TcCmdContext* /*context*/, TcArgCol& args)
{
    GFile* file = ActiveFile::activeGet()->file();
    if ( file == nullptr ) return 0;

    UpdateLock l;

    file->setTransfFlipY(!file->getTransfFlipY());
    file->refresh();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_activate(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter file name");

    /*ActiveFile* af = ActiveFile::activeGet();
    if (af != nullptr && af->file()->changeRegistry() > 0) {
        QMessageBox::StandardButton button = QMessageBox::question(EasyView::instanceBase(),
            "Continuation Question",
            "The active file has unsaved changes. CONTINUE?",
            QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) return 0;
    }*/

    TcArg* arg = args.at(1);
    QString fullFileName = arg->value();

    GFile* file = GFileCol::instance().getByFileName(fullFileName);
    if (file == nullptr) return args.appendError("wrong file name");

    UpdateLock l;

    ActiveFile::changeActiveFile(file, false, false);

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_close(TcCmdContext* /*context*/, TcArgCol& args)
{
    if ( args.count() <= 1 ) return args.appendError("you must enter file name");

    TcArg* arg = args.at(1);
    QString fullFileName = arg->value();

    GFile* file = GFileCol::instance().getByFileName(fullFileName);
    if (file == nullptr) return args.appendError("wrong file name");

    /*if (ActiveFile::activeGet()->file() == file) {
        ActiveFile::instance_ = nullptr;
    }*/

    file->close();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_save(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    ActiveFile* af = ActiveFile::activeGet();
    if (af == nullptr) return 0;

    af->file()->save();

    ////////////////////////////////////////////////////////////////////////////
    // save thumbnail

    CadObject_papper* papper = nullptr;
    for ( int i = 0; i < af->file()->objects().count(); i++ ) {
          papper = dynamic_cast<CadObject_papper*>(af->file()->objects().get(i));
        if ( papper != nullptr ) break;
    }

    Box2F newDisplay;
    QColor color(228, 228, 228);

    if ( papper ) {
        newDisplay = papper->papperBox();
        color = QColor(242, 238, 203);
    }
    else {
        if ( DisplayCol::instance().count() == 0 ) return 0;

        GFile* file = ActiveFile::activeGet()->file();
        if ( file == nullptr ) return 0;
        newDisplay.inflateBy(file->bound());

        /*for (int i = 0; i < GFileCol::instance().count(); i++) {
            GFile* file = GFileCol::instance().get(i);
            if (file->loaded() == false) continue;
            newDisplay.inflateBy(file->bound());
        }*/
    }

    double delta = newDisplay.x().getLength();
    if ( delta < newDisplay.y().getLength() ) {
        delta = newDisplay.y().getLength();
    }
    if (delta == 0) delta = 100;

    Box2F box;
    box.inflateTo(newDisplay.getCenter());
    box.inflateBy(delta/2);

    Box2F boundSq = PapperEx::boundSq(box.getPoint(0), box.getPoint(2));
    PapperEx papperEx( 300, 300, boundSq.x().getLength()/300,
                     4000 );
    papperEx.print2( boundSq.getPoint(0));

    QString path = af->file()->filePath();
    QFileInfo fi(path);
    path = fi.dir().path() + "/thumbnails/" + fi.fileName();
    path.replace(".t2d", ".png");

    if ( QDir(fi.dir().path() + "/thumbnails").exists() == false ) {
        fi.dir().mkdir("thumbnails");
    }

    papperEx.pixmap().save( path );

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_file_open(TcCmdContext* context, TcArgCol& args)
{
    ActiveFile* af = ActiveFile::activeGet();


#ifndef Q_OS_WASM
    if (af != nullptr && af->file()->changeRegistry() > 0) {
        QMessageBox::StandardButton button = QMessageBox::question(EasyView::instanceBase(),
            "Continuation Question",
            "The active file has unsaved changes. CONTINUE?",
            QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) return 0;
    }
#endif

    if (args.count() < 2) return args.appendError("dir name must be entered");
    TcArgVal* val = args.at(1);
    if (val == nullptr) return args.appendError("dir name must be entered");

    QFileInfo fileInfo(val->value());
    if ( fileInfo.exists() == false ) {
        return args.appendError("file does not exist");
    }

    QString suffix = fileInfo.suffix();

    //bool show = false;

    QList<GFile*> files;

    if ( suffix == "t2d") {
        QString refs = val->value();
        /*refs.replace(".t2d", ".refs");
        bool thisLoaded = false;
        if ( args.count()<4 && QFileInfo(refs).exists() ) {
            GLoadSave loader(refs);
            Afile afile;
            afile.load(loader);

            for ( int i = 0; i < afile.recordCount(); i++) {
                AfileRecord* reci = afile.recordGet(i);

                if (reci->attrsGet(0).value() == "this") {
                    files.append(new GFileObjects(val->value()));
                    thisLoaded = true;
                    continue;
                }

                QString reference = "";
                Vector2F offset;
                double scale = 1;

                for ( int ir = 0; ir < reci->attrsCount(); ir++ ) {
                    AfileAttr& attri = reci->attrsGet(ir);

                    if (string(attri.name()) == "reference") {
                        reference = attri.value();
                    }
                    else if (string(attri.name()) == "offset-num") {
                        StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                        double dx = attrNum.get(0);
                        double dy = attrNum.get(1);
                        offset = Vector2F(dx, dy);
                    }
                    else if (string(attri.name()) == "scale-num") {
                        StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                        scale = attrNum.get();
                    }
                }

                if ( reference.isEmpty() == false) {
                    GFileObjects* gfile = new GFileObjects(reference);
                    gfile->setOffset(offset);
                    gfile->setScale(scale);

                    files.append(gfile);
                }
            }
        }*/

        RefFiles refFiles(refs);
        bool thisLoaded = false;
        for (int i = 0; i < refFiles.count(); i++) {
            RefFilesItem rfi = refFiles.refItemGet(i);
            if (rfi.isThis()) {
                files.append(new GFileObjects(val->value()));
                thisLoaded = true;
            }
            else {
                GFileObjects* gfile = new GFileObjects(rfi.filePath());
                gfile->setOffset(rfi.offset());
                gfile->setScale(rfi.scale());
                gfile->setTransfFlipX(rfi.flipX());
                gfile->setTransfFlipY(rfi.flipY());
                gfile->setTransfAngle(rfi.angle());

                files.append(gfile);
            }
        }

        if (thisLoaded == false) {
            files.append(new GFileObjects(val->value()));
        }
    }
    else if ( ( suffix == "png" ) ||
              ( suffix == "jpg" ) ||
              ( suffix == "jpeg" ) ) {
        files.append(new GFileImage(val->value()));
    }
    else if ( suffix == "t2limgd") {
        files.append(new GFileImgDescr(val->value()));
    }

    if (files.count() == 0) {
        return args.appendError("file is not of type t2l or png");
    }

    for ( int f = 0; f < files.count(); f++) {

        GFileCol::instance().add(files[f]);

        if (args.count() >= 3 ) {

            TcArgVal* val2 = args.at(2);

            bool fifile = true;

            if (args.count() >= 3 ) {
                fifile = false;
            }

            Scene* scene = nullptr;
            if ( val2->getString()=="show" ) {
                //WidgetInteractCol& widgets = WidgetInteractCol::instance();

                if(files[f]->filePath() == val->value()) {
                    ActiveFile::changeActiveFile(files[f], false, true);
                }
                else {
                    files[f]->load();
                }

                int cnt = WidgetFile::col().count();
                WidgetFile* view = nullptr;
                if ( fifile || WidgetFile::col().count()==0 ) {
                    view = new WidgetFile( "", Point2F(0, 0), 1.0/1000.0 );
                    //view->setAttribute(Qt::WA_DeleteOnClose);
                    //widgets.add(view);
                    view->resize(400, 300);

                    Filter* filter = nullptr;
                    if (fifile) {
                        filter = new FilterFile(files[f]);
                    }
                    else {
                        filter = new Filter();
                    }

                    Scene* scene = new Scene(filter);
                    GObjectPool::instance().addRefCol(scene);

                    view->colorBackgroundSet(Color::WHITE);
                    scene->entities().addDisplay(view);
                }
                else {
                    view = WidgetFile::col().get(0);
                }

                Box2F newDisplay;
                newDisplay.inflateBy(files[f]->bound());
                newDisplay.inflateBy( (newDisplay.x().getLength() + newDisplay.y().getLength()) / 10.0);
                if ( newDisplay.isEmpty() == false ) {
                    Point2F originNew (
                        ( view->scale() > 0 ) ? newDisplay.x().beg() : newDisplay.x().end(),
                        ( view->scale() > 0 ) ? newDisplay.y().beg() : newDisplay.y().end() );

                    view->originSet(originNew);

                    double scaleX = view->getRefCanvas().scale()*view->size().w()/newDisplay.x().getLength();
                    double scaleY = view->getRefCanvas().scale()*view->size().h()/newDisplay.y().getLength();

                    double scale = scaleX;
                    if (scaleY > scale) scale = scaleY;

                    view->scaleSet( scale);
                }

                if ( scene ) {
                    for (int i = 0; i < scene->count(); i++) {
                        scene->get(i)->repaint();
                    }
                }

                //Ref* get(int index) { return items_.get(index); }

                view->refresh();
                view->show();

                //show = true;
            }
        }

        /*if (show == false) {
            ActiveFile::changeActiveFile(files[f], false, true);
        }*/
    }

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_fileref_open(TcCmdContext* context, TcArgCol& args)
{
    int result = 0;

    if (args.count() < 2) return args.appendError("file name must be entered");
    TcArgVal* val = args.at(1);
    if (val == nullptr) return args.appendError("file name must be entered");
    QFileInfo fileInfo(val->value());
    if ( fileInfo.exists() == false ) {
        return args.appendError("file does not exist");
    }
    QString suffix = fileInfo.suffix();
    if ( suffix != "t2d") return args.appendError("file has not extension t2d");

    QString refs = val->value();
    refs.replace(".t2d", ".refs");
    if ( QFileInfo(refs).exists() ) {
        //GLoadSave loader(refs);
        Afile afile;
        afile.load(refs);

        for ( int i = 0; i < afile.recordCount(); i++) {
            AfileRecord* reci = afile.recordGet(i);

            QString reference = "";
            Vector2F offset;
            double scale = 1;

            for ( int ir = 0; ir < reci->attrCount(); ir++ ) {
                AfileAttr& attri = reci->attrGet(ir);

                if (string(attri.name()) == "reference") {
                    reference = attri.value();
                }
                else if (string(attri.name()) == "offset-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    double dx = attrNum.get(0);
                    double dy = attrNum.get(1);
                    offset = Vector2F(dx, dy);
                }
                else if (string(attri.name()) == "scale-num") {
                    StoredAttrNUM attrNum(attri.name(), attri.value().toStdString().c_str());
                    scale = attrNum.get();
                }
            }

            if ( reference.isEmpty() == false) {
                result += args.appendMsg("adding reference to %s", "MSG", reference.toStdString().c_str());
                GFileObjects* gfile = new GFileObjects(reference);
                gfile->setOffset(offset);
                gfile->setScale(scale);
                GFileCol::instance().add(gfile);
                gfile->load();
            }
        }
    }

    GFileObjects* gfile = new GFileObjects(fileInfo.absoluteFilePath());
    GFileCol::instance().add(gfile);
    ActiveFile::changeActiveFile(gfile, false, true);

    //WidgetInteractCol& widgets = WidgetInteractCol::instance();

    WidgetFile* view = new WidgetFile( "", Point2F(0, 0), 1.0/1000.0 );
    //view->setAttribute(Qt::WA_DeleteOnClose);
    view->colorBackgroundSet(Color::WHITE);
    //widgets.add(view);
    view->resize(600, 400);
    view->move(0,0);

    Filter* filter = new Filter();

    Scene* scene = new Scene(filter);
    GObjectPool::instance().addRefCol(scene);
    scene->entities().addDisplay(view);

    Box2F newDisplay;
    newDisplay.inflateBy(gfile->bound());
    newDisplay.inflateBy( (newDisplay.x().getLength() + newDisplay.y().getLength()) / 10.0);
    if ( newDisplay.isEmpty() == false ) {
        Point2F originNew (
            ( view->scale() > 0 ) ? newDisplay.x().beg() : newDisplay.x().end(),
            ( view->scale() > 0 ) ? newDisplay.y().beg() : newDisplay.y().end() );

        view->originSet(originNew);

        double scaleX = view->getRefCanvas().scale()*view->size().w()/newDisplay.x().getLength();
        double scaleY = view->getRefCanvas().scale()*view->size().h()/newDisplay.y().getLength();

        double scale = scaleX;
        if (scaleY > scale) scale = scaleY;

        view->scaleSet( scale);
    }

    for (int i = 0; i < scene->count(); i++) {
        scene->get(i)->repaint();
    }

    view->refresh();
    view->show();

    return result;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_list_files(TcCmdContext* /*context*/, TcArgCol& args)
{
    stringstream ss;

    ss << "<br>";

    GFileCol& files = GFileCol::instance();
    for (int f = 0; f < files.count(); f++) {
        GFile* file = files.get(f);

        ss << "</br>";
        ss << "#### " << file->fileName().toStdString();

        if (file->loaded()) {
            ss << " [loaded]";
        }
        else {
            ss << " [not loaded]";
        }

        if (file == ActiveFile::activeGet()->file()) {
            ss << " [active]";
        }

        for (int i = 0; i < file->objects().count(); i++) {
            ss << "<br>" << file->objects().get(i)->print();
        }
    }

    args.appendVal(ss.str().c_str(), "result");

    return 1;
}

//=============================================================================
/*int Cmds_cad_exe::cmd_cad_set_show_thumbs(TcCmdContext* context, TcArgCol& args)
{
    bool value = !CadExeSettings::instance().showThumbnails();
    CadExeSettings::instance().showThumbnailsSet(value);
    return 0;
}*/

/*Display* display = new Display(Point2F(0,0), 1.0/10000);

display->bitmap_->bmpPixmap = new QPixmap(800, 700);
display->bitmap_->bmpPixmap->fill(qRgba(255, 50, 80, 255));

scene->entities().addDisplay(display);

//display->refresh();
display->bitmap_->bmpUpdate();
QPixmap pixmap = *display->bitmap();
*/

//=============================================================================
int Cmds_cad_exe::cmd_cad_print_test(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    Scene* scene = new Scene(new Filter());
    GObjectPool::instance().addRefCol(scene);
    scene->entities().refresh();

    QPixmap pixmap( 2100, 2970 );
    pixmap.fill(QColor(255, 255, 255));

    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);
    CanvasPainter display( painter, Point2F(-1000, -1000), Size2F(2100, 2970),
                           1.0/20000, 4000);
    scene->entities().draw(display);
    painter.end();

    pixmap.save("C:\\HOME\\KADLUB\\cvz\\apky\\cad_exe\\examples\\TEST\\PRINT.png");

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_smallprint_test(TcCmdContext* /*context*/, TcArgCol& args)
{
    Scene* scene = new Scene(new Filter());
    GObjectPool::instance().addRefCol(scene);
    scene->entities().refresh();

    QPixmap pixmap( 100, 100 );
    pixmap.fill(QColor(255, 255, 255));

    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::Antialiasing);
    CanvasPainter display( painter, Point2F(-0.5, -0.5), Size2F(100, 100),
                           1.0/250, 25000);

    static int i = 0;
    StyleCol& styles = ActiveFile::activeGet()->file()->styles();
    if (i >= styles.count()) i=0;
    Style* pointStyle = styles.get(i++)->style();;
    EntityPoint* point = new EntityPoint( Point2F(0, 0), *pointStyle, false,
                                 ANGLE_ZERO_VIEW, 0, nullptr, -1 );
    point->draw(&display);

    painter.end();

    pixmap.save("C:\\HOME\\KADLUB\\cvz\\apky\\cad_exe\\examples\\TEST\\PRINT.png");

    QString result;
    QTextStream resultStream(&result);

    resultStream << "ahoj";
    resultStream.flush();

    args.appendVal(result.toStdString().c_str(), "result");

    return 1;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_save_reference(TcCmdContext* /*context*/, TcArgCol& /*args*/)
{
    if ( ActiveFile::activeGet() == nullptr ) return 0;

    QString path = ActiveFile::activeGet()->file()->filePath();
    path.replace(".t2d", ".refs");

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream stream(&file);

    for ( int i = 0; i < GFileCol::instance().count(); i++ ) {
        GFile* gfile = GFileCol::instance().get(i);
        if (gfile == ActiveFile::activeGet()->file()) {
            stream << "this" << Qt::endl << Qt::endl;
            continue;
        }

        stream << "reference: " << gfile->filePath() << Qt::endl;
        stream << "offset-num: " << gfile->getOffset().x() << " ";
        stream << gfile->getOffset().y() << Qt::endl;
        stream << "scale-num: " << gfile->getScale() << Qt::endl;
        stream << "flipx-num: " << (gfile->getTransfFlipX()?1:0) << Qt::endl;
        stream << "flipy-num: " << (gfile->getTransfFlipY()?1:0) << Qt::endl;
        stream << "angle-num: " << gfile->getTransfAngle().get();
        if (i<GFileCol::instance().count()-1) stream << Qt::endl << Qt::endl;
    }

    file.close();

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_create_file(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("file name must be entered");
    TcArgVal* val = args.at(1);
    if (val == nullptr) return args.appendError("file name must be entered");
    QDir dir(val->value());

    bool ok;

    assert(0);
    /*QString text = QInputDialog::getText(EasyView::instanceBase(), "Enter the new file name",
                          "File name", QLineEdit::Normal, "", &ok);

    if (ok == false) return 0;

    QString fileName = QString(val->value())+"/"+text+".t2d";

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QString cmd = QString("cmd_cad_file_open \"") + fileName + "\" show";
    XCALL(cmd.toStdString().c_str());*/

    return 0;
}

//=============================================================================
int Cmds_cad_exe::cmd_cad_create_file_direct(TcCmdContext* /*context*/, TcArgCol& args)
{
    if (args.count() < 2) return args.appendError("file name must be entered");
    TcArgVal* val = args.at(1);
    TcArgVal* val2 = args.at(2);
    if (val == nullptr) return args.appendError("file name must be entered");
    QDir dir(val->value());

    /*QSettings s(QSettings::WebIndexedDBFormat,
                QSettings::UserScope,
                "T2ls", "T2lsCad");

    // store some values
    s.setValue(val2->value(), "aaa");
    s.sync();*/

    /*bool ok;
    QString text = QInputDialog::getText(EasyView::instanceBase(), "Enter the new file name",
                                         "File name", QLineEdit::Normal, "", &ok);

    if (ok == false) return 0;*/

    QString fileName = QString(val->value())+"/"+val2->value()+".t2d";

    QDir().mkpath(val->value());

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QString cmd = QString("cmd_cad_file_open \"") + fileName + "\" show";
    XCALL(cmd.toStdString().c_str());

/*#ifdef __EMSCRIPTEN__
    EM_ASM({
        if (typeof FS === 'undefined') return;
        if (!Module.idbfsReady) {
            console.warn('IDBFS flush skipped: not ready yet');
            return;
        }
        FS.syncfs(false, function (err) {
            if (err) console.error('IDBFS flush failed:', err);
            else console.log('IDBFS flushed OK');
        });
    });
#endif*/

    return 0;
}


//=============================================================================

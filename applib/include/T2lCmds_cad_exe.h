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
#pragma once

#include <TcCmdEngine.h>

//=============================================================================
class Cmds_cad_exe {
//=============================================================================
public:
//<CMDS>
//=============================================================================
//<REGISTRATOR>
    static bool registerCmds_()
    {
        REGISTER_CMD("cad_download_file",        cmd_cad_download_file,        "cad");
        REGISTER_CMD("cad_upload_file",        cmd_cad_upload_file,        "cad");
        REGISTER_CMD("cmd_cad_file_open",        cmd_cad_file_open,        "cad");
        REGISTER_CMD("cmd_cad_fileref_open",     cmd_cad_fileref_open,     "cad");
        REGISTER_CMD("cmd_cad_save",             cmd_cad_save,             "cad");
        REGISTER_CMD("cmd_cad_file_load",        cmd_cad_file_load,        "cad");
        REGISTER_CMD("cmd_cad_active_file_move", cmd_cad_active_file_move, "cad");
        REGISTER_CMD("cmd_cad_list_files",       cmd_cad_list_files,       "cad");
        REGISTER_CMD("cmd_cad_file_activate",    cmd_cad_file_activate,    "cad");
        REGISTER_CMD("cmd_cad_draw_line", cmd_cad_draw_line, "cad");
        REGISTER_CMD("cmd_move_point", cmd_move_point, "cad");

        REGISTER_CMD("cmd_cad_draw_area", cmd_cad_draw_area, "cad");
        REGISTER_CMD("cmd_cad_draw_dimm", cmd_cad_draw_dimm, "cad");
        REGISTER_CMD("cad_draw_papper", cmd_cad_draw_papper, "cad");
        REGISTER_CMD("cad_draw_papper_space", cmd_cad_draw_papper_space, "cad");
        REGISTER_CMD("cad_draw_reference", cmd_cad_draw_reference, "cad");
        REGISTER_CMD("cmd_cad_transform_image", cmd_cad_transform_image, "cad");
        REGISTER_CMD("cmd_cad_image_properties", cmd_cad_image_properties, "cad");
        REGISTER_CMD("cad_print_test", cmd_cad_print_test, "cad");
        REGISTER_CMD("cad_smallprint_test", cmd_cad_smallprint_test, "cad");
        REGISTER_CMD("cmd_cad_draw_image",       cmd_cad_draw_image,       "cad");
        REGISTER_CMD("cmd_cad_draw_text",        cmd_cad_draw_text,        "cad");
        REGISTER_CMD("cmd_cad_draw_text2",        cmd_cad_draw_text2,        "cad");
        REGISTER_CMD("alias",                    alias,                    "cad");
        REGISTER_CMD("alias_print",              alias_print,              "cad");
        REGISTER_CMD("cmd_cad_view_fit",         cmd_cad_view_fit,         "cad");
        REGISTER_CMD("cmd_cad_file_close",       cmd_cad_file_close,       "cad");
        REGISTER_CMD("cmd_cad_draw_refline",     cmd_cad_draw_refline,     "cad");
        REGISTER_CMD("cmd_cad_draw_refbox_develop",      cmd_cad_draw_refbox_develop,      "cad");
        REGISTER_CMD("cmd_cad_draw_textbox",      cmd_cad_draw_textbox,      "cad");
        REGISTER_CMD("cad_settings",             cmd_cad_settings,         "cad");
        REGISTER_CMD("cad_save_reference",       cmd_cad_save_reference,   "cad");

        REGISTER_CMD( "cad_create_file",      cmd_cad_create_file,     "cad" );
        REGISTER_CMD( "cad_create_file_direct",      cmd_cad_create_file_direct,     "cad" );
        REGISTER_CMD( "cad_file_shift",       cmd_cad_file_shift,      "cad" );
        REGISTER_CMD( "cad_set_afile_scale",  cmd_cad_set_afile_scale, "cad" );
        REGISTER_CMD( "cmd_cad_set_afile_x",  cmd_cad_set_afile_x, "cad" );
        REGISTER_CMD( "cmd_cad_set_afile_y",  cmd_cad_set_afile_y, "cad" );
        REGISTER_CMD( "cad_set_afile_transf_angle", cmd_cad_set_afile_transf_angle, "cad" );
        REGISTER_CMD( "cad_set_afile_transf_flipx", cmd_cad_set_afile_transf_flipx, "cad" );
        REGISTER_CMD( "cad_set_afile_transf_flipy", cmd_cad_set_afile_transf_flipy, "cad" );



        return true;
    }
private:
//<INTERNALS>

    CMD_FCE(cmd_cad_download_file);
    CMD_FCE(cmd_cad_upload_file);


    CMD_FCE(cmd_move_point);

    CMD_FCE(cmd_cad_file_open);
    CMD_FCE(cmd_cad_fileref_open);
    CMD_FCE(cmd_cad_save);
    CMD_FCE(cmd_cad_file_load);
    CMD_FCE(cmd_cad_active_file_move);
    CMD_FCE(cmd_cad_list_files);
    CMD_FCE(cmd_cad_file_activate);
    CMD_FCE(cmd_cad_draw_line);
    CMD_FCE(cmd_cad_draw_area);
    CMD_FCE(cmd_cad_draw_dimm);
    CMD_FCE(cmd_cad_draw_image);
    CMD_FCE(cmd_cad_draw_text);
    CMD_FCE(cmd_cad_draw_text2);
    CMD_FCE(cmd_cad_view_fit);
    CMD_FCE(alias);
    CMD_FCE(alias_print);
    CMD_FCE(cmd_cad_file_close);
    CMD_FCE(cmd_cad_draw_refline);
    CMD_FCE(cmd_cad_draw_textbox);
    CMD_FCE(cmd_cad_draw_refbox_develop);
    CMD_FCE(cmd_cad_settings);
    CMD_FCE(cmd_cad_draw_papper);
    CMD_FCE(cmd_cad_draw_papper_space);
    CMD_FCE(cmd_cad_draw_reference);
    CMD_FCE(cmd_cad_transform_image);
    CMD_FCE(cmd_cad_image_properties);
    CMD_FCE(cmd_cad_print_test);
    CMD_FCE(cmd_cad_smallprint_test);
    CMD_FCE(cmd_cad_save_reference);

    CMD_FCE( cmd_cad_create_file);
    CMD_FCE( cmd_cad_create_file_direct);

    // file transformation
    CMD_FCE( cmd_cad_file_shift);
    CMD_FCE( cmd_cad_set_afile_x);
    CMD_FCE( cmd_cad_set_afile_y);
    CMD_FCE( cmd_cad_set_afile_scale);
    CMD_FCE( cmd_cad_set_afile_transf_angle);
    CMD_FCE( cmd_cad_set_afile_transf_flipx);
    CMD_FCE( cmd_cad_set_afile_transf_flipy);
};

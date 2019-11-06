///////////////////////////////////////////
//  LilypondTranscription.h
//  LilypondTranscription
//
//  Created by Georg Boenn on 2019-10-19.
//  Copyright (c) 2019 Georg Boenn. All rights reserved.
//  GNU General Public License version 3.0
//  Free Software Foundation
///////////////////////////////////////////

#ifndef __LilypondTranscription_h__
#define __LilypondTranscription_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif

#ifndef __RhythmParser_h__
#include "RhythmParser.h"
#endif

#ifndef ShDecode_hpp
#include "ShDecode.hpp"
#endif

#ifndef __Modul_h__
#include "Modul.h"
#endif


#include <string>
#include <fstream>
#include <vector>

class LilypondTranscription {
public:
    LilypondTranscription () { sh_dec.SetDecoder (&dec); linevar = "line_"; var_opened = false; s_count = 0; }
    ~LilypondTranscription ();
    
    void open_lily_file (string filename);
    void open_ssh_file (string filename);
    void open_pitch_file (string filename);
    void create_header ();
    void parse_sh (string filename);
    void pass_lines ();
    void create_footer ();
    string create_meter (int pulses);
    
    void create_header2 ();
    void create_variable ();
    void create_ly_book ();
    void write_variable ();
    void create_footer2 ();
    void close_variable ();
    void pass_lines2 ();
    void close_files ();
    
private:
    ifstream sh_file; // sh_file.open (filename.c_str());
    ofstream lily_file;
    ShDecode sh_dec;
    RhythmParser rh_parser;
    Decoder dec;
    vector<vector<string> > matrix; // holding the lines of pitches
    
    vector<string> var_names; // storing variable names
    string linevar;
    bool var_opened;
    vector<int> staff_pitch_beg;
    int s_count;
};

#endif

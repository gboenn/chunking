///////////////////////////////////////////
//  LilypondTranscription.cpp
//
//  Created by Georg Boenn on 2019-10-14.
//  Copyright © 2019 Georg Boenn. All rights reserved.
//  GNU General Public License version 3.0
//  Free Software Foundation
///////////////////////////////////////////

#include "LilypondTranscription.h"

extern vector<string> vrh;

LilypondTranscription::~LilypondTranscription () {
    if (lily_file)
        lily_file.close ();
    if (sh_file)
        sh_file.close ();
}

void LilypondTranscription::open_lily_file (string filename) {
    lily_file.open (filename);
    if (!lily_file) {
        cout << "Error:  Could not open file " << filename << endl;
        return;
    }
}

void LilypondTranscription::open_ssh_file (string filename) {
    sh_file.open (filename);
    if (!sh_file) {
        cout << "Error:  Could not open file " << filename << endl;
        return;
    }
}

void LilypondTranscription::create_header () {
    if (lily_file) {
        lily_file << "\\version \"2.18.2\"" << endl;
        lily_file << "\\header { tagline = \" \" }" << endl;
        lily_file << "\\score {" << endl;
        lily_file << "\\new Staff  { " << endl;
    }
}

void LilypondTranscription::parse_sh (string filename) {
    open_ssh_file (filename); // check whether file exists
    if (sh_file) {
        sh_file.close ();
        rh_parser.process (filename);
    }
//    cout << "---------------" << endl;
//    auto len = vrh.size();
//    for (auto i = 0; i < len; i++) {
//        cout << vrh[i] << endl;
//    }
//    cout << "---------------" << endl;
}

void LilypondTranscription::pass_lines () {
    if (vrh.size() > 0) {
        auto npl = matrix.size (); // number of lines in pitch file
        u_long ln = 0;
        vector<string> shline;
        vector<string> outs;
        auto len = vrh.size();
        cout << endl << endl;
        float prevdur = 0;
        for (auto i = 0; i < len; i++) {
            string item = vrh[i];
            if (item != "newline") {
                shline.push_back (item);
            } else {
                // a new line of snmr code is decoded:
                dec.SetPitchLine (ln++);
                float dur = sh_dec.list_feed (shline, outs);
                //cout << "duration: " << dur << endl;
                if (fabs(prevdur - dur) > 0.01f) {
                    cout << create_meter (dur) << endl;
                    lily_file << create_meter (dur) << endl;
                }
                prevdur = dur;
                auto tlen = outs.size ();
                for (auto k = 0; k < tlen; k++) {
                    cout << outs[k] << endl;
                    lily_file << outs[k] << endl;
                }
                outs.clear();
                shline.clear();
                if (ln == npl) ln = 0;
            }
        }
    }
}

void LilypondTranscription::create_footer () {
    if (lily_file) {
        lily_file << endl << "}" << endl << "\\layout { }" << endl;
        lily_file << "\\midi {\\tempo 8 = 200 }" << endl;
        lily_file << "}" << endl;
    }
}

string LilypondTranscription::create_meter (int pulses) {
    string meter = to_string(pulses) + "/8";
    if (meter == "8/8")
        meter = "4/4";
    return ("\\time " + meter + " ");
}

void LilypondTranscription::open_pitch_file (string filename) {
    
    ifstream file (filename.c_str());
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl; return;
    }
    
    vector<string> row;
    string line;
    string cell;
    
    while (file) {
        getline (file,line);
        stringstream lineStream (line);
        row.clear();
        
        while (getline(lineStream, cell, ',' )) {
            if (cell.find ("$") == string::npos)
                row.push_back (cell);
        }
        
        if (!row.empty ())
            matrix.push_back (row);
    }
    
    dec.SetPitches (matrix);
}


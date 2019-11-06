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
//    if (lily_file)
//        lily_file.close ();
//    if (sh_file)
//        sh_file.close ();
}

void LilypondTranscription::close_files () {
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
        u_long ln = 0; // line counter for pitch lines
        vector<string> shline;
        vector<string> outs;
        auto len = vrh.size();
        cout << endl << endl;
        float prevdur = 0;
        //create new var first time
        for (auto i = 0; i < len; i++) {
            string item = vrh[i];
            if (item != "newline") {
                shline.push_back (item);
                // else if (item == "S") {
                // create new var
                //}
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
                // close_variable ();
                outs.clear();
                shline.clear();
                if (ln == npl) ln = 0;
            }
        }
    }
}

void LilypondTranscription::pass_lines2 () {
    if (vrh.size() > 0) {
        auto npl = matrix.size (); // number of lines in pitch file
        u_long ln = 0; // line counter for pitch lines
        vector<string> shline;
        vector<string> outs;
        auto len = vrh.size();
        cout << endl << endl;
        float prevdur = 0;
        //create new var first time
        create_variable ();
        for (auto i = 0; i < len; i++) {
            string item = vrh[i];
            if (item != "newline") {
                if (item == "S") {
                    if (var_opened)
                        close_variable ();
//                    cout << "create new var" << endl;
                    create_variable ();
                    // advance pitch matrix to line after next S
                    if (s_count < staff_pitch_beg.size ()) {
                        ln = staff_pitch_beg[s_count++];
                        ln++;
                    }
                    continue;
                }
                shline.push_back (item);
            } else {
                // a new line of snmr code is decoded:
                if (ln+1 <= matrix.size()-1) {
                    dec.SetPitchLine (ln++);
                    string curline = matrix[ln][0];
                    if (curline.find ("S") != string::npos) {
                        // check if this pitch line starts with 'S'
                        // if so, reset ln to either th beginning or to the line after previous S
                        // neeed to store the line numbers for the S in the pitchfile in separate vector
                        ln = staff_pitch_beg[s_count];
                    }
                }
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
                if (ln >= matrix.size()) {
                    ln = staff_pitch_beg.back();
                    ln++;
                }
            }
        }
        if (var_opened)
            close_variable ();
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
    if (pulses == 0) {
        return ("\\time 1/16 ");
    }
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
    staff_pitch_beg.clear();
    int line_number = -1;
    while (file) {
        getline (file,line);
        cout << line << endl;
        // ignore empty lines
        if (line == "") {
            continue;
        }
        if (line.find ("$") != string::npos) {
            continue;
        }
        line_number++;
        if (line.find ("S") != string::npos) {
            staff_pitch_beg.push_back (line_number);
            cout << "staff_pitch_beg.push_back " << line_number << endl;
        }
        
        stringstream lineStream (line);
        row.clear();
        
        cout << "line_number " << line_number << endl;
        while (getline(lineStream, cell, ',' )) {
            row.push_back (cell);
//            if (cell.find ("$") == string::npos) {
//                row.push_back (cell);
//                if (cell.find ("S") != string::npos) {
//                    staff_pitch_beg.push_back (line_number);
//                    cout << "staff_pitch_beg.push_back " << line_number << endl;
//                }
//            }
        }
        
        if (!row.empty ()) {
            cout << "row.size " << row.size() << endl;
            matrix.push_back (row);
            cout << "matrix.push_back (row) " << line_number << endl;
            //cout << row.back() << endl;
        }
    }
    
    dec.SetPitches (matrix);
}

void LilypondTranscription::create_header2 () {
    if (lily_file) {
        lily_file << "\\version \"2.18.2\"" << endl;
        lily_file << "\\header { tagline = \" \" }" << endl;
    }
}

void LilypondTranscription::create_variable () {
    int letter = 97;
    int vlen = var_names.size ();
    letter += vlen;
    if (letter > 122) {
        letter = 97;
        linevar += char(letter);
    }
    linevar += char(letter);
    var_names.push_back (linevar);
    if (lily_file) {
        lily_file << linevar << " = {" << endl;
    }
    var_opened = true;
}

void LilypondTranscription::close_variable () {
    lily_file << "}" << endl;
    var_opened = false;
}

void LilypondTranscription::create_ly_book () {
    lily_file << "\\book {" << endl;
    lily_file << "  \\score {" << endl;
    lily_file << "      <<" << endl;
}

void LilypondTranscription::write_variable () {
    auto vlen = var_names.size ();
    for (int i = 0; i < vlen; i++) {
        lily_file << "          \\new Staff  {" << endl;
        lily_file << "              \\new Voice  \\" << var_names[i] << endl;
        lily_file << "          }" << endl;
        
    }
}

void LilypondTranscription::create_footer2 () {
    lily_file << ">>" << endl;
    lily_file << "\\layout { }" << endl;
    lily_file << "\\midi {\\tempo 8 = 200 }" << endl;
    lily_file << "} " << endl;
    lily_file << "\\paper {}" << endl;
    lily_file << "} " << endl;
}


/*

 to do:
 develop gereal LY structure:
 %%%%%%%%%% header
 \version "2.18.2"
 \header { tagline = " " }
 
 %%%%%%%%%% variables
 %%%%%%%%%% naming convention line_a line_b etc. line_z line_aa line_ab etc. line_az
 line_a = { \time 21/8
 d'8 e'4 a'4. b'4.
 ~
 b'4 cis''8[ e''8]
 \tuplet 3/2 {
 d''8 b'8 a'8
 ~
 }
 a'4 e'2 }
 
 %%%%%%%%%%% if there is at least on 'S' in the parsed input
 %%%%%%%%%%%% it means new staff/voice therefore new variable
 line_b = { c'8 c'4 c'4. d'~d'4 e'8 g' ~ g'2 c' }
 
 %%%%%%%%%% create LY book
 \book {
 \score {
 <<
 %%%%%%%%%% for each variable do:
 \new Staff  {
 \new Voice  \line_a
 }
 
 \new Staff  {
 \new Voice  \line_b
 }
 %%%%%%%%% end loop
 %%%%%%%%% add footer:
 >>
 \layout { }
 \midi {\tempo 8 = 200 }
 }
 \paper {}
 }
%%%%%%%%%% EOF
 */

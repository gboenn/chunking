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

LilypondTranscription::~LilypondTranscription () {}

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
    //deprecated use create_header2()
    if (lily_file) {
        lily_file << "\\version \"2.18.2\"" << endl;
        lily_file << "\\header { tagline = \" \" }" << endl;
        lily_file << "\\score {" << endl;
        lily_file << "\\new Staff  { " << endl;
    }
}

void LilypondTranscription::parse_sh (string filename) {
    // invokes the snmr parser with the snmr file
    open_ssh_file (filename); // check whether file exists
    if (sh_file) {
        sh_file.close ();
        rh_parser.process (filename);
    }
}

void LilypondTranscription::pass_lines () {
    // deprecated precursor of pass_lines2()
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
    // new method to process lines in seperate snmr and midi pitch files
    // allows for multiple staves in the score
    if (vrh.size() > 0) {
        int ln = 0; // line counter for pitch lines
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
                if (item == "S") { // rhythm code new staff
                    // the previous staff is closed
                    // and a new staff can start
                    if (var_opened)
                        close_variable ();
                    create_variable ();
                    // advance pitch matrix to line after next S
                    // only process as many pitch staves as there are in the file
                    // after all pitch material has run out, the last pitch line just repeats
                    if (++s_count < staff_pitch_beg.size ()) {
                        ln = staff_pitch_beg[s_count];
                    } else {
                        if (staff_pitch_beg.size () > 1) {
                            // if multiple staves in pitches then repeat last staff's pitches for remaining bars on all remaining staves
                            ln = staff_pitch_beg.back();
                        } else
                            // if no staves in pitches then jump back
                            // results in all staves having same pitches
                            // but they can have different rhythms, and different number of bars
                            ln = 0;
                    }
                    continue;
                }
                shline.push_back (item);
            } else {
                // a new line of snmr code is decoded:
                if (ln < int(matrix.size())) {
                    string curline = matrix[ln][0];
                    if (curline.find ("S") != string::npos) {
                        // check if this pitch line starts with 'S'
                        // meaning new staff has to start
                        // line numbers for the S in the pitchfile are stored in vector staff_pitch_beg
                        if (s_count == staff_pitch_beg.size())
                            s_count = staff_pitch_beg.size()-1;
                        ln = staff_pitch_beg[s_count]+1;
                    }
                    dec.SetPitchLine (ln);
                }
                //cout << automatic_clef (ln) << endl;
                lily_file << automatic_clef (ln) << endl;
                float dur = sh_dec.list_feed (shline, outs);
                //cout << "duration: " << dur << endl;
                if (fabs(prevdur - dur) > 0.01f) {
                    //cout << create_meter (dur) << endl;
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
                ln++;
                if (ln >= matrix.size()) {
                    ln = staff_pitch_beg.back()+1;
                }
            }
        }
        if (var_opened)
            close_variable ();
    }
}


void LilypondTranscription::create_footer () {
    //deperectaed, use create_footer2()
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
    staff_pitch_beg.push_back (line_number);
    while (file) {
        getline (file,line);
        cout << line << endl;
        // ignore empty lines
        if (line == "") {
            continue;
        }
        // ignore lines that are comments
        if (line.find ("$") != string::npos) {
            continue;
        }
        //store the line number where pitch information for a new staff begins
        line_number++;
        if (line.find ("S") != string::npos) {
            staff_pitch_beg.push_back (line_number);
            cout << "staff_pitch_beg.push_back " << line_number << endl;
        }
        
        stringstream lineStream (line);
        row.clear();
        
        //        cout << "line_number " << line_number << endl;
        while (getline(lineStream, cell, ',' )) {
            row.push_back (cell);
        }
        
        if (!row.empty ()) {
            //cout << "row.size " << row.size() << endl;
            matrix.push_back (row);
            //cout << "matrix.push_back (row) " << line_number << endl;
            //cout << row.back() << endl;
        }
    }
    // all rows of pitch data is now in matrix and passed on to the lilypond decoder object
    dec.SetPitches (matrix);
    
//    cout << "++++++++++ matrix ++++++++++++" << endl;
//    auto templen = matrix.size();
//    for (auto i = 0; i < templen; i++) {
//        cout << "vec " << i << ": " << endl;
//        vector<string> tempvec = matrix[i];
//        auto tvlen = tempvec.size();
//        for (auto k = 0; k < tvlen; k++) {
//            cout << tempvec[k] << " ";
//        }
//        cout << endl;
//    }
//    cout << "++++++++++ matrix ++++++++++++" << endl;
}

string LilypondTranscription::automatic_clef (int row) {
// re calculates clef per bar and resets if necessary
    
    // count how many notes are >= 55 and <= 65. If the ratio is 90% set bass clef
    // if treble (default) is set, and note is < 55, set bass clef
    // if bass clef is set, and note is > 65 set treble clef
    
    string clef = "\\clef treble ";
    vector<string> pline = matrix[row];
    vector<float> midi_line;
    auto len = pline.size();
    
    for (auto i = 0; i < len; i++) {
        string curline = pline[i];
        if (curline.find(":") != string::npos) {
            stringstream sstr1 (curline);
            string n;
            // chord tones are separated by ":"
            while (getline (sstr1, n, ':')) {
                midi_line.push_back (atof (n.c_str ()));
            }
        } else {
            midi_line.push_back (atof (curline.c_str ()));
        }
    }
    
    len = midi_line.size();
    int count_hibass_range = 0;
    int count_lobass_range = 0;
    int count_treble_range = 0;
    for (auto i = 0; i < len; i++) {
        int cur = midi_line[i];
        if (cur >= 55 && cur <= 60)
            count_hibass_range++;
        if (cur < 55)
            count_lobass_range++;
        if (cur > 60)
            count_treble_range++;
        //cout << pline[i] << endl;
    }
    float perc = float(count_hibass_range) / float (len);
    float perclo = float(count_lobass_range) / float (len);
    if (perc > 0.89f || perclo > 0.f)
        clef = "\\clef bass ";
    current_clef = clef;
    return clef;
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

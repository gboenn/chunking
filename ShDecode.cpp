//
//  ShDecode.cpp
//  lilypond_encoder
//
//  Created by Georg Boenn on 2019-10-14.
//  Copyright © 2019 Georg Boenn. All rights reserved.
//

#include "ShDecode.hpp"

ShDecode::ShDecode () {
    inv_bin_durs = {4.0, 2.0, 1.0, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.0078125};
    fill_sh_values ();
}

float ShDecode::calculate_length (string& item) {
    float res = 0.0f;
    float factor = 1.f;
    for (auto i = 0; i < divlist.size(); i++) {
        factor *= divlist[i];
    }
    for (auto i = 0; i < item.size(); i++) {
        char c = item[i];
        auto l = sh_durs[c].size();
        for (auto k = 0; k < l; k++) {
            res += (abs(sh_durs[c][k]) / factor);
        }
    }
    cout << res << endl;
    return res;
}

string ShDecode::close_tuplet () {
    return "}";
}

void ShDecode::fill_sh_values () {
    sh_durs['.'] = {1.f};
    sh_durs['I'] = {2.f};
    sh_durs[':'] = {1.f, 1.f};
    sh_durs['v'] = {-1.f, 1.f};
    sh_durs['-'] = {3.f};
    sh_durs['i'] = {1.f, 1.f, 1.f};
    sh_durs['<'] = {-1.f, 2.f};
    sh_durs['w'] = {-2.f, 1.f};
    sh_durs['X'] = {1.f, 2.f};
    sh_durs['>'] = {2.f, 1.f};
    sh_durs['+'] = {-1.f, 1.f, 1.f};
    sh_durs['!'] = {1.f, 3.f};
    sh_durs['H'] = {4.f};
    sh_durs['G'] = {6.f}; // half pointed
    sh_durs['F'] = {7.f}; // double pointed
    
    sh_durs['W'] = {8.f}; // whole
    sh_durs['Q'] = {12.f}; // whole pointed
    sh_durs['E'] = {14.f}; // whole double pointed
    
    sh_durs['B'] = {16.f}; // breve
    sh_durs['L'] = {32.f}; // longa
}

string ShDecode::process_tie () {
    cout << "process_tie " << endl;
    dec->SaveNote ();
    return " ~ ";
    
//    dec->Set(-1);
}

string ShDecode::start_tuplet () {
    int num = divlist.back();
    string res = "";
    int prop = power2below (num);
    // prop has to be greatest power of 2 less than num
    res += "\\tuplet " + to_string(num) + "/" + to_string(prop) + " {";
    return res;
}

string ShDecode::process_silence (string& in) {
    string res; // = "{";
    // prop has to be greatest power of 2 less than num
    auto len = divlist.size();
    int subdiv = 1;
    for (int i = 0; i < len; i++) {
        subdiv *= divlist[i];
    }
    int prop = power2below (subdiv);
    for (auto i = 0; i < in.size(); i++) {
        res += print_lp_values (sh_durs[in[i]], prop, true);
    }
    return res;
}

//string ShDecode::transcribe_sh (string& in) {
//    auto len = divlist.size();
//    int subdiv = 1;
//    for (int i = 0; i < len; i++) {
//        subdiv *= divlist[i];
//    }
//    int prop = power2below (subdiv);
//    string t = transcribe_tuplet (in, prop, sh_durs);
//    return t;
//}

string ShDecode::transcribe_sh (string& in) {
    auto len = divlist.size();
    int subdiv = 1;
    int count_3 = 0;
    for (int i = 0; i < len; i++) {
        int div = divlist[i];
        if (div == 3) {
            count_3++;
        }
        subdiv *= div;
    }
    int prop = power2below (subdiv);
    if ((count_3 > 0) && (divlist[len-2] == 3)) {
        int curdiv = divlist.back();
        if (curdiv == 3 || curdiv == 7 || curdiv == 11 || curdiv == 13) {
            prop *= 0.5;
        }
    }
    //    if (count_3 > 0 && len > 1) {
    //        prop *= 0.5;
    //    }
    string t = transcribe_tuplet (in, prop, sh_durs);
    return t;
}

float ShDecode::list_feed (vector<string>& sh_parsed, vector<string>& outs) {
    float duration = 0.f;
    vector<bool> open_tuplet;
    auto len = sh_parsed.size();
    for (int i = 0; i < len; i++) {
        string item = sh_parsed[i];
        if (item == "[") {
            if (isdigit(sh_parsed[i+1].c_str()[0]) == false) {
                divlist.push_back(2.f);
            } else {
                open_tuplet.push_back (true);
            }
        } else if (item == "]") {
            if (open_tuplet.size() > 0) { 
                outs.push_back(close_tuplet ());
                open_tuplet.pop_back();
            }
            divlist.pop_back();
        } else if (item == "(") {
            duration += calculate_length(sh_parsed[i+1]);
            outs.push_back(process_silence (sh_parsed[i+1]));
            i++;
        } else if (item == ")") {
            ;
        } else if (isdigit(item.c_str()[0])) {
            divlist.push_back(atof(item.c_str()));
            outs.push_back(start_tuplet());
        } else if (item == "~") {
            if (sh_parsed[i+1] == "(") {
                continue;
            }
            if (sh_parsed[i-1] == ")" || sh_parsed[i-1] == "]") {
                continue;
            }
            outs.push_back(process_tie ());
	} else if (item == "S") {
        cout << "NEW STAFF" << endl;
        } else {
            duration += calculate_length(item);
            outs.push_back(transcribe_sh (item));
        }
    }
    return duration;
}

bool ShDecode::isPower2(int x) {
    if (x < 2)
        return false;
    if (x & (x - 1))
        return false;
    return true;
}

int ShDecode::power2below (int x) {
    if (x < 2)
        return 1;
    while (!isPower2 (x)) {
        --x;
    }
    return x;
}

bool ShDecode::find_bin_dur (double dur) {
    if (find (inv_bin_durs.begin (), inv_bin_durs.end (), dur) != inv_bin_durs.end ()) {
        return true;
    } else {
        return false;
    }
}

int ShDecode::find_nearest_dur (double dur) {
    int count = 0;
    for (vector<double>::iterator it = inv_bin_durs.begin() ; it != inv_bin_durs.end(); ++it) {
        if ((*it - dur) < 0.) {
            return count;
        }
        count++;
    }
    return -1;
}

void ShDecode::translate_dur (double dur, double prev, string& lp_note) {
    double frac = dur - (int(dur));
    if (frac < 0.001) {
        dur = int(dur);
    }
    if (find_bin_dur (1./dur)) {
        if (prev == 0.f) {
            if (dur == 0.25) {
                lp_note += "\\longa";
            }
            else if (dur == 0.5) {
                lp_note += "\\breve";
            } else {
                lp_note += to_string(int(dur));
            }
            
        } else {
            if (fabs((dur / prev) - 2.)  < 0.0001) {
                lp_note += ".";
            }
        }
    } else {
        if (fabs((dur / prev) - 1.3333f)  < 0.0001) {
            // this is to process the 7 duration as in double-dotted note values
            // important is the ratio of 4/3
            lp_note += "..";
            return;
        }
        int pos = find_nearest_dur (1./dur);
        if (pos > -1) {
            lp_note += to_string(int(1./inv_bin_durs[pos]));
            //lp_note += " ";
            double dotted_dur1 = (1./dur - inv_bin_durs[pos]);
            translate_dur (1./dotted_dur1, 1./inv_bin_durs[pos], lp_note);
        }
    }
}

#if 0
string ShDecode::print_lp_values (const vector<float>& v, int scale, bool restflag) {
    // translating shorthand pulse values to lilypond score notes
    // scale = 2 halves all note values : quarter => eighth (4 => 8)
    
    if (scale > 1 && !isPower2(scale)) {
        cout << "Warning. " << scale << " is not a power of two." << endl;
    }
    float scale_factor = scale;
    if (scale_factor < 0) {
        scale_factor = pow(2.,scale_factor);
    }
    float wp = 8.f * scale_factor; // whole note in shorthand '.' pulses
    char note = 'c';
    char rest = 'r';
    string res = "";
    
    for (int i = 0; i < v.size(); i++) {
        float dur = wp/v[i];
        string lp_note = "";
        if (restflag) {
            lp_note += rest;
            //dur *= -1.f;
        } else {
            lp_note += note;
        }
        if (dur <= 0.125) {
            cout << "Warning. Note lengths exceeding the 'longa' (4 x whole note) are not supported in tuplets or subdivisions. Use ties between smaller durations in shorthand." << endl;
        }
        translate_dur(dur, 0., lp_note);
        //cout << lp_note << " ";
        res += lp_note;
        res += " ";
    }
    //cout << endl;
    return res;
}
#endif

void ShDecode::manage_group (const vector<float>& v, string& lps, const int& i) {
    int group = v.size();
    if (group == 1) return;
    if (group == 2 && i == 0 && v[0] == 1.f && v[1] == 1.f) {
        lps += "[";
    }
    if (group == 2 && i == 1 && v[0] == 1.f && v[1] == 1.f) {
        lps += "]";
    }
    if (group == 3 && i == 0 && v[0] == 1.f && v[1] == 1.f && v[2] == 1.f) {
        lps += "[";
    }
    if (group == 3 && i == 2 && v[0] == 1.f && v[1] == 1.f && v[2] == 1.f) {
        lps += "]";
    }
    if (group == 3 && i == 1 && v[0] == -1.f && v[1] == 1.f && v[2] == 1.f) {
        lps += "[";
    }
    if (group == 3 && i == 2 && v[0] == -1.f && v[1] == 1.f && v[2] == 1.f) {
        lps += "]";
    }
    
}

string ShDecode::print_lp_values (const vector<float>& v, int scale, bool restflag) {
    // translating shorthand pulse values to lilypond score notes
    // scale = 2 halves all note values : quarter => eighth (4 => 8)
    
    if (scale > 1 && !isPower2(scale)) {
        cout << "Warning. " << scale << " is not a power of two." << endl;
    }
    float scale_factor = scale;
    if (scale_factor < 0) {
        scale_factor = pow(2.,scale_factor);
    }
    float wp = 8.f * scale_factor; // whole note in shorthand '.' pulses
    string note = "c'";
    char rest = 'r';
    string res = "";
    bool shrest = false; //shorthand notation rests
    
    for (int i = 0; i < v.size(); i++) {
        float dur = wp/fabs(v[i]);
        if (v[i] < 0)
            shrest = true;
        else
            shrest = false;
        string lp_note = "";
        if (restflag || shrest) {
            lp_note += rest;
            //dur *= -1.f;
        } else {
            dec->AdvanceNote ();
            note = dec->GetNote ();
            lp_note += note; // use AdvanceNote() and the getNote() to receive lilypond code
        }
        if (dur <= 0.125) {
            cout << "Warning. Note lengths exceeding the 'longa' (4 x whole note) are not supported in tuplets or subdivisions. Use ties between smaller durations in shorthand." << endl;
        }
        translate_dur(dur, 0., lp_note);
        //cout << lp_note << " ";

        manage_group( v, lp_note, i);
        res += lp_note;
        res += " ";
    }
    //cout << endl;
    return res;
}


string ShDecode::transcribe_tuplet (string input, int prop, map<char,vector<float> >& sh_durs) {
    // determine
    string res; // = "{";
    // prop has to be greatest power of 2 less than num
    for (auto i = 0; i < input.size(); i++) {
        res += print_lp_values (sh_durs[input[i]], prop, false);
    }
    //res += "}";
    return res;
}

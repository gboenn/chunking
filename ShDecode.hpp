//
//  ShDecode.hpp
//  lilypond_encoder
//
//  Created by Georg Boenn on 2019-10-14.
//  Copyright © 2019 Georg Boenn. All rights reserved.
//

#ifndef ShDecode_hpp
#define ShDecode_hpp

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>     


using namespace std;

class ShDecode {
public:
    ShDecode ();
    ~ShDecode () {}
    
    float calculate_length (string& item);
    string close_tuplet ();
    void fill_sh_values ();
    bool find_bin_dur (double dur);
    int find_nearest_dur (double dur);
    bool isPower2(int x);
    float list_feed (vector<string>& sh_parsed, vector<string>& outs);
    int power2below (int x);
    string print_lp_values (const vector<float>& v, int scale, bool restflag);
    string process_silence (string& in);
    string process_tie ();
    string start_tuplet ();
    string transcribe_sh (string& in);
    string transcribe_tuplet (string input, int prop, map<char,vector<float> >& sh_durs);
    void translate_dur (double dur, double prev, string& lp_note);
    
private:
    
    map<char,vector<float> > sh_durs;
    vector<double> inv_bin_durs;
    vector<float> divlist;
    
};

#endif /* ShDecode_hpp */

///////////////////////////////////////////
// PitchParser.cpp
// Copyright (C) 2018, 2019 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __PitchParser_h__
#include "PitchParser.h"
#endif

#include <sstream>

void PitchParser::process (vector<vector<float> > &p, string pitches) {
    stringstream aline (pitches);
    string cell;
    while (getline (aline, cell, ',')) {
        stringstream aline2 (cell);
        string cell2;
        vector<float> p2;
        size_t found2 = cell.find(":");
        if (found2 != string::npos) {
            while (getline (aline2, cell2, ':')) {
                p2.push_back (atof (cell2.c_str()));
            }
        } else {
            p2.push_back (atof(cell.c_str()));
        }
        p.push_back (p2);
    }
}

int PitchParser::check (string pitches) {
    size_t found = pitches.find (",");
    if (found != string::npos)
        return 1;
    else {
        cout << "Error: input pitches are strings of MIDI note numbers (float or int) seperated by commas." << endl;
        return 0;
    }
}

///////////////////////////////////////////
// RhythmParser.cpp
// Copyright (C) 2018, 2019 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "RhythmParser.h"
#include "TextIO.h"
#include <vector>

void RhythmParser::process (string filename) {
    vrh.clear ();
    if (!(yyin = fopen(filename.c_str(), "r"))) {
        cout << "RhythmParser says: error opening " << filename << endl;
    }
    yyparse();
}

void RhythmParser::parse_snmr_line (string rhythm) {
    StringToFile f ("_mutation_temp.txt");
    //f.Append(s2.str());
    f.Append(rhythm);
    process ("_mutation_temp.txt");
}

void RhythmParser::detect_snmr (vector<unsigned long>& occurence, vector<unsigned long>& tilde) {
    if (vrh.size() > 0) {
        auto len = vrh.size();
        for (auto i = 0; i < len; i++) {
            string item = vrh[i];
            if (item == "newline") {
                continue;
            }
            if (item == "[") {
                continue;
            } else if (item == "]") {
                continue;
            } else if (item == "(") {
                continue;
            } else if (item == ")") {
                continue;
            } else if (isdigit(item.c_str()[0])) {
                continue;
            } else if (item == "~") {
                tilde.push_back(i);
            } else if (item == "S") {
                continue;
            } else {
//                cout << "detect " << vrh[i] << endl;
                 occurence.push_back(i);
            }
        }
    }
}

void RhythmParser::render_online_string (string& result) {
    int len = vrh.size();
    result = "";
    for (int i = 0; i < len; i++){ // go through parsed snmr
        string temp = vrh[i];
        if (temp == "newline") { // ignore newlines and new staves because of single line input
            continue;
        }
        if (temp == "S") {
            continue;
        }
        result += temp;
    }
}

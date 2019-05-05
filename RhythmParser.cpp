///////////////////////////////////////////
// RhythmParser.cpp
// Copyright (C) 2018, 2019 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "RhythmParser.h"

void RhythmParser::process (string filename) {
    if (!(yyin = fopen(filename.c_str(), "r"))) {
        cout << "RhythmParser says: error opening " << filename << endl;
    }
    yyparse();
    vrh.clear ();
}

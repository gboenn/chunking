///////////////////////////////////////////
// RhythmParser.h
// Copyright (C) 2018, 2019 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __RhythmParser_h__
#define __RhythmParser_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern vector<string> vrh;

class RhythmParser {
 public:
  RhythmParser () {}
  ~RhythmParser () {}

  void process (string filename);
    void parse_snmr_line (string rhythm);
    void detect_snmr (vector<int>& occurence, vector<int>& tilde);
    void render_online_string (string& result);
};


#endif // __RhythmParser_h__

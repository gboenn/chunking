///////////////////////////////////////////
// PitchParser.h
// Copyright (C) 2018, 2019 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __PitchParser_h__
#define __PitchParser_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif

#include <vector>

class PitchParser {
public:
    PitchParser () {}
    ~PitchParser () {}
    
    int check (string pitches);
    void process (vector<vector<float> > &p, string pitches);
    
};


#endif // __PitchParser_h__

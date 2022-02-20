///////////////////////////////////////////
// Mutations.h
// Copyright (C) 2018-2019 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef    __Mutations_h__
#define    __Mutations_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif


class Mutations {

public:
    Mutations () {};
    ~Mutations () {};
    string Jumping (string rhythm, unsigned long n, int k, int flag);
    string Fragment (string rhythm);
    string Rotation (string rhythm);
    string Mutation (string rhythm, unsigned long n);
    string Swap (string rhythm, unsigned long n);
    string Reverse ();
    string Silence (string rhythm, unsigned long n, unsigned long k);
    string ProcessToShapes (string rhythm, int flag);
    unsigned long CloseBracketInd (unsigned long index);
    unsigned long CloseSilenceBracketInd(unsigned long index);
    void ReverseBrackets(unsigned long openb, unsigned long closb);
    bool isNum (string line);
};
#endif // __Mutations_h__

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
    string Jumping (string rhythm, int n, int k, int flag);
    string Fragment (string rhythm);
    string Rotation (string rhythm);
    string FragmentRotation (string rhythm);
    string Mutation (string rhythm, int n);
    string Swap (string rhythm, int n);
    string Reverse (string rhythm);
    string Silence (string rhythm, int n, int k);
    string ProcessToShapes (string rhythm, int flag);
    int CloseBracketInd (int index);
    int CloseSilenceBracketInd(int index);
    void ReverseBrackets(int openb, int closb);
    bool isNum (string line);
};
#endif // __Mutations_h__

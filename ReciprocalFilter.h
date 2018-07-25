///////////////////////////////////////////
// ReciprocalFilter.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef ReciprocalFilter_h
#define ReciprocalFilter_h

#include "DList.h"
#include "Farey.h"
#include "Visitor.h"
#include "Alea.h"
#include "SternBrocot.h"

class ReciprocalFilter : public Visitor {

 public:

    ReciprocalFilter (); 
    virtual ~ReciprocalFilter (); 
    virtual void Visit (Farey& f, int=0);
    virtual void Visit (SternBrocot& s);
    virtual DLink<Ratio>* GetRatios(); 
    virtual void Clear ();
    virtual int GetFareySeqLength () const { return ratios->GetSize (); }
    virtual void PostCalc (Farey* f);
    virtual void OverrideFareyRatios (Farey* f) { }
    virtual DList<Ratio>* GetRatioList () const { return ratios; }
    virtual int FilterReciprocalNumbers (int t);

 protected:
    DList<Ratio>* ratios;

};
#endif

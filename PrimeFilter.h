///////////////////////////////////////////
// PrimeFilter.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef PrimeFilter_h
#define PrimeFilter_h

#include "DList.h"
#include "Farey.h"
#include "Visitor.h"
#include "Alea.h"

class PrimeFilter : public Visitor {

 public:

    PrimeFilter (); 
    virtual ~PrimeFilter (); 
    virtual void Visit (Farey& f, int=0);
    virtual void Visit (SternBrocot&) {};
    virtual DLink<Ratio>* GetRatios(); 
    virtual void SetFilterVal (float t) { m_FilterValue = t; }
    virtual void Clear ();
    virtual int GetFareySeqLength () const { return ratios->GetSize (); }
    virtual void PostCalc (Farey* f);
    virtual void OverrideFareyRatios (Farey* f) { }
    virtual DList<Ratio>* GetRatioList () const { return ratios; }
 protected:
    DList<Ratio>* ratios;
    float m_FilterValue;

};
#endif

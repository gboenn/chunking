#ifndef SmoothFilter_h
#define SmoothFilter_h

#include "DList.h"
#include "Farey.h"
#include "Visitor.h"
#include "Alea.h"
#include "SternBrocot.h"

class SmoothFilter : public Visitor {

 public:

    SmoothFilter (); 
    virtual ~SmoothFilter (); 
    virtual void Visit (Farey& f, int=0);
    virtual void Visit (SternBrocot& s);
    virtual DLink<Ratio>* GetRatios(); 
    virtual void SetFilterVal (int t) { m_FilterValue = t; }
    virtual void Clear ();
    virtual int GetFareySeqLength () const { return ratios->GetSize (); }
    virtual void PostCalc (Farey* f);
    virtual void OverrideFareyRatios (Farey* f) { }
    virtual DList<Ratio>* GetRatioList () const { return ratios; }
    virtual int FilterSmoothNumbers (int testval);

 protected:
    DList<Ratio>* ratios;
    int m_FilterValue;

};
#endif

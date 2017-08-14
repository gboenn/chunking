#ifndef SubdivisionFilter_h
#define SubdivisionFilter_h

#include "DList.h"
#include "Farey.h"
#include "Visitor.h"
#include "Alea.h"
#include "SternBrocot.h"

class SubdivisionFilter : public Visitor {

 public:

    SubdivisionFilter (); 
    virtual ~SubdivisionFilter (); 
    virtual void Visit (Farey& f, int=0);
    virtual void Visit (SternBrocot& s);
    virtual DLink<Ratio>* GetRatios(); 
    virtual void SetFilterVal (DList<int>* subl) { subdivs = subl; }
    virtual void Clear ();
    virtual int GetFareySeqLength () const { return ratios->GetSize (); }
    virtual void PostCalc (Farey* f);
    virtual void OverrideFareyRatios (Farey* f) { }
    virtual DList<Ratio>* GetRatioList () const { return ratios; }
    virtual void FilterSubdivisions ();

 protected:
    DList<Ratio>* ratios;
    DList<int>* subdivs;
    Farey* farey;

};
#endif

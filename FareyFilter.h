#ifndef FareyFilter_h
#define FareyFilter_h

#include "DList.h"
#include "Farey.h"
#include "Visitor.h"


class FareyFilter : public Visitor {

 public:

    FareyFilter (); 
    virtual ~FareyFilter (); 
    virtual void Visit (Farey& f, int=0);
    virtual void Visit (SternBrocot&) {};
    virtual DLink<Ratio>* GetRatios(); 
    virtual void SetFilterVal (float t) { m_FilterValue = t; }
    virtual void Clear ();
    virtual int GetFareySeqLength () const { return ratios->GetSize (); }
    virtual void PostCalc (Farey* f);
    virtual void OverrideFareyRatios (Farey* f) { }
    virtual DList<Ratio>* GetRatioList () const { return ratios;} 
    virtual void SetNegative (int n=0) { negative = n; }
    virtual Farey* GetVisited () const { return visited; }
    virtual void UpdateScalings (Farey* f);
 protected:
    DList<Ratio>* ratios;
    float m_FilterValue;
    int negative;
    Farey* visited;
};
#endif

///////////////////////////////////////////
// ProbFilter.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "ProbFilter.h"
#include "AlgoComp.h"
#include "Alea.h"

ProbFilter::ProbFilter ()
{
    ratios = new DList<Ratio>;
}

ProbFilter::~ProbFilter ()
{
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
}

void ProbFilter::Visit(Farey &f, int norm)
{
    Alea a;
    DLink<Ratio>* r;  
    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	Farey* s = r->data->GetSubdiv ();
	if (s)
	    s->Accept (*this);
	else
	    if (a.Uniform (0., 1.) <= m_FilterValue)
	    	ratios->append (r->data); 
    } 
    PostCalc (&f);
}

DLink<Ratio>* ProbFilter::GetRatios()
{
    return ratios->first ();
}

void ProbFilter::Clear ()
{
    ratios->destroy ();
}

void ProbFilter::PostCalc (Farey* f)
{
    // set scaling for all Ratios in ratios*
    // scaled by scaling in Farey*
    float scaling = f->GetScaling ();
    DLink<Ratio>* r = ratios->first ();
    for (; r != NULL; r = r->next)
    {
	if (r->next)
	{
	    scaling =  r->next->data->GetFloat () - r->data->GetFloat ();
	    r->data->SetScaling (scaling);
	}
    }
}

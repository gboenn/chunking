///////////////////////////////////////////
// PrimeFilter.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "PrimeFilter.h"
#include "AlgoComp.h"
//#include "smoothtab.h"

PrimeFilter::PrimeFilter ()
{
    ratios = new DList<Ratio>;
}

PrimeFilter::~PrimeFilter ()
{
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
}

void PrimeFilter::Visit(Farey &f, int norm)
{
    DLink<Ratio>* r;  
    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	Farey* s = r->data->GetSubdiv ();
	if (s)
	    s->Accept (*this);
	else
	    if (Digest (r->data->GetQ ()) <= m_FilterValue) 
	    	ratios->append (r->data); 
    } 
    PostCalc (&f);
}

DLink<Ratio>* PrimeFilter::GetRatios()
{
    return ratios->first ();
}

void PrimeFilter::Clear ()
{
    ratios->destroy ();
}

void PrimeFilter::PostCalc (Farey* f)
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

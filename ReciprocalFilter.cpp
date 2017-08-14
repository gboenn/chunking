#include "ReciprocalFilter.h"
#include "AlgoComp.h"

ReciprocalFilter::ReciprocalFilter ()
{
    ratios = new DList<Ratio>;
}

ReciprocalFilter::~ReciprocalFilter ()
{
#if 0
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
#endif
}

void ReciprocalFilter::Visit(Farey &f, int norm)
{
    DLink<Ratio>* r;  
    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	Farey* s = r->data->GetSubdiv ();
	if (s)
	    s->Accept (*this);
	else
	    if (FilterReciprocalNumbers (r->data->GetP ())) 
	    	ratios->append (r->data); 
    }
    PostCalc (&f);
}

void ReciprocalFilter::Visit(SternBrocot &s)
{
    DLink<Ratio>* r;  
    for (r = s.GetFirst (); r != NULL; r = r->next) 
    { 
	if (FilterReciprocalNumbers (r->data->GetQ ())) 
	    ratios->append (r->data); 
    }
}

DLink<Ratio>* ReciprocalFilter::GetRatios()
{
    return ratios->first ();
}

void ReciprocalFilter::Clear ()
{
    ratios->destroy ();
}

void ReciprocalFilter::PostCalc (Farey* f)
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

int ReciprocalFilter::FilterReciprocalNumbers (int t) 
{ 
    if (t == 1)
	return 1;
    return 0;
} 


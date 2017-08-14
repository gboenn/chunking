#include "FareyFilter.h"
#include "AlgoComp.h"

FareyFilter::FareyFilter ()
{
    ratios = new DList<Ratio>;
    SetNegative (0);
}

FareyFilter::~FareyFilter ()
{
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
}

void FareyFilter::Visit(Farey &f, int norm)
{
    DLink<Ratio>* r;  
    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	Farey* s = r->data->GetSubdiv ();
	if (s)
	    s->Accept (*this);
	else
	    if (!negative)
	    {
		if (Digest (r->data->GetQ ()) <= m_FilterValue) 
		    ratios->append (r->data);
	    }
	    else
	    {
		if (Digest (r->data->GetQ ()) > m_FilterValue) 
		    ratios->append (r->data);
	    }    
    } 
    visited = &f;
    PostCalc (visited);
}

DLink<Ratio>* FareyFilter::GetRatios()
{
    return ratios->first ();
}

void FareyFilter::Clear ()
{
    ratios->destroy ();
}

void FareyFilter::PostCalc (Farey* f)
{
//    cout << "PostCalc called in " << f << endl;
    // set scaling for all Ratios in ratios*
    // scaled by scaling in Farey*
    float scaling = f->GetScaling ();
    DLink<Ratio>* r = ratios->first ();
    for (; r != NULL; r = r->next)
    {
	if (r->next)
	{
	    if (f->GetParent ())
		scaling =  r->next->data->GetFloat () - r->data->GetFloat ();
	    r->data->SetScaling (scaling);
	}
    }
}

void FareyFilter::UpdateScalings (Farey* f)
{
    // this is needed because ratios is a new list of Ratios
    // that is likely to be different from the one in Farey* f
//    cout << "UpdateScalings called in FareyFilter " << this << endl;
    // set scaling for all Ratios in ratios*
    // scaled by scaling in Farey*
    float scaling = f->GetScaling ();
    DLink<Ratio>* r = ratios->first ();
    for (; r != NULL; r = r->next)
    {
	if (r->next)
	{
	    // we know that we have to update // if (GetParent ())
	    scaling =  r->next->data->GetFloat () - r->data->GetFloat ();
	    r->data->SetScaling (scaling);
	}
    }
}



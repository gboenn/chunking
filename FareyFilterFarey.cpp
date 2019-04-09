///////////////////////////////////////////
// FareyFilterFarey.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "FareyFilterFarey.h"
#include "chunking_Standards.h"

FareyFilterFarey::FareyFilterFarey ()
{
    ratios = new DList<Ratio>;
}

FareyFilterFarey::~FareyFilterFarey ()
{
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
}

void FareyFilterFarey::Visit(Farey &f, int n)
{
    Farey* nf = new Farey;
    nf->CreateFareySeq (m_FilterValue);
    nf->PrintFareySeq ();

    DLink<Ratio>* r;  
    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	Farey* s = r->data->GetSubdiv ();
	if (s)
	    s->Accept (*this);
	else
	{
	    DLink<Ratio>* rt = nf->GetFirst (); 
	    for (; rt != NULL; rt = rt->next)
	    {
//		cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) <<  " == " << (rt->data->GetP ()) << "/" << (rt->data->GetQ ()) << endl;
		if (*r->data == *rt->data)
		{
		    //	    cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) <<  " == " << (rt->data->GetP ()) << "/" << (rt->data->GetQ ()) << endl;
		    f.GetRatioList ()->removeElement (r->data);
		    break;
		}
	    }
	}
    } 

    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	ratios->append (r->data);
    }
    //PostCalc (&f);
}

DLink<Ratio>* FareyFilterFarey::GetRatios()
{
    return ratios->first ();
}

void FareyFilterFarey::Clear ()
{
    ratios->destroy ();
}

void FareyFilterFarey::PostCalc (Farey* f)
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

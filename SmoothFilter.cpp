#include "SmoothFilter.h"
#include "AlgoComp.h"

extern int mult_11[41];
extern int smooth2[19];
extern int smooth2_3[41];
extern int smooth2_3_5[87];
extern int smooth2_3_5_7[143];
enum {
	s2,
	s2_3,
	s2_3_5,
	s2_3_5_7
};

SmoothFilter::SmoothFilter ()
{
    ratios = new DList<Ratio>;
}

SmoothFilter::~SmoothFilter ()
{
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
}

void SmoothFilter::Visit(Farey &f, int norm)
{
    DLink<Ratio>* r;  
    for (r = f.GetFirst (); r != NULL; r = r->next) 
    { 
	Farey* s = r->data->GetSubdiv ();
	if (s)
	    s->Accept (*this);
	else
	    if (FilterSmoothNumbers (r->data->GetQ ())) 
	    	ratios->append (r->data); 
    }
    PostCalc (&f);
}

void SmoothFilter::Visit(SternBrocot &s)
{
    DLink<Ratio>* r;  
    for (r = s.GetFirst (); r != NULL; r = r->next) 
    { 
	if (FilterSmoothNumbers (r->data->GetQ ())) 
	    ratios->append (r->data); 
    }
}

DLink<Ratio>* SmoothFilter::GetRatios()
{
    return ratios->first ();
}

void SmoothFilter::Clear ()
{
    ratios->destroy ();
}

void SmoothFilter::PostCalc (Farey* f)
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

int SmoothFilter::FilterSmoothNumbers (int testval) 
{ 
	int leng = 0; 
	int i = 0; 
	switch (m_FilterValue) { 
		case s2: 
			leng = sizeof (smooth2) / sizeof (int); 
			for (; i < leng; i++) 
			{ 
				if (testval == smooth2[i]) 
					return 1; 
			} 
			return 0; 
		case s2_3: 
			leng = sizeof (smooth2_3) / sizeof (int); 
			for (; i < leng; i++) 
			{ 
				if (testval == smooth2_3[i]) 
					return 1; 
			} 
			return 0; 
		case s2_3_5: 
			leng = sizeof (smooth2_3_5) / sizeof (int); 
			for (; i < leng; i++) 
			{ 
				if (testval == smooth2_3_5[i]) 
					return 1; 
			} 
			return 0; 
		case s2_3_5_7: 
			leng = sizeof (smooth2_3_5_7) / sizeof (int); 
			for (; i < leng; i++) 
			{ 
				if (testval == smooth2_3_5_7[i]) 
					return 1; 
			} 
			return 0; 
		default: return 0; 
	} 
} 


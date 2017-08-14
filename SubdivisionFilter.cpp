#include "SubdivisionFilter.h"
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

SubdivisionFilter::SubdivisionFilter ()
{
    ratios = new DList<Ratio>;
}

SubdivisionFilter::~SubdivisionFilter ()
{
    if (ratios)
    {
	ratios->destroy ();
	delete ratios;
    }
}

void SubdivisionFilter::Visit(Farey &f, int norm)
{
    farey = &f;
    FilterSubdivisions ();
}

void SubdivisionFilter::Visit(SternBrocot &s)
{
    
}

DLink<Ratio>* SubdivisionFilter::GetRatios()
{
    return ratios->first ();
}

void SubdivisionFilter::Clear ()
{
    ratios->destroy ();
}

void SubdivisionFilter::PostCalc (Farey* f)
{

}

void SubdivisionFilter::FilterSubdivisions () 
{ 
	DLink<Ratio>* r1 = farey->GetFirst (); 
    
    DLink<int>* sl = subdivs->first ();
	
	for (r1 = farey->GetFirst (); r1 != NULL; r1 = r1->next)
	{
		for (sl = subdivs->first (); sl !=NULL; sl = sl->next)
		{
			int i = *sl->data;
			int q = r1->data->GetQ ();
			if (q > 1) {
				if ((i == q) || !(i % q)) {
					DLink<Ratio>* col = ratios->first ();
					int flag = 1;
					int p = r1->data->GetP ();
					for (; col != NULL; col = col->next) {
						if (p == col->data->GetP() && q == col->data->GetQ ())
							flag = 0;
					}
					if (flag)
						ratios->append (r1->data);
				}
			}
			
		}
	}
	
} 

#if 0
void SubdivisionFilter::FilterSubdivisions () 
{ 

    DList<int>* marks = new DList<int>;
    DLink<Ratio>* r1 = farey->GetFirst (); 
    
    for (; r1 != NULL; r1 = r1->next)
    {
	marks->append (new int(0));
    }

    int i = 1;
    int farey_index = farey->GetFareyIndex ();
    for (; i <= farey_index; i++)
    {
		int isin = 0;
		DLink<int>* sl = subdivs->first ();
		for (; sl !=NULL; sl = sl->next)
		{
			if (i == *sl->data)
				isin = 1;
		}
	
		if (isin)
		{
			DLink<Ratio>* r1 = farey->GetFirst (); 
			DLink<int>* m1 = marks->first ();
			for (; r1 != NULL; r1 = r1->next, m1 = m1->next)
			{
				int q = r1->data->GetQ ();
				if (q == i || !(i % q))
				{
					*m1->data = 1;
				}
			}
		}
    }

    DLink<int>* m1 = marks->first ();
    r1 = farey->GetFirst ();
    for (; m1!=NULL; m1 = m1->next, r1 = r1->next)
    {
	if (*m1->data)
	    ratios->append (r1->data);
    }

    marks->destroy ();
} 

#endif
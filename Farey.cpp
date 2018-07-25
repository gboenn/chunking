///////////////////////////////////////////
// Farey.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "Farey.h" 
#include "AlgoComp.h" 

#include "gc_switch_ssh.h"
#if BOEHM_GC_SWITCH
#define GC_THREADS
//#include "gc/gc_alloc.h"
#include "gc.h"
//#include "gc_cpp.h"

inline void * operator new(size_t n) { return GC_malloc(n); }
inline void operator delete(void *) {}
inline void * operator new[](size_t n) { return GC_malloc(n); }
inline void operator delete[](void *) {}
#endif

 
 
Farey::Farey()  
{ 
    
	m_FareySeq = new DList<Ratio>; 
	m_FareyDiffList = new DList<Ratio>; 
	m_FareyCommonDenomList = new DList<Ratio>; 
	Init (); 
	parent = NULL;
	scaling = 1.f;
	m_inverse = 0;
} 
 
Farey::~Farey() 
{ 
	delete m_FareySeq; 
	delete m_FareyDiffList; 
	delete m_FareyCommonDenomList; 
} 
 
void Farey::Init () 
{ 
	m_FareySeq->destroy (); 
	Ratio* r1 = new Ratio (0,1); 
	Ratio* r2 = new Ratio (1,1); 
	m_FareySeq->append (r1); 
	m_FareySeq->append (r2); 
	m_FareyIndex = 1; 
} 

void Farey::Multiply (Ratio* r)
{
    DLink<Ratio>* rf = m_FareySeq->first ();
    for (; rf != NULL; rf = rf->next) 
    {
	float p = rf->data->GetP ();
	rf->data->SetP (p * r->GetP ());
	float q = rf->data->GetQ ();
	rf->data->SetQ (q * r->GetQ ());
    }
}
 
void Farey::CreateFareySeq (int i) 
{ 
	if (i <= 1) 
		return; 
	 
	Init (); 
 
	int k = 1; 
	int stop = m_FareySeq->GetSize (); 
	int m = 0; 
	int insert_index; 
	for (; k < i; k++) 
	{ 
		DLink<Ratio>* r1 = m_FareySeq->first (); 
		DLink<Ratio>* r2 = r1->next; 
 
		stop = m_FareySeq->GetSize () - 1; 
		for (m = 0; m < stop; m++) 
		{ 
			if ((r1->data->GetQ () + r2->data->GetQ ()) <= i) 
			{ 
				Ratio* r3 = new Ratio (); 
				r3->Median (*(r1->data), *(r2->data)); 
				insert_index = m_FareySeq->getPos (r2->data) - 1; 
				r1 = r1->next; 
				r2 = r2->next; 
				m_FareySeq->insertAt (insert_index, r3); 
			} 
			else 
			{ 
				r1 = r1->next; 
				r2 = r2->next; 
			} 
			 
		} 
		m_FareyIndex++; 
 
	} 
	if (m_inverse)
	{
	    DLink<Ratio>* r1 = m_FareySeq->last ();
	    int len = GetFareySeqLength () - 2;
	    r1 = r1->previous;
	    int i = 0;
	    for (; i<len; i++, r1 = r1->previous) 
	    {
		m_FareySeq->append (new Ratio ((r1->data->GetQ ()), (r1->data->GetP ())));
	    }
	}
} 
	 

void Farey::AddInverse ()
{
    DLink<Ratio>* r1 = m_FareySeq->last ();
    int len = GetFareySeqLength () - 1;
    r1 = r1->previous;
    int i = 0;
    for (; i<len; i++, r1 = r1->previous) 
    {
	if (r1->data->GetP () == 0)
	    continue;
	m_FareySeq->append (new Ratio ((r1->data->GetQ ()), (r1->data->GetP ())));
    }
}
 
void Farey::PrintFareySeq () 
{ 
	cout << endl; 
	cout << "Farey Sequence (" << m_FareyIndex << ") : Length (" << (m_FareySeq->GetSize ()) << ")"; 
	cout << endl << endl; 
	DLink<Ratio>* r1 = m_FareySeq->first (); 
	for (; r1 != NULL; r1 = r1->next) 
		cout << setw(8) << (r1->data->GetP ()) << " / " << (r1->data->GetQ ()) << endl; 
 
}

void Farey::PrintFareyLatticePoints () 
{ 
	DLink<Ratio>* r1 = m_FareySeq->first (); 
	for (; r1 != NULL; r1 = r1->next) 
	    cout << (r1->data->GetP ()) << " " << (r1->data->GetQ ()) << endl; 
}

void Farey::PrintFareyTree ()
{
    string empty = "";
    //string space = "x"; string divis = "/";
    string space = " ";  string divis = "+";
    int i = 1;
    for (; i <= m_FareyIndex; i++)
    {
	DLink<Ratio>* r1 = m_FareySeq->first (); 
	for (; r1 != NULL; r1 = r1->next)
	{
	    empty = "";
	    int p = r1->data->GetP ();
	    if (p < 10) empty += space;
	    if (p > 9) empty += space + space;
	    empty += divis;
	    int q = r1->data->GetQ ();
	    if (q < 10) empty += space;
	    if (q > 9) empty += space + space;
	    empty += " ";
	    if (q == i)
		cout << p << "/" << q << " ";
	    else
		cout << empty;
	}
	cout << endl;
    }
} 

void Farey::PrintFareyResonances (int f)
{
    if (f > m_FareyIndex)
	return;

    //    int i = 1;
    DLink<Ratio>* r1 = m_FareySeq->first (); 
    for (; r1 != NULL; r1 = r1->next)
    {
	int p = r1->data->GetP ();
	int q = r1->data->GetQ ();
	if (q == f || !(f % q))
	{
	    cout << p << "/" << q << " ";
	}
	else
	    cout << "    ";
    }
    cout << endl;
    
}

void Farey::PrintFareyResonances ()
{
    string empty = "";
    //string space = "x"; string divis = "/";
    string space = " ";  string divis = "+";
    int i = 1;
    for (; i <= m_FareyIndex; i++)
    {
	DLink<Ratio>* r1 = m_FareySeq->first (); 
	for (; r1 != NULL; r1 = r1->next)
	{
	    empty = "";
	    int p = r1->data->GetP ();
	    if (p < 10) empty += space;
	    if (p > 9) empty += space + space;
	    empty += divis;
	    int q = r1->data->GetQ ();
	    if (q < 10) empty += space;
	    if (q > 9) empty += space + space;
	    empty += " ";
	    if (q == i || !(i % q))
	    {
		cout << p << "/" << q << " ";
	    }
	    else
		cout << empty;

	}
	cout << endl;
    }
}
 
void Farey::CreateDiffList () 
{ 
	m_FareyDiffList->destroy ();
	DLink<Ratio>* r1; 
	 
	for (r1 = m_FareySeq->first (); r1 != NULL && r1->next != NULL; r1 = r1->next) 
	{ 
		Ratio* d = new Ratio (1,1); 
		d->SetQ ((r1->data->GetQ ()) * (r1->next->data->GetQ ())); 
		m_FareyDiffList->append (d); 
	} 
} 
 
#if 0 
int Farey::GetLCDOfDiffList () 
{ 
	DLink<Ratio>* r1; 
	DList<Power>* prime_factors = new DList<Power>; 
 
	for (r1 = m_FareyDiffList->first (); r1 != NULL; r1 = r1->next) 
		PrimFaktoren (r1->data->GetQ (), *prime_factors); 
 
	DList<Power>* max_prime_factors = new DList<Power>; 
	DLink<Power>* p1; 
	int i = 0; 
	for (; i < MAX_PRIMES; i++) 
	{ 
		Power cur_pow; // p^q 
		cur_pow.SetP (primes[i]); 
		cur_pow.SetQ (0); 
		for (p1 = prime_factors->first (); p1 != NULL; p1 = p1->next) 
		{ 
			if (p1->data->GetP () == cur_pow.GetP ()) 
				if (p1->data->GetQ () > cur_pow.GetQ ()) 
					cur_pow.SetQ (p1->data->GetQ ()); 
			 
		} 
		if (cur_pow.GetQ ()) 
		{ 
			Power* p = new Power; 
			p->SetP (cur_pow.GetP ()); 
			p->SetQ (cur_pow.GetQ ()); 
			max_prime_factors->append (p); 
		} 
	 
	} 
 
	DLink<Power>* mp; 
	int result = 1; 
	for (mp = max_prime_factors->first (); mp != NULL; mp = mp->next) 
		result *= mp->data->GetVal (); 
	delete prime_factors; 
	delete max_prime_factors; 
 
	return result; 
 
} 
#endif 
 
void Farey::CreateCommonDenomList () 
{ 
	m_FareyCommonDenomList->destroy ();
	int cd = GetLCDOfRatioList (*m_FareyDiffList); 
	DLink<Ratio>* r1; 
	 
	for (r1 = m_FareyDiffList->first (); r1 != NULL; r1 = r1->next) 
	{ 
		Ratio* r0 = new Ratio (); 
		r0->SetP (cd / (r1->data->GetQ ())); 
		r0->SetQ (cd); 
		m_FareyCommonDenomList->append (r0); 
	} 
} 

void Farey::CreateCommonDenomList2 () 
{ 
	m_FareyDiffList->destroy ();
	m_FareyCommonDenomList->destroy ();
	//int cd = GetLCDOfRatioList (*m_FareyDiffList); 
	DLink<Ratio>* r1; 
	Ratio* r2 = new Ratio ();
	for (r1 = m_FareySeq->first (); r1->next != NULL; r1 = r1->next) 
	{ 
		Ratio* r0 = new Ratio (); 
		r0->SetP (r1->data->GetP ()); 
		r0->SetQ (r1->data->GetQ ());
		r2->SetP (r1->next->data->GetP ()); 
		r2->SetQ (r1->next->data->GetQ ());
		*r0 = *r2 - *r0;
		r0->AutoReduce ();
		m_FareyDiffList->append (r0); 
	} 
	
	comdenom = GetLCDOfRatioList (*m_FareyDiffList); 
	//cout << "com denom = " << cd;
	for (r1 = m_FareyDiffList->first (); r1 != NULL; r1 = r1->next) 
	{
		int p = r1->data->GetP ();
		int q = r1->data->GetQ ();
		int qfac = comdenom / q;
		p *= qfac;
		Ratio* r0 = new Ratio ();
		r0->SetP (p);
		r0->SetQ (comdenom);
		m_FareyCommonDenomList->append (r0);
	}
	
	delete r2;
}
 
 
void Farey::Accept (Visitor& v, int norm) 
{ v.Visit(*this, norm); } 

void Farey::SetScaling (float scaling)
{ 
//    cout << "in Farey::SetScaling " << "(" << scaling << ")" << endl;
    this->scaling = scaling;
    DLink<Ratio>* r = GetFirst ();
    for (; r != NULL; r = r->next)
    {
//	cout << r->data << " Ratio gets scaled " << endl;
	r->data->SetScaling (scaling);
    }
} 

void Farey::UpdateScalings ()
{
    cout << "UpdateScalings called in Farey " << this << endl;
    // set scaling for all Ratios in ratios*
    // scaled by scaling in Farey*
    float scaling = GetScaling ();
    DLink<Ratio>* r = GetFirst (); //ratios->first ();
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

#if 0
bool Farey::TreeGoesDeep ()
{
    DLink<Ratio>* r = ratios->first ();
    for (; r != NULL; r = r->next)
    {

    }

}
#endif


void Farey::SetFareySeq (DList<Ratio>* rl) {
	m_FareySeq->destroy ();
	DLink<Ratio>* dl = rl->first ();
	for (; dl != NULL; dl = dl->next) {
		m_FareySeq->append (new Ratio(dl->data->GetP(), dl->data->GetQ()));
	}
}

void Farey::Analyse (Farey* fn) {
    Farey* X;
    Farey* Y;
    X = this; Y = fn;
    int lengthX = X->GetCommonDenomList ()->GetSize ();
    int lengthY = Y->GetCommonDenomList ()->GetSize ();
    cout << "size X: " << lengthX << " size Y: " << lengthY << endl;

    if (lengthX >= lengthY) {
	X = this; Y = fn;
    }
    else {
	Y = this; X = fn;
    }

    DList<Ratio>* xf = X->GetCommonDenomList ();
    DList<Ratio>* yf = Y->GetCommonDenomList ();

    DLink<Ratio>* xfl = xf->first ();
    DLink<Ratio>* yfl = yf->first ();

    int ldiff = X->GetCommonDenomList ()->GetSize () - Y->GetCommonDenomList ()->GetSize () + 1;
    int i = 0;
    DLink<Ratio>* xfc = xf->first ();
    xfl = xf->first ();
    double dE = 0;
    for (; i < ldiff; i++) {
	dE = 0;
	for (yfl = yf->first (); yfl != NULL && xfl != NULL; yfl = yfl->next, xfl = xfl->next) {
	    int x = xfl->data->GetP ();
	    int y = yfl->data->GetP ();
	    dE += ((x - y) * (x - y));
	    cout << x << "|" << y << endl;
	}
	xfc = xfc->next;
	xfl = xfc;
	cout << "Euclid distance, phase " << i << ": " << (sqrt (dE)) << endl; 
    }
}

void Farey::AnalyseChronotonic (Farey* fn) {
	//measures Euclidean distance, Kullback-Lebler and Komolgorov distance
	//between Fareu Sequences as chronotonic functions (Toussaint article)
    Farey* X;
    Farey* Y;
    X = this; Y = fn;

    DList<Ratio>* xf = X->GetCommonDenomList ();
    DList<Ratio>* yf = Y->GetCommonDenomList ();

    DLink<Ratio>* xfl = xf->first ();
    DLink<Ratio>* yfl = yf->first ();

    DList<int>* ctx = new DList<int>;
    DList<int>* cty = new DList<int>;

    cout << "chronotonic function x:" << endl;
    for (; xfl != NULL; xfl = xfl->next) {
	int cur = xfl->data->GetP () + 1;
	int n = cur - 1;
	while (--cur > 0) {
	    ctx->append (new int(n));
	    cout << n << " ";
	}
    }
    cout << endl;
    cout << "chronotonic function y:" << endl;
    for (; yfl != NULL; yfl = yfl->next) {
	int cur = yfl->data->GetP () + 1;
	int n = cur - 1;
	while (--cur > 0) {
	    cty->append (new int(n));
	    cout << n << " ";
	}
    }
    cout << endl;
    
    int lengthX = ctx->GetSize ();
    int lengthY = cty->GetSize ();
//    cout << "size X: " << lengthX << " size Y: " << lengthY << endl;

    if (lengthX >= lengthY) {
	Edistance (ctx, cty);
	KLdistance (ctx, cty);
	Kdistance (ctx, cty);
    }
    else {
	Edistance (cty, ctx);
	KLdistance (cty, ctx);
	Kdistance (cty, ctx);
    }
    
    ctx->destroy ();
    delete ctx;
    cty->destroy ();
    delete cty;
}

void Farey::KLdistance (DList<int>* xl, DList<int>* yl) {
    DLink<int>* xfl = xl->first ();
    DLink<int>* yfl = yl->first ();

    int ldiff = xl->GetSize () - yl->GetSize () + 1;
    int i = 0;
    DLink<int>* xfc = xl->first ();
    xfl = xl->first ();
    double dE = 0;
    for (; i < ldiff; i++) {
	dE = 0;
	for (yfl = yl->first (); yfl != NULL && xfl != NULL; yfl = yfl->next, xfl = xfl->next) {
	    double x = double(*xfl->data);
	    double y = double(*yfl->data);
	    dE += (x * log(x/y));
//	    cout << x << "|" << y << endl;
	}
	xfc = xfc->next;
	xfl = xfc;
	cout << "Kullback-Liebler distance, phase " << i << ": " << (dE) << endl; 
    }

}

void Farey::Kdistance (DList<int>* xl, DList<int>* yl) {
 DLink<int>* xfl = xl->first ();
    DLink<int>* yfl = yl->first ();

    int ldiff = xl->GetSize () - yl->GetSize () + 1;
    int i = 0;
    DLink<int>* xfc = xl->first ();
    xfl = xl->first ();
    double dE = 0;
    for (; i < ldiff; i++) {
	dE = 0;
	for (yfl = yl->first (); yfl != NULL && xfl != NULL; yfl = yfl->next, xfl = xfl->next) {
	    double x = double(*xfl->data);
	    double y = double(*yfl->data);
	    dE += fabs(x - y);
//	    cout << x << "|" << y << endl;
	}
	xfc = xfc->next;
	xfl = xfc;
	cout << "Kolmogorov var. distance, phase " << i << ": " << (dE) << endl; 
    }

}

void Farey::Edistance (DList<int>* xl, DList<int>* yl) {
    DLink<int>* xfl = xl->first ();
    DLink<int>* yfl = yl->first ();

    int ldiff = xl->GetSize () - yl->GetSize () + 1;
    int i = 0;
    DLink<int>* xfc = xl->first ();
    xfl = xl->first ();
    double dE = 0;
    for (; i < ldiff; i++) {
	dE = 0;
	for (yfl = yl->first (); yfl != NULL && xfl != NULL; yfl = yfl->next, xfl = xfl->next) {
	    int x = *xfl->data;
	    int y = *yfl->data;
	    dE += ((x - y) * (x - y));
	    //    cout << x << "|" << y << endl;
	}
	xfc = xfc->next;
	xfl = xfc;
	cout << "Euclid distance, phase " << i << ": " << (sqrt (dE)) << endl; 
    }

}

void Farey::OnsetMatches (Farey* fn) {
	//when do two rhythms as Farey Sequences contain common onsets?
	//this function counts the number of common onsets of note durations
    Farey* X;
    Farey* Y;
    X = this; Y = fn;

    DList<int>* ox = new DList<int>;
    DList<int>* oy = new DList<int>;

    DList<Ratio>* xf = X->GetCommonDenomList ();
    DList<Ratio>* yf = Y->GetCommonDenomList ();

    DLink<Ratio>* xfl = xf->first ();
    DLink<Ratio>* yfl = yf->first ();

    int accum = 0;
    ox->append (new int(0));
    for (; xfl != NULL; xfl = xfl->next) {
		//cout << accum << " ";
		accum += xfl->data->GetP ();
		ox->append (new int(accum));	
    }
	//cout << accum << " " << endl;

    accum = 0;
    oy->append (new int(0));
    for (; yfl != NULL; yfl = yfl->next) {
		//cout << accum << " ";
		accum += yfl->data->GetP ();
		oy->append (new int(accum));
    }
	//cout << accum << " " << endl;
	
    int lengthX = ox->GetSize ();
    int lengthY = oy->GetSize ();
    DList<int>* otemp;
    if (lengthX < lengthY) {
	otemp = ox;
	ox = oy;
	oy = otemp;
    }

    DLink<int>* oxl = ox->first ();
    DLink<int>* oyl = oy->first ();
    DLink<int>* oxcount = ox->first ();
    int ldiff = ox->GetSize () - oy->GetSize () + 1;
    int i = 0;
    int count = 0;
	int accumphase_x = 0;
    for (; i < ldiff; i++) {
		count = 0;
		for (oyl = oy->first (); oxl != NULL && oyl != NULL; oxl = oxl->next, oyl = oyl->next) {
			int x = *oxl->data;
			int	y = *oyl->data + accumphase_x;
			if (x == y)
				count++;
		}
	oxcount = oxcount->next;
	oxl = oxcount;
	accumphase_x = *oxl->data;
	cout << "Onset matches, phase " << i << ": " << count << endl; 
    }
    ox->destroy ();
    delete ox;
    oy->destroy ();
    delete oy;
}

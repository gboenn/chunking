 
#include "Ratio.h" 
#include "AlgoComp.h" 
#include "Farey.h"

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

 
//Ratio::Ratio() : rlist(new DList<Ratio>), elist(new DList<Ratio>), tie(false), scaling(1.f), events(new DList<Event>)

Ratio::Ratio() : rlist(new DList<Ratio>), elist(new DList<Ratio>), tie(false), scaling(1.f)
{
    subdiv = NULL;
    events = NULL;
} 
 
Ratio::~Ratio() 
{ 
	if (rlist != NULL) 
	{ 
		rlist->destroy (); 
		delete rlist; 
	} 
	if (elist != NULL) 
	{ 
		elist->destroy (); 
		delete elist; 
	} 
#if 0
	if (events != NULL) 
	{ 
		events->destroy (); 
		delete events; 
	} 
#endif
} 
 
void Ratio::DoElist ()  
{ 
/* jannis  boenn */ 
/* martin  boenn */ 
/* cat */ 
    elist->destroy ();
	if (p == 1 || q == 1) 
	{ 
		elist->append (this); 
		return; 
	} 
	 
	Ratio cp (*this); 
// 220311 bug here
	while (0) 
	{ 
		int locp = cp.GetP (); 
		int locq = cp.GetQ (); 
		Ratio r (locq, locp); 
		cout << (r.GetP ()) << "/" << (r.GetQ ());
		int newq = Ceiling (r.GetDouble ());
		Ratio* rd = new Ratio (1, newq); 
		cout << " - " << (rd->GetP ()) << "/" << (rd->GetQ ());
		elist->append (rd); 
		cp - (*rd); 
		cout << " = " << (cp.GetP ()) << "/" << (cp.GetQ ()) << endl;
		if (!cp.GetP ())	 
			return; 
	} 
} 
 
void Ratio::EngelExpansion ()
{
    elist->destroy ();
    if (p == 1 || q == 1) 
    { 
	elist->append (this); 
	return; 
    } 
    DList<int>* engel = new DList<int>;
    double u = this->GetDouble ();
    cout << "u: " << u << endl;
    while (u > 0.0000001)
    {
	int a = Ceiling (1./u);
	u = u * a - 1.;
	engel->append (new int(a));
    }
    DLink<int>* el = engel->first ();
    int accumul = 1;
    for (; el != NULL; el = el->next)
    {
	accumul *= (*el->data);
	cout << (*el->data) << ", ";
	elist->append (new Ratio (1, (accumul)));
    }
    cout << endl;
}

void Ratio::FareyEgyptians ()
{
    elist->destroy ();
    if (p == 1 || q == 1) 
    { 
	elist->append (this); 
	return; 
    } 
    if (p > q)
    {
	cout << "ratio must be in [0...1]" << endl; 
	return;
    }
    Farey f;
    f.CreateFareySeq (q);
    DList<Ratio>* r = f.GetRatioList ();
    //   cout << "r->getPos(this)" << (r->getPos(this)) << endl;
    DLink<Ratio>* rl = r->first ();
    int pos = 0;
    for (; rl != NULL; rl = rl->next, pos++)
    {
	if (rl->data->GetP () == p && rl->data->GetQ () == q)
	    break;
    }

    cout << "index: " << pos << ": " << p << " / " << q << endl;

    DLink<Ratio>* fr = r->getAt(pos);
    //cout << (fr->data->GetP ()) << " " << (fr->data->GetQ ()) << endl;
    
    for (; fr != NULL; fr = fr->previous) 
    {
	if ((fr->data->GetP ()) == 1)
	    break;
    }
    Ratio* rd = new Ratio (fr->data->GetP (), fr->data->GetQ ());
    //cout << (rd->GetP ()) << " " << (rd->GetQ ()) << endl;

    elist->append (rd);
#if 1
    for (; fr->next != NULL; fr = fr->next)
    {
	int que = fr->data->GetQ () * fr->next->data->GetQ ();
	Ratio* cur = new Ratio (1, que);
	elist->append (cur);
	if (fr->next->data->GetP () == this->p && fr->next->data->GetQ () == this->q)
	    break;
    }
#endif
}

// given that the distance between farey sequence elements is always c/d - a/b = 1/db
// and if only a fraction a/b is given in its lowest terms,
// then building the series ... -1/3b, -1/2b, -1/b, 1/b, 1/2b, 1/3b ... gives all possible
// distances from a/b where the fraction adjacent to a/b within F(n) could be found.
// the search for the fraction c/d next to a/b is constrained by the relation:
// ad - bc = 1 if c/d < a/b or bc - ad = 1 otherwise
// and constrained by d <= n.

void Ratio::FareyNet ()
{
    if (p > q)
    {
	cout << "ratio must be in [0...1]" << endl; 
	return;
    }
    int i = 0;
    int max_multiplier = 100;
    for (; i < max_multiplier; i++)
    {
	Ratio abplus (p,q);
	Ratio abminus (p,q);
	Ratio cd (1,i*q);
	abplus + cd;
	abminus - cd;
	abplus.AutoReduce ();
	abminus.AutoReduce ();
	if (((p*abminus.GetQ()) - (q*abminus.GetP())) == 1)
	{
	    cout << (abminus.GetP()) << "/" << (abminus.GetQ()) << ", " << p << "/" << q << endl;
	}
	if (((q*abplus.GetP()) - (p*abplus.GetQ())) == 1)
	{
	    cout << p << "/" << q  << ", " << (abplus.GetP()) << "/" << (abplus.GetQ()) << endl;
	}
    }
}
 

int Ratio::Gradus (int choice)
{
// if switch == 0, gradus only calcultaed for q of p/q
// if switch == 1, gradus calculated for p/q
    DList<Ratio>* rl = new DList<Ratio>;
    if (choice == 0)
    {
	cout << "gradus suavitatis only for q of p/q:" << endl;
	rl->append(new Ratio (p, q));
    }
    else
    {
	cout << "gradus suavitatis for p/q:" << endl;
	rl->append(new Ratio (1, p));
	rl->append(new Ratio (1, q));
    }

    int lcm = GetLCDOfRatioList (*rl);
    DList<Power>* prime_factors = new DList<Power>;
    PrimFaktoren (lcm, prime_factors);
    int gradus = 0;
    int numfactors = 0;
    DLink<Power>* pl; // p^q
    cout << p << "/" << q << " => ";
    for (pl = prime_factors->first (); pl != NULL; pl = pl->next) 
    { 
	cout << (pl->data->GetP ()) << "^" << (pl->data->GetQ ()) << " * ";
	gradus += (pl->data->GetQ () * pl->data->GetP ());
	numfactors += pl->data->GetQ ();
    }
    cout << " 1 => exponens: " << gradus << endl; 
    cout << "number of factors: " << numfactors << endl;
    gradus -= (numfactors - 1);
    cout << "gradus: " << gradus << endl;
    delete rl;
    return gradus;
}

void Ratio::MEX () 
{ 
	// implementation of modified Engel expansion 
 
 
} 
 
Ratio& Ratio::operator= (const Ratio& r) 
{ 
	if (&r == this) 
		return *this; 
	 
	p = r.p; 
	q = r.q; 
 
	return *this; 
} 
 
Ratio& Ratio::operator+ (const Ratio& r) 
{ 
	if (q == r.q) 
	{ 
		p += r.p; 
		return *this; 
	} 
 
	p = p * r.q + r.p * q; 
	q *= r.q; 
 
	return *this; 
} 
 
Ratio& Ratio::operator- (const Ratio& r) 
{ 
	if (q == r.q) 
	{ 
		p -= r.p; 
		return *this; 
	} 
 
	p = p * r.q - r.p * q; 
	q *= r.q; 
 
	return *this; 
} 
 
Ratio& Ratio::operator* (const Ratio& r) 
{ 
	 
	p *= r.p; 
	q *= r.q; 
 
	return *this; 
} 
 
Ratio& Ratio::operator/ (const Ratio& r) 
{ 
	 
	p *= r.q; 
	q *= r.p; 
 
	return *this; 
} 
 
 
void Ratio::Reduce (int c) 
{ 
	if (!c) 
		return; 
 
	p /= c; 
	q /= c; 
} 
 
void Ratio::Expand (int c) 
{ 
	if (!c) 
		return; 
	p *= c; 
	q *= c; 
} 
 
void Ratio::Median (const Ratio& ac, const Ratio& bd) 
{ 
	p = ac.p + bd.p; 
	q = ac.q + bd.q; 
} 
 
void Ratio::AutoReduce () 
{ 
	int red = GGT (p, q); 
	if (red < 1) 
		red = 1; 
	 
	Reduce (red); 
} 
 
bool Ratio::QisPow2 () 
{ 
	return IsPowerOfTwo(q); 
} 

bool Ratio::QisPow2le128 () 
{ 
    if (q < 128 && IsPowerOfTwo(q))
	return true;
    return false;
} 
 
 
void Ratio::GetFloats (DList<float>* rfloats, Ratio* r)
{
    if (subdiv)
    {
	int s = subdiv->GetRatioList ()->GetSize (); 
	if (s)
	{
	    DLink<Ratio>* l = subdiv->GetFirst ();
	    for (; l->next != NULL; l = l->next)
		l->data->GetFloats (rfloats, this);
		
	    return;
	}
    }
    if (r != this)
    {
	rfloats->append (new float (r->GetFloat () + this->GetFloat () * scaling));
//	cout << this << " GetFloats gets r " << r << ": " <<  r->GetFloat () << " + " << this->GetFloat () << " * " <<  scaling << " = " << r->GetFloat () + this->GetFloat () * scaling <<  endl;
    }
    else
    {
	rfloats->append (new float (this->GetFloat () * scaling));
//	cout << this << " GetFloats gets " << this->GetFloat () << " * " <<  scaling << " = " <<  this->GetFloat () * scaling <<  endl;
    }
}

void Ratio::SetSubdiv(Farey* subdiv_farey)
{
//  cout << this << " SetSubdiv " << subdiv_farey << endl;
    subdiv = subdiv_farey;
    subdiv_farey->SetParent (this);
//  cout << "call  subdiv->SetScaling with " << scaling << endl;
    subdiv->SetScaling (scaling); // this overrides subdiv_farey's scaling member
}

Farey* Ratio:: GetSubdiv()
{
    return subdiv;
}

void Ratio::SetScaling (float scale)
{
//    cout << this << " Ratio::SetScaling " << scale << endl; 
    scaling = scale;
    if (subdiv)
    {
//	cout << this << " calls subdiv->SetScaling (scale);" << endl;
	subdiv->SetScaling (scale);
    }
}

float Ratio::GetScaling ()
{
    return scaling;
}

DLink<Event>* Ratio::GetEvents ()
{
    return events->first ();
}

void Ratio::SetParent(Farey* parent)
{
    this->parent = parent;
}

Farey* Ratio::GetParent()
{
    return parent;
}

void Ratio::SetRatioWithFloat (float f)
{
    // data arrays for dec to continuos fraction conversion: 
    const int N = 10; 
    int a[N+1];; 
    int p_[N+2]; 
    int q_[N+2];
    float default_error = 0.0001;

    float_to_cfrac (f, N, a, p_, q_);

    for ( int i = 0; i <= N; i++ ) 
    { 
	if (!q_[i+1]) 
	    continue; 
	double temp = ( double ) p_[i+1] / ( double ) q_[i+1]; 
			 
	float error = f - temp; // should collect and store errors in a list 
 
	if ((fabs(error)) < default_error /*&& (dec == temp)*/) 
	{ 
#if 0
	    cout                        << "  " 
					<< setw(12) << a[i]    << "  " 
					<< setw(12) << p_[i+1]  << "  " 
					<< setw(12) << q_[i+1]  << "  " 
					<< setw(14) << temp    << "  " 
					<< setw(14) << error   << "\n"; 
#endif
	    p = p_[i+1];
	    q = q_[i+1];
	    break; 
	} 
    } 
	
}

void Ratio::GetFlatList (DList<Ratio>* rflat)
{
    if (subdiv)
    {
	int s = subdiv->GetRatioList ()->GetSize (); 
	if (s)
	{
	    DLink<Ratio>* l = subdiv->GetFirst ();
	    for (; l->next != NULL; l = l->next)
		l->data->GetFlatList (rflat);
		
	    return;
	}
    }
    rflat->append (this);
}

float Ratio::Indig_a ()
{
    return (Digest (p));
}

float Ratio::Indig_b ()
{
    return (Digest (q));
}

float Ratio::Indig_ab ()
{
    return (Digest (p) + Digest (q));
}

float Ratio::Harmon_ab ()
{
    if ((p - q) == 0)
		return 0.f;
    return (1./Indig_ab ());
}

string Ratio::Christoffel (bool flag) {
    /*
     Christoffel Words
     input: coprime ratio m/n
     prev-y = 0
    
     iterate integers for i=0 i<=n i++
     lower christoffel: (flag == true)
    
     y = floor(i * m./n.)
     test-y = y - prev-y
     
     if (test-y == 0) then output a
     else output a,b
     
     prev-y = y
     
     higher christoffel: (flag == false)
     
     y = ceiling(i * m./n.)
     test-y = next-y - y
     
     if (test-y == 0) then output a
     else output b,a
     
     input comes form farey sequence, or from partition of primes into k=2 distinct parts
     */
    
    int i = 0;
    float prev_y = 0.f;
    string result = "";
    double value = GetDouble ();
    int countletters = 0;
    if (flag){
        for (i=1; i<=q; i++) {
            double y = int(double(i) * value);
            double test_y = y - prev_y;
            result += "a";
            ++countletters;
            if (test_y > 0.f) {
                int k = 0;
                int t = int(test_y);
                for (; k < t; k++){
                    result += "b";
                    ++countletters;
                }
            }
            
            prev_y = y;
        
        }
    }
    return result;
}

void Ratio::GetNeighbours (DList<Ratio>* p, int flag) {
    Farey* f = new Farey ();
    f->CreateFareySeq (this->GetQ ());
    DLink<Ratio>* l = f->GetFirst ();
    if (flag) {
        cout << "ancestors of " << this->GetQ() << "/" << this->GetP() << " are:" << endl;
    } else {
        cout << "ancestors of " << this->GetP() << "/" << this->GetQ() << " are:" << endl;
    }
    
    for (; l != NULL; l = l->next) {
        if (l->data->GetP() == this->GetP () && l->data->GetQ() == this->GetQ ()) {
            if (l->previous != NULL) {
                p->append ( new Ratio (l->previous->data->GetP (), l->previous->data->GetQ ()));
                if (flag) {
                    cout << "L: " << l->previous->data->GetQ () << "/" << l->previous->data->GetP () << endl;
                } else {
                    cout << "L: " << l->previous->data->GetP () << "/" << l->previous->data->GetQ () << endl;
                }
                
            }
            if (l->next != NULL) {
                p->append ( new Ratio (l->next->data->GetP (), l->next->data->GetQ ()));
                if (flag) {
                    cout << "R: " << l->next->data->GetQ () << "/" << l->next->data->GetP () << endl;
                } else {
                    cout << "R: " << l->next->data->GetP () << "/" << l->next->data->GetQ () << endl;
                }
            }
        }
    }
    delete f;
}


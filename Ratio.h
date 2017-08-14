#ifndef __Ratio_h__ 
#define __Ratio_h__ 
 
#include "DList.h" 
#include "Farey.h"
#include <string>

class Event;
class Farey;

class Ratio   
{ 
public: 
	Ratio (); 
	Ratio (int a, int b) : p(a), q(b), rlist(new DList<Ratio>), elist(new DList<Ratio>), tie(false), events(new DList<Event>) { scaling = 1.f; subdiv = NULL; } 
	Ratio (const Ratio& r) : rlist(new DList<Ratio>), elist(new DList<Ratio>) 
	{ p = r.p; q = r.q; tie = r.tie; scaling = r.scaling; subdiv = r.subdiv; events = r.events; } 
	Ratio& operator= (const Ratio& r); 
	Ratio& operator+ (const Ratio& r); 
	Ratio& operator- (const Ratio& r); 
	Ratio& operator* (const Ratio& r); 
	Ratio& operator/ (const Ratio& r); 
 
	bool operator== (const Ratio& r) 
	{  
		if (p == r.p && q == r.q) 
			return true; 
		return false; 
	} 
 
	virtual ~Ratio (); 
 
 
	void SetP (int i) { p = i; } 
	void SetQ (int i) { q = i; } 
 
	int GetP () const { return p; } 
	int GetQ () const { return q; } 
 
	float GetFloat () { return ((float (p)) / (float (q))); } 
	double GetDouble () { return ((double (p)) / (double (q))); } 
 
	void Reduce (int c); 
	void Expand (int c); 
 
	void Median (const Ratio& ac, const Ratio& bd); 
	 
	void AutoReduce (); 
 
	bool IsReciprocal () 
	{ 
		if (p == 1 || p == -1) 
			return true; 
		return false; 
	} 
 
	bool QisPow2 ();
	bool QisPow2le128 ();
 
	void DoElist (); 
	void MEX (); 

	DList<Ratio>* GetList () { return rlist; } 
	DList<Ratio>* GetEList () { return elist; } 
	void SetTie (bool v) { tie = v; } 
	bool HasTie () { return tie; } 

	void GetFloats(DList<float>* rfloats, Ratio* r);
	void SetSubdiv(Farey* subdiv_farey);
	Farey* GetSubdiv();
	void SetScaling(float scale);
	float GetScaling();
	DLink<Event>* GetEvents();
	void SetParent(Farey* parent);
	Farey* GetParent();
	void SetRatioWithFloat (float f);
	void AppendEvent (Event* e) { events->append (e); }
	void GetFlatList (DList<Ratio>* rflat);
	void FareyEgyptians ();
	void EngelExpansion ();
	void FareyNet ();
	int Gradus (int choice);
	float Indig_a ();
	float Indig_b ();
	float Indig_ab ();
	float Harmon_ab ();
    string Christoffel (bool flag);
    void GetNeighbours (DList<Ratio>* p, int flag);
    
protected: 
	int p; 
	int q; 
	DList<Ratio>* rlist; 
	DList<Ratio>* elist; 
	bool tie; 

	DList<Event>* events;
	Farey* subdiv;
	Farey* parent;
	float scaling;

}; 
 
#endif 

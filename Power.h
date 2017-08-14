#ifndef __Power_h__
#define __Power_h__

class Power  
{
public:
	
	Power ();
	Power (int a, int b) : p(a), q(b) {}
	Power (const Power& r) { p = r.p; q = r.q; }

	virtual ~Power();

	void SetP (int i) { p = i; }
	void SetQ (int i) { q = i; }

	int GetP () const { return p; }
	int GetQ () const { return q; }

	int GetVal ();  

protected:
	int p;
	int q;
};

#endif 

#ifndef __Farey_h__
#define __Farey_h__ 
 
#include "Ratio.h" 
#include "DList.h" 
#include "Visitor.h" 

class Ratio;
 
class Farey   
{ 
public: 

    Farey(); 
	virtual ~Farey(); 
 
	void Init (); 
	void CreateFareySeq (int i); 
	void PrintFareySeq (); 
	void CreateDiffList (); 

	void SetAddInverse (int i) {m_inverse = i;}
	void Multiply (Ratio* r);
	void AddInverse ();

	DList<Ratio>* GetRatioList () const { return m_FareySeq; }
	DLink<Ratio>* GetFirst () const { return m_FareySeq->first (); } 
	DLink<Ratio>* GetLast () const { return m_FareySeq->last (); } 
 
	DLink<Ratio>* GetFirstDiff () const { return m_FareyDiffList->first (); } 
	DLink<Ratio>* GetLastDiff () const { return m_FareyDiffList->last (); } 
 
	DLink<Ratio>* GetFirstCommonDenom () const { return m_FareyCommonDenomList->first (); } 
	DLink<Ratio>* GetLastCommonDenom () const { return m_FareyCommonDenomList->last (); } 
 
	void CreateCommonDenomList (); 
	void CreateCommonDenomList2 ();
	int GetFareyIndex () const { return m_FareyIndex; } 
 
	void Accept (Visitor& v, int norm=0);  
	int GetFareySeqLength () { return m_FareySeq->GetSize (); } 
	int GetCommonDenominator () {return comdenom;}
	void SetScaling (float scaling);

	float GetScaling () const { return scaling; }
	
	DList<Ratio>* GetFareySeq () const { return m_FareySeq; }
	DList<Ratio>* GetCommonDenomList () const { return m_FareyCommonDenomList; }
	void SetFareySeq (DList<Ratio>* rl); 
	void SetParent (Ratio* r) { parent = r; }
	Ratio* GetParent () const { return parent; }

	void UpdateScalings ();
	void PrintFareyTree ();
	void PrintFareyResonances (int f);
	void PrintFareyResonances ();
	void PrintFareyLatticePoints ();

	void Analyse (Farey* fn);
	void AnalyseChronotonic (Farey* fn);
	void KLdistance (DList<int>* xl, DList<int>* yl);
	void Kdistance (DList<int>* xl, DList<int>* yl);
	void Edistance (DList<int>* xl, DList<int>* yl);
	void OnsetMatches (Farey* fn);

protected: 
 
	DList<Ratio>* m_FareySeq; 
	DList<Ratio>* m_FareyDiffList;  
	DList<Ratio>* m_FareyCommonDenomList; 
	int comdenom;
	int m_FareyIndex; 
        float scaling; 
	Ratio* parent;
	int m_inverse;
}; 
 
#endif  

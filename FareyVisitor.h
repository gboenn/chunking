///////////////////////////////////////////
// FareyVisitor.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////


#ifndef __FareyVisitor_h__
#define __FareyVisitor_h__ 
 
#include "Farey.h" 
#include "Visitor.h" 
 
class FareyVisitor : public Visitor 
{ 
	 
public: 
	FareyVisitor(); 
	FareyVisitor(float); 
	virtual ~FareyVisitor(); 
 
	virtual void Visit (Farey&, int=0); 
	virtual void Visit (SternBrocot&) {};
	virtual void PostCalc (Farey* f) { }
	virtual void OverrideFareyRatios (Farey* f) { }
	
	virtual DList<Ratio>* GetRatioList () const { return m_FareySeq; }
	
	DLink<Ratio>* GetFirst () const { return m_FareySeq->first (); } 
	DLink<Ratio>* GetLast () const { return m_FareySeq->last (); } 
 
	DLink<Ratio>* GetFirstDiff () const { return m_FareyDiffList->first (); } 
	DLink<Ratio>* GetLastDiff () const { return m_FareyDiffList->last (); } 
 
	DLink<Ratio>* GetFirstCommonDenom () const { return m_FareyCommonDenomList->first (); } 
	DLink<Ratio>* GetLastCommonDenom () const { return m_FareyCommonDenomList->last (); } 
 
	int GetOriginalFareyIndex () const { return m_FareyIndex; } 
 
	//void SetFilterValue (float); 
	void CreateDiffList (); 
	void CreateCommonDenomList (); 
 
protected: 
	DList<Ratio>* m_FareySeq; 
	DList<Ratio>* m_FareyDiffList;  
	DList<Ratio>* m_FareyCommonDenomList; 
	float m_FilterValue; 
	int m_FareyIndex; 
}; 
 
 
#endif 

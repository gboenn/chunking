///////////////////////////////////////////
// FareyVisitor.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "FareyVisitor.h"
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


FareyVisitor::FareyVisitor() : m_FilterValue (1.0f)
{
	m_FareySeq = new DList<Ratio>;
	m_FareyDiffList = new DList<Ratio>;
	m_FareyCommonDenomList = new DList<Ratio>;
}

FareyVisitor::FareyVisitor(float f) : m_FilterValue (f)
{
	m_FareySeq = new DList<Ratio>;
	m_FareyDiffList = new DList<Ratio>;
	m_FareyCommonDenomList = new DList<Ratio>;
}

FareyVisitor::~FareyVisitor()
{
	delete m_FareySeq;
	delete m_FareyDiffList;
	delete m_FareyCommonDenomList;
}


void FareyVisitor::Visit (Farey& f, int norm)
{
	DLink<Ratio>* r;
	
	double scale_val = 1.0f;
	if (!norm)
		scale_val /= Digest (GetFirstPrimeLower (f.GetFareyIndex ()));

	for (r = f.GetFirst (); r != NULL; r = r->next)
	{
		if ((Digest (r->data->GetQ ()) * scale_val) > m_FilterValue)
			continue;
		Ratio* nr = new Ratio (*(r->data));
		m_FareySeq->append (nr);
	}

	m_FareyIndex = f.GetFareyIndex ();

//	CreateDiffList ();
//	CreateCommonDenomList ();
}

void FareyVisitor::CreateDiffList ()
{
	DLink<Ratio>* r1;
	
	for (r1 = m_FareySeq->first (); r1 != NULL && r1->next != NULL; r1 = r1->next)
	{
		Ratio* d = new Ratio (1,1);
		d->SetQ ((r1->data->GetQ ()) * (r1->next->data->GetQ ()));
		m_FareyDiffList->append (d);
	}
}

void FareyVisitor::CreateCommonDenomList ()
{
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

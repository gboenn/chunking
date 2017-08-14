#include "SternBrocot.h" 
#include "AlgoComp.h" 

#include "gc_switch_ssh.h"
#if BOEHM_GC_SWITCH
#define GC_THREADS
//#include "gc/gc_alloc.h"
#include "gc.h"

inline void * operator new(size_t n) { return GC_malloc(n); }
inline void operator delete(void *) {}
inline void * operator new[](size_t n) { return GC_malloc(n); }
inline void operator delete[](void *) {}
#endif

SternBrocot::SternBrocot()  
{ 
    
	m_SternBrocotSeq = new DList<Ratio>; 
	Init (); 
} 
 
SternBrocot::~SternBrocot() 
{ 
	delete m_SternBrocotSeq; 
} 
 
void SternBrocot::Init () 
{ 
	m_SternBrocotSeq->destroy (); 
	Ratio* r1 = new Ratio (0,1); 
	Ratio* r2 = new Ratio (1,0); 
	m_SternBrocotSeq->append (r1); 
	m_SternBrocotSeq->append (r2); 
	m_SternBrocotIndex = 1; 
} 

void SternBrocot::Accept (Visitor& v) 
{ v.Visit(*this); } 
 
void SternBrocot::CreateSternBrocotSeq (int i) 
{ 
	if (i <= 1) 
		return; 
	 
	Init (); 
 
	int k = 1; 
	int stop = m_SternBrocotSeq->GetSize (); 
	int m = 0; 
	int insert_index; 
	for (; k < i; k++) 
	{ 
		DLink<Ratio>* r1 = m_SternBrocotSeq->first (); 
		DLink<Ratio>* r2 = r1->next; 
 
		stop = m_SternBrocotSeq->GetSize () - 1; 
		for (m = 0; m < stop; m++) 
		{ 
		    Ratio* r3 = new Ratio (); 
		    r3->Median (*(r1->data), *(r2->data)); 
		    insert_index = m_SternBrocotSeq->getPos (r2->data) - 1; 
		    r1 = r1->next; 
		    r2 = r2->next; 
		    m_SternBrocotSeq->insertAt (insert_index, r3); 
      		} 
		m_SternBrocotIndex++; 
 
	} 
} 
	 
 
void SternBrocot::PrintSternBrocotSeq () 
{ 
	cout << endl; 
	cout << "SternBrocot Sequence (" << m_SternBrocotIndex << ") : Length (" << (m_SternBrocotSeq->GetSize ()) << ")"; 
	cout << endl << endl; 
	DLink<Ratio>* r1 = m_SternBrocotSeq->first (); 

	for (; r1 != NULL; r1 = r1->next) 
		cout << setw(8) << (r1->data->GetP ()) << " / " << (r1->data->GetQ ()) << endl; 
 
} 
 

#ifndef __SternBrocot_h__
#define __SternBrocot_h__ 

#ifndef __Ratio_h__
#include "Ratio.h" 
#endif

#ifndef __DList_h__
#include "DList.h" 
#endif

class Ratio;
 
class SternBrocot   
{ 
public: 

        SternBrocot(); 
	virtual ~SternBrocot(); 
 
	void Init (); 
	void CreateSternBrocotSeq (int i); 
	void PrintSternBrocotSeq (); 
	void CreateDiffList (); 

	void Accept (Visitor& v);

	DList<Ratio>* GetRatioList () const { return m_SternBrocotSeq; }
	DLink<Ratio>* GetFirst () const { return m_SternBrocotSeq->first (); } 
	DLink<Ratio>* GetLast () const { return m_SternBrocotSeq->last (); } 
 
	int GetSternBrocotIndex () const { return m_SternBrocotIndex; } 
 
	int GetSternBrocotSeqLength () { return m_SternBrocotSeq->GetSize (); } 
  
	DList<Ratio>* GetSternBrocotSeq () const { return m_SternBrocotSeq; }
	void SetSternBrocotSeq (DList<Ratio>* rl) 
	{ 
	    m_SternBrocotSeq->destroy ();
	    m_SternBrocotSeq = rl; 
	}

protected: 
 
	DList<Ratio>* m_SternBrocotSeq; 
	
	int m_SternBrocotIndex; 
        
}; 
 
#endif  

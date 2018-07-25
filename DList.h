///////////////////////////////////////////
// DList.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __DList_h__ 
#define __DList_h__ 
 
#include "Standards.h" 
 
//#include <iostream> 
//#include <stdio.h> 

#include "gc_switch_ssh.h"
#if BOEHM_GC_SWITCH
#define GC_THREADS
//#include "gc/new_gc_alloc.h"
#include "gc.h"
#include "gc_cpp.h"
#endif


 
template <class Data> class DList; 
 
template <class Data> 
class DLink { 
 
public: 
	DLink () {data=0; next=0; previous=0;} 
	~DLink () { }  
	 
	Data* data; 
	DLink<Data>* next; 
	DLink<Data>* previous; 
 
	friend class DList<Data>; 
}; 
 
template <class Data> 
class DList { 
 
public: 
	DList () {size=0;head=0;}; 
	~DList (); 
	bool append (Data* data); 
	bool prepend (Data* data); 
	bool insertAt (int index, Data* data); 
	bool replaceAt (int index, Data* data); 
         
        bool removeElement (Data* element); 
	DLink<Data>* getAt (int index) const; 
	int getPos (Data* element) const; 
	int has (Data* element) const; 
 
	DLink<Data>* first () const; 
	DLink<Data>* last () const; 
	int GetSize () const { return size; } 
	void destroy (); 
	void print (); 
	void printback (); 
	    
#if BOEHM_GC_SWITCH
	    inline void * operator new(size_t n) { return GC_malloc(n); }
	    inline void operator delete(void *) {}
	    inline void * operator new[](size_t n) { return GC_malloc(n); }
	    inline void operator delete[](void *) {}
#endif

protected: 
	int size; 
	DLink<Data>* head; 
	DLink<Data>* tail; 
 
}; 
 
template <class Data> 
DList<Data>::~DList () 
{ 
	if (head != NULL) 
		destroy (); 
} 
 
template <class Data> 
void DList<Data>::destroy () 
{ 

//	cout << "Dlist::destroy(), size " << size; 
	if (size > 1) 
	{ 
		DLink<Data>* cur = head; 
		//cout << "head: " << head << endl; 
		//cout << "head->data: " << head->data << endl; 
		int i = size; 
		int k = size; 
		while (--i >= 1) 
		{ 
			while (--k >= 1) 
				cur = cur->next; 
			//cout << "delete cur: " << cur << endl; 
			//cout << "delete cur->data: " << cur->data << endl; 
			delete cur; 
			--size; 
			k = size; 
			cur = head; 
		//	printf ("size: %d\n", size); 
		} 
	} 
	if (head) 
	{ 
		//cout << "delete head: " << head << endl; 
		//cout << "delete head->data: " << head->data << endl; 
		delete head; 
		head = NULL; 
	}	 
 
	size = 0; 
} 
 
template <class Data> 
bool DList<Data>::append (Data* data) 
{ 
	DLink<Data>* item = new DLink<Data>; 
	if (!item) 
		return false; 
 
	item->data = data; 
	if (!head) 
	{ 
		head = item; 
		tail = item; 
		size++; 
		return true; 
	} 
 
	DLink<Data>* cur = head; 
	int i = size; 
	while (--i >= 1) 
		cur = cur->next; 
	cur->next = item; 
	item->previous = cur; 
	tail = item; 
	size++; 
		 
	return true; 
} 
 
 
template <class Data> 
bool DList<Data>::prepend (Data* data) 
{ 
 
	DLink<Data>* item = new DLink<Data>; 
	if (!item) 
		return false; 
 
	item->data = data; 
	if (!head) 
	{ 
		head = item; 
		tail = item; 
		size++; 
		return true; 
	} 
	 
	item->next = head; 
	head->previous = item; 
	head = item; 
	size++; 
	return true; 
} 
 
template <class Data> 
void DList<Data>::print () 
{ 
	DLink<Data>* cur; 
		printf ("list forward =====================\n"); 
	for (cur = head; cur != NULL; cur = cur->next) 
	{ 
		printf ("cur: %d\n", cur); 
		printf ("cur->data: %d\n", (*cur->data)); 
		printf ("cur->next: %d\n", cur->next); 
		printf ("cur->previous: %d\n", cur->previous); 
		printf ("===================================\n"); 
	} 
} 
 
template <class Data> 
void DList<Data>::printback () 
{ 
	DLink<Data>* cur; 
		printf ("list backward =====================\n"); 
	for (cur = tail; cur != NULL; cur = cur->previous) 
	{ 
		printf ("cur: %d\n", cur); 
		printf ("cur->data: %d\n", (*cur->data)); 
		printf ("cur->next: %d\n", cur->next); 
		printf ("cur->previous: %d\n", cur->previous); 
		printf ("===================================\n"); 
	} 
} 
 
template <class Data> 
bool DList<Data>::insertAt (int index, Data* data) 
{ 
	// insert before index [0,1,2,3...] 
 
	if (index > size) 
		return false; 
 
	if (index == size) 
		return append (data); 
	 
	if (index <= 0) 
		return prepend (data); 
 
	DLink<Data>* item = new DLink<Data>; 
	if (!item) 
		return false; 
 
	item->data = data; 
 
	DLink<Data>* cur = head; 
	int i = 1; 
	while (i++ < index) 
	{ 
		cur = cur->next; 
	} 
	item->next = cur->next; 
	item->previous = cur; 
	cur->next->previous = item; 
	cur->next = item; 
	size++; 
	return true; 
} 
 
template <class Data> 
bool DList<Data>::replaceAt (int index, Data* data) 
{ 
	// replace data at index no. [0,1,2,3...] 
	if (index >= size) 
		return false; 
 
	if (index <= 0) 
	{ 
		if (!head) 
		{ 
			head = new DLink<Data>; 
			tail = head; 
			if (!head || !tail) 
				return false; 
			size++; 
		} 
		 
		head->data = data; 
		return true; 
	} 
	 
	DLink<Data>* cur = head; 
	int i = 0; 
	while (i++ < index) 
		cur = cur->next; 
	cur->data = data; 
 
	return true; 
} 
 
template <class Data> 
DLink<Data>* DList<Data>::getAt (int index) const 
{ 
	DLink<Data>* cur = head; 
	int i = -1; 
	while (i++ < index) 
	{ 
		if (i == index) 
			return cur; 
		cur = cur->next; 
	} 
 
	return 0; 
} 
 
template <class Data> 
int DList<Data>::getPos (Data* element) const 
{ 
	DLink<Data>* cur = head; 
	int i = 0; 
	while (i++ < size) 
	{ 
		if (cur->data == element) 
			return i; 
		cur = cur->next; 
	} 
 
	return -1; 
} 
 
template <class Data> 
int DList<Data>::has (Data* element) const 
{ 
	DLink<Data>* cur = head; 
	int i = -1; 
	while (++i < size) 
	{ 
		if (*cur->data == *element) 
			return i; 
		cur = cur->next; 
	} 
 
	return -1; 
} 
 
 
template <class Data> 
bool DList<Data>::removeElement (Data* element)  
{ 
	DLink<Data>* cur = head; 
	int i = 0; 
//cout << "size: " << size << endl; 
	while (i++ < size) 
	{ 
//cout << "count: " << i << endl; 
		if (cur->data == element) 
			break; 
		cur = cur->next; 
	} 
 
	if (i == 1) 
	{ 
		if (!head) 
		    return false; 
		if (!cur->next)
		    return false;
		DLink<Data>* temp = cur->next; 
		//	delete cur; 
		head = temp;
		if (head->previous)
		    head->previous = 0; 
		size--; 
//cout << "head deleted" << endl; 
		return true; 
	} 
	if (i == size) 
	{ 
		if (!tail) 
			return false; 
		DLink<Data>* temp = cur->previous; 
		//	delete cur; 
		tail = temp;
		if (tail->next)
		    tail->next = 0; 
		size--; 
//cout << "tail deleted" << endl; 
		return true; 
	} 

	DLink<Data>* temp = cur->next; 
	DLink<Data>* tempp = cur->previous; 
//int addr = &(*cur); 
//cout << "address of cur: " << cur << endl; 
//cout << "address of cur->data: " << cur->data << endl; 
//cout << "value: " << (*cur->data) << endl;
//delete cur; 
	if (temp != NULL) 
		temp->previous = tempp; 
	if (tempp != NULL) 
		tempp->next = temp; 
	 
	size--; 
//cout << "element " << addr << " deleted, size: " << size << endl;  
	return true; 
 
} 
 
template <class Data> 
DLink<Data>* DList<Data>::first () const 
{ 
	//if (!head) 
	//	printf("warning: using zero pointer?\n"); 
	return head; 
} 
 
template <class Data> 
DLink<Data>* DList<Data>::last () const 
{ 
	//if (!tail) 
	//	printf("warning: using zero pointer?\n"); 
	return tail; 
} 
 
#endif 
 

///////////////////////////////////////////
// Visitor.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __Visitor_h__ 
#define __Visitor_h__ 
 
class Farey; 
class SternBrocot;

class Visitor   
{ 
public: 
	Visitor(); 
	virtual ~Visitor(); 
 
	virtual void Visit (SternBrocot&) = 0;
	virtual void Visit (Farey&, int) = 0; 
	virtual void PostCalc (Farey*) = 0;
	virtual void OverrideFareyRatios (Farey*) = 0;
}; 
 
 
#endif  

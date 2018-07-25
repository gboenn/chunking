///////////////////////////////////////////
// Power.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "Power.h"


//////////////////////////////////////////////////////////////////////

Power::Power()
{

}

Power::~Power()
{

}


int Power::GetVal ()
{
  // p^q
	if (!q)
		return 1;
	int i = 1; 
	int res = p; 
	for (; i<q; i++) 
		res *= p;
	return res;

}

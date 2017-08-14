
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

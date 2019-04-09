///////////////////////////////////////////
// Alea.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef	__Alea_h__
#define	__Alea_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif

#ifndef	__AlgoComp_h__
#include "AlgoComp.h"
#endif

class Alea {

private: 
	
	double rand_max;

public:

	Alea();

	double Uniform( double kmin, double kmax );
	double Linear();
	double ReverseLinear();
	double Triangular();
	double Exponential( double lambda );
	double BiExpon( double lambda );
	double Gaussian( double sigma, double xmu, long N );
	double Cauchy( double alpha );
	double Beta( double a, double b );
	double Poisson( double xlambda );
	double Weibull( double s, double t );

    vector<int> Shuffle (int n);
    
	void See();
};

#endif //__Alea_h__


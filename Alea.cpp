#ifndef	__Alea_h__
#include "Alea.h"
#endif

Alea::Alea()
{	
	time_t now;
	unsigned int seed = (unsigned int)time( &now );
	srand( seed );
	rand_max = (double)RAND_MAX;
	////cout << "rand_max: " << rand_max << endl;
}

double Alea::Uniform( double kmin, double kmax )
{
	return ( (kmax - kmin) * ( rand() / rand_max ) + kmin );
}

double Alea::Linear()
{
	double r1, r2;
	r1 = Uniform( 0., 1. );
	r2 = Uniform( 0., 1. );

	if( r2 < r1 )
		r1 = r2;

	return r1;
}

double Alea::ReverseLinear()
{
	double r1, r2;
	r1 = Uniform( 0., 1. );
	r2 = Uniform( 0., 1. );

	if( r2 > r1 )
		r1 = r2;

	return r1;
}

double Alea::Triangular()
{
	double r1, r2;
	r1 = Uniform( 0., 1. );
	r2 = Uniform( 0., 1. );

	r1 = 0.5 * ( r1 + r2 );

	return r1;
}

double Alea::Exponential( double lambda )
{
	double r0;

	while(1)
	{
		r0 = Uniform( 0., 1. ) / lambda;
		if( r0 != 0. )
			break;
	}

	return ( -log( r0 ) );
}

double Alea::BiExpon( double lambda )
{
	double r0;

	while(1)
	{
		r0 = 2. * Uniform( 0., 1. );
		if( r0 != 0 && r0 != 2. )
			break;
	}

	if( r0 > 1. )
	{
		r0 = 2. - r0;
		return ( -log( r0 ) / lambda );
	}
	else
		return ( log(r0) / lambda );
}

double Alea::Gaussian( double sigma, double xmu, long N )
{	
	// sigma = deviation; xmu = mean; N = number of random values added together
	if( (N % 2) != 0 )
	{
		cerr << "N must be an even number > 1 in Alea::Gaussian( double sigma, double xmu, long N )" << endl;
		exit(8);
	}
	double No2 = N / 2.;
	double scale;
	scale = 1. / (sqrt( N / 12. ));
	double sum = 0.;

	while( --N >= 0 )
	{
		sum += Uniform( 0., 1. );
	}
	////cout << sigma << " " << scale << " " << sum << " " << No2 << " " << xmu << endl;

	return ( sigma * scale * (sum - No2) + xmu );
}

double Alea::Cauchy( double alpha )
{
	double r0;

	while(1)
	{
		r0 = Uniform( 0., 1. );
		if( r0 != 0.5 )
			break;
	}

	r0 *= PI;

	return ( alpha * tan( r0 ) );
}

double Alea::Beta( double a, double b )
{
	double r0, r1, s1, s2, sum;
	double ainv = 1. / a;
	double binv = 1. / b;

	while(1)
	{
		while(1)
		{
			r0 = Uniform( 0., 1. );
			if( r0 != 0. )
				break;
		}

		while(1)
		{
			r1 = Uniform( 0., 1. );
			if( r1 != 0. )
				break;
		}

		s1 = pow( r0, ainv );
		s2 = pow( r1, binv );
		sum = s1 + s2;

		if( sum <= 1. )
			break;
	}

	return ( s1 / sum );
}

double Alea::Poisson( double xlambda )
{
	double N = 0.;
	double r0 = Uniform( 0., 1. );
	double v = exp( -xlambda );

	while(1)
	{
		if( r0 >= v )
		{
			N++;
			r0 *= Uniform( 0., 1. );
		}
		else
		{
			return N;
			break;
		}
	}
}

double Alea::Weibull( double s, double t )
{
	double a, r0;
	while(1)
	{
		r0 = Uniform( 0., 1. );
		if( r0 != 0. && r0 != 1. )
			break;
	}
	a = 1. / (1. - r0);
	return ( s * ( pow( log(a), (1. / t) ) ) );
}

void Alea::See()
{
	long count = 20;
	double result;

	while( count > 0 )
	{
		//result = Uniform( -1., 1. );
		//result = Linear();
		//result = Triangular();
		//result = Exponential( 6 );
		//result = BiExpon( 2 );
		//result = Gaussian( 0.5, 0., 12 );
		//result = Cauchy( 0.5 );
		//result = Beta( 0.4, 0.8 );
		result = Poisson( 100. );
		//result = Weibull( 0.8, 0.99 );
		//cout << result << endl;
		--count;
	}
}

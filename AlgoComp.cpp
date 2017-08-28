
#include <string.h> 
#include "AlgoComp.h" 
#include "TextIO.h"
#include "Alea.h"
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

 
#if 0 
AlgoComp::AlgoComp() 
{ 
 
} 
 
AlgoComp::~AlgoComp() 
{ 
 
} 
#endif
 
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

int decode_shorthand_length (int s) {
// . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |	
	//int code = s;
	switch (s) {
		case 46:
			return 1;
		case 73:
			return 2;
		case 58:
			return 2;
		case 47:
			return 2;
		case 88:
			return 2;
		case 62:
			return 3;
		case 60:
			return 3;
		case 43:
			return 3;
		case 105:
			return 3;
		case 45:
			return 3;
		case 126:
			return -1;
		case 40:
			return -2;
		case 41:
			return -3;
		default:
			return 0;
	}
	
	
}

string decode_shorthand_symbol (int s) {
	// . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |	
	//int code = s;
	string code = "";
	switch (s) {
		case 46:
			code = "1";
			break;
		case 73:
			code = "10";
			break;
		case 58:
			code = "11";
			break;
		case 47:
			code = "01";
			break;
		case 88:
			code = "110";
			break;
		case 62:
			code = "101";
			break;
		case 60:
			code = "101";
			break;
		case 43:
			code = "011";
			break;
		case 105:
			code = "111";
			break;
		case 45:
			code = "100";
			break;
		case 126:
			code = "";
			break;
		case 40:
			code = "";
			break;
		case 41:
			code = "";
			break;
		default:
			return code;
	}
	
	return code;
}


int Round( double x ) 
{ 
	// rounds a double and converts it to int 
	return (int)( x + 0.5 ); 
} 
 
int Ceiling( double x ) 
{ 
	int temp = (int)x; 
	double rest = 0.; 
	rest = x - temp; 
	if( rest > 0. ) 
	{ 
		return (temp + 1); 
	} 
	else if( rest < 0. ) 
	{ 
		return (temp - 1); 
	} 
	else 
	{ 
		return temp; 
	} 
} 
	 
float Floor (float x)
{
    return (float(int (x)));
}

double Normalize( double x, double unten, double oben, double xmin, double xmax ) 
 	{ 
 	return ( ( oben - unten ) * ( x - xmin ) / ( xmax - xmin ) + unten ); 
 	}	 
 
int GGT( int a, int b ) 
	{ 
	if (!a || !b) 
		return 0; 
	if( b > a ) 
		{ 
		int oldb = b; 
		b = a; 
		a = oldb; 
		} 
	 
	int c = 1; 
	 
	while( c ) 
		{ 
		c = a % b; 
		a = b; 
		b = c; 
		} 
	 
	return a; 
	} 
	 
int Compare( double da, double db ) 
	{ 
	float a = (float)da; 
	float b = (float)db; 
	 
	int result = 0; 
	 
	if( a == b ) 
		 result = 0; 
	 
	else if( a > b ) 
		result = 1; 
	 
	else if( a < b ) 
		result = -1; 
	 
	return result; 
	} 
 
void Swap( double a, double b ) 
	{ 
	double aux = 0; 
	aux = a; 
	a = b; 
	b = aux; 
	} 
	 
void SortInt( int* inlist, int length ) 
	{ 
	for( int k = 0; k < length - 1; k ++ ) 
		{ 
		for( int j = k+1; j < length; j++ ) 
			{ 
			if( inlist[j] < inlist[k] ) 
				{ 
				int aux; 
				aux = inlist[k]; 
				inlist[k] = inlist[j]; 
				inlist[j] = aux; 
				} 
			} 
		} 
	} 
 
void SortDoub( double* inlist, int length ) 
	{ 
	for( int k = 0; k < length - 1; k ++ ) 
		{ 
		for( int j = k+1; j < length; j++ ) 
			{ 
			if( inlist[j] < inlist[k] ) 
				{ 
				double aux; 
				aux = inlist[k]; 
				inlist[k] = inlist[j]; 
				inlist[j] = aux; 
				} 
			} 
		} 
	} 
		 
 
 
void PrimFaktoren (int enteger, DList<Power>* p) 
{ 
    if (enteger == 0)
    {
	Power* np = new Power; 
	np->SetP (0); 
	np->SetQ (0); 
	p->append (np); 
	return; 
    }
	int i = 0; 
	int i_exp = 0; 
	while (i < MAX_PRIMES) 
	{ 
		if (enteger == primes[i]) 
		{ 
			Power* np = new Power; 
			np->SetP (enteger); 
			np->SetQ (1); 
			p->append (np); 
			return; 
		} 
		while (!(enteger % primes[i])) 
		{ 
			i_exp++; 
			enteger /= primes[i]; 
		} 
		if (i_exp) 
		{ 
			Power* np = new Power; 
			np->SetP (primes[i]); 
			np->SetQ (i_exp); 
			p->append (np); 
		} 
		i++; 
		if (primes[i] > enteger) 
			return; 
		i_exp = 0; 
	} 
} 
		 
DList<int>* GenerateSmoothTable (DList<int>* plist, int limit) 
{ 
	DList<int>* stable = new DList<int>; 
	int i = 1; 
	for (;  i < limit; i++) 
	{ 
		DList<Power>* powerlist = new DList<Power>; 
		PrimFaktoren (i, powerlist); 
		// Power := p^q 
		DLink<int>* plist_link = plist->first (); 
		DLink<Power>* powerlist_link = powerlist->first (); 
 
		// find out whether powerlist is a subset of plist 
		// if yes append i to the result 
		int isequal = 0; 
		for (; powerlist_link != NULL; powerlist_link = powerlist_link->next) 
		{ 
			isequal = 0; 
			for (plist_link = plist->first (); plist_link != NULL; plist_link = plist_link->next) 
			{ 
				if (*plist_link->data == powerlist_link->data->GetP ()) 
					isequal = 1; 
			} 
			if (!isequal) 
				break; 
		} 
		if (isequal) 
			stable->append (new int(i)); 
		 
	} 
	return stable;	 
} 
		 
 
double Digest (int enteger) 
{ 
    if (!enteger) 
	return 0.; 

//    if (enteger == 2)
    //return 1.f;
    
    double result = 0.;	 
    int i = 0; 
    int exponent = 0; 
    while( i < MAX_PRIMES ) 
    { 
	int prime = primes[i];
	if (enteger == prime) 
	{ 
	    result += (((prime - 1)*(prime - 1)) / double (prime)); 
	    return (result * 2.); 
	} 
	while (!(enteger % prime)) 
	{ 
	    exponent++; 
	    enteger /= prime; 
	} 
	if (exponent) 
	{
	    result += (exponent * (((prime - 1)*(prime - 1)) / double (prime)));
	} 
	i++; 
	exponent = 0; 
    } 
    return (result * 2.); 
} 
 
// if all integers whose digest value is smaller than  
// Digest (n) are filtered out from a Farey Sequence F(m) 
// then the resulting list of ratios is the optimised search space 
// for quantisation against the ratios of this list 
// if the number of beats in the sequence to be quantised 
// is a prime number n \> 2 
double Harmon( int p, int q ) 
	{ 
	double dp = Digest( p ); 
	double dq = Digest( q ); 
	double dggt = Digest( GGT(p, q) ); 
	 
	int signumb = 1; 
	 
	if( (dp - dq) < 0. ) 
		signumb = -1; 
	 
	double dadd = dp + dq; 
	 
	double result = 0.; 
	// after hajdu 
	result = signumb / (dadd - 2 * dggt); 
	 
	return result; 
	} 

double Harmon3( int p, int q ) 
	{ 
	double dp = Digest( p ); 
	double dq = Digest( q ); 
	//double dggt = Digest( GGT(p, q) ); 
	 
	int signumb = 1; 
	 
	if( (dp - dq) < 0. ) 
		signumb = -1; 
	 
	double dadd = dp + dq; 
	 
	double result = 0.; 
	// after barlow
	result = signumb / dadd; 
	 
	return result; 
	} 
 
double Harmon2( int p, int q ) 
{ 
	if (!p || !q) 
		return double (0.); 
	if (p == q) 
		return double (1.); 
	double dp = Digest (p); 
	double dq = Digest (q); 
	double dggt = Digest (GGT (p, q)); 
	 
	double dadd = dp + dq; 
	 
	return (1. / dadd - 2. * dggt); 
} 
	 
double NormGauss( double x, double mittel, double varianz ) 
	{ 
	double sqrt2pi = 2.506628275; 
	double twovar = varianz * varianz; 
	double xminmittel = x - mittel; 
	double result = 0.; 
	 
	result = ( 1 / varianz * sqrt2pi ) * exp( -( xminmittel * xminmittel ) / ( 2 * twovar ) ); 
	 
	return result; 
	} 
	 
	 
double CalcInterval( double p, double q ) 
	{ 
	double result = 0.; 
	 
	result = ( log(p/q) / log(2) ) * 1200.; 
	 
	return result; 
	} 
 
void Reverse(char s[]) 
{ 
	int c, i, j; 
	 
	for(i=0, j=strlen(s)-1; i<j; i++, j--) 
		{ 
		c = s[i]; 
		s[i] = s[j]; 
		s[j] = c; 
		} 
} 
 
void Itoa( int n, char s[] ) 
	{ 
	int i, sign; 
	sign = n; 
	i = 0; 
	do{ 
		s[i++] = abs(n%10) + '0'; 
	} while ((n/=10) != 0); 
	if (sign <0) 
		s[i++] = '-'; 
	s[i] = '\0'; 
	Reverse(s); 
	} 
 
double Clipping( double input, double clipmin, double clipmax ) 
{ 
	if( input < clipmin ) 
		return clipmin; 
	else if( input > clipmax ) 
		return clipmax; 
	else 
		return input; 
} 
 
double MIDItoFreq( double midinote ) 
	{ 
	double var = ( ( midinote - 69. ) * 100. ) / 1200.; 
	return ( (pow( 2.0, var )) * 440. ); 
	} 
 
double CentsToRatio( double cents ) 
{ 
	return ( pow( 2.0, ( cents / 1200. ) ) ); 
} 
 
double RatioToCents( double ratio ) 
{ 
	return ( ( log(ratio) / log(2) ) * 1200. ); 
} 
 
double FreqtoMIDI( double p ) 
	{ 
	return ( ( ( ( log(p/440.0) / log(2) ) * 1200.0 ) + 6900.0) / 100.0); 
	} 
	 
double MMtoF( double mm ) 
{ 
	return (mm / 60.0); 
} 
 
// how many beats n in x bpm are in y secs? 
// n = y * MMtoF( x ) 
 
double FtoMM( double freq ) 
{ 
	return (freq * 60.0); 
} 
 
double mstof( double msecs ) 
{ 
	return (1.0/(msecs/1000.0)); 
} 
 
double mstoMM( double msecs ) 
{ 
	return ((mstof(msecs))*60.0); 
} 
 
double QtoMM( double p, double q, double refmm) 
{ 
// give me the tempo p/q times a reference BPM 
	return ( ( refmm / p ) * q ); 
} 
 
double SampleFun( double i, double k, double amp, double x ) 
{ 
// sampling function sinc 
// i = bandwidth of central lobe 
// k = position of central lobe 
	double sincfun = 1.0; 
	double term; 
	if( ( x - k ) != 0. ) 
	{ 
		term = ( 1./i ) * PI * ( x - k ); 
		sincfun =  sin( term ) / term; 
	} 
	return ( sincfun  * amp ); 
} 
 
double SampleFun1( double k, double amp, double x ) 
{ 
// sampling function sinc 
// bandwidth of central lobe = 1 
// k = position of central lobe 
	double sincfun = 1.0; 
	double term; 
	if( ( x - k ) != 0. ) 
	{ 
		term = PI * ( x - k ); 
		sincfun =  sin( term ) / term; 
	} 
	return ( sincfun  * amp ); 
} 
 
double SampleFunSq( double i, double k, double amp, double x ) 
{ 
// sampling function sinc^2 
// i = bandwidth of central lobe 
// y = 0.64 == -3.87 dB 
// k = position of central lobe 
	double sincfun = 1.0; 
	double term; 
	if( ( x - k ) != 0. ) 
	{	 
		term = ( 1./i ) * PI * ( x - k ); 
		sincfun =  sin( term ) / term; 
	} 
	return (sincfun * sincfun * amp); 
} 
 
double AmpToDB( double linamp, double refdb ) 
{ 
	linamp /= refdb; 
	if( linamp <= 0. ) 
		linamp = 0.00000001; 
	 
	return 20 * log10( linamp ); 
} 
 
double DBtoAmp( double db, double refdb ) 
{ 
	return refdb * pow( 10, ( db/20. ) ); 	 
} 
	 
double radius( double x, double y ) 
{ 
	return sqrt( pow(x, 2) + pow(y, 2) );	 
} 
 
double theta( double x, double y ) 
{ 
	return atan2( y, x ); 
} 
 
void Polar2Cart( double* r, double* th ) 
{ 
	// converts polar coordinates to cartesian in place 
	// r (radius) -> x 
	// th (angle) -> y 
	double x,y; 
	x = *r; y = *th; 
	*r = x * cos( y ); 
	*th = x * sin( y ); 
	 
} 
 
void Cart2Polar( double* x, double* y ) 
{ 
	// converts cartesian coordinates to polar in place 
	// x -> radius 
	// y -> angle 
	double r, th; 
	r = *x; th = *y; 
	*x = radius( r, th ); 
	*y = theta( r, th ); 
} 
 
double gammaDeg( double x ) 
{ 
	// x in degrees 
	return (180 - 2 * x) * CGRD; 
} 
 
double R( double x, double y, double beta ) 
{ 
	// beta in degrees 
	double g = gammaDeg( beta ); 
	return radius(x,y) * sin( beta * CGRD ) / sin( g ); 
} 
 
double phi( double sigma, double beta ) 
{ 
	// beta & sigma in degrees 
	double g = gammaDeg( beta ); 
	return 0.5 * ( g - sigma * CGRD ); 
} 
 
unsigned long factorial( unsigned long i ) 
{ 
	unsigned long res = i; 
	while( --i > 0 ) 
		res *= i; 
	return res; 
} 
 
unsigned long binominal( unsigned long n, unsigned long i ) 
{ 
	return factorial( n ) / ( factorial( i ) * factorial( n-1 ) ); 
} 
 
double bernstein( double x, unsigned long n, unsigned long i ) 
{ 
	return (double)binominal( n, i ) * pow( x, i ) * (double)pow( (1-x), (n-i) ); 
} 
 
double csc( double theta ) 
{ 
	double result = sin(theta); 
	if( !result ) 
		return result; 
	return 1.; 
} 
 
void DDvector( double r, double phi, double lambda, dreiP* rectP ) 
{ 
	rectP->x = r * cos(phi*CGRD) * cos(lambda*CGRD); 
	rectP->y = r * cos(phi*CGRD) * sin(lambda*CGRD); 
	rectP->z = r * sin(phi*CGRD); 
} 
 
void DDvectorRev( double* r, double* phi, double* lambda, dreiP* rectP ) 
{ 
	*r = sqrt( (rectP->x*rectP->x) + (rectP->y*rectP->y) + (rectP->z*rectP->z) ); 
	*phi = atan2(rectP->z , (sqrt((rectP->x*rectP->x) + (rectP->y*rectP->y)))); 
	*lambda = atan2(rectP->y , rectP->x); 
}	 
	 
int Signum( double x_ ) 
{ 
	if( x_ >= 0. ) 
		return 1; 
	return -1; 
}	 
 
string GetTimeStamp(long* now) 
{ 
	char* stamp; 
	struct tm* date; 
	date = localtime( now ); 
	stamp = asctime( date );	 
	return	string(stamp); 
} 
 
int GetGGTOfRatioNomList (DList<Ratio>& rlist) 
{ 
	if (rlist.GetSize () < 2) 
		return 1; 
	DLink<Ratio>* r1 = rlist.first (); 
	int p1,p2; 
	p1 = r1->data->GetP (); 
	p2 = r1->next->data->GetP (); 
	int ggt = GGT (p1, p2); 
	r1 = r1->next; 
	for (; r1->next != NULL; r1 = r1->next) 
	{ 
		p1 = r1->data->GetP (); 
		p2 = r1->next->data->GetP (); 
		int temp = GGT (p1, p2); 
		if (ggt != temp) 
		{ 
			if ((GGT (ggt, temp)) == 1) 
				return 1; 
			else 
				ggt = GGT (ggt, temp); 
		} 
	} 
	return ggt; 
} 

int GetGGTOfRatioDenomList (DList<Ratio>& rlist) 
{ 
	if (rlist.GetSize () < 2) 
		return 1; 
	DLink<Ratio>* r1 = rlist.first (); 
	int p1,p2; 
	p1 = r1->data->GetQ (); 
	p2 = r1->next->data->GetQ (); 
	int ggt = GGT (p1, p2); 
	r1 = r1->next; 
	for (; r1->next != NULL; r1 = r1->next) 
	{ 
		p1 = r1->data->GetQ (); 
		p2 = r1->next->data->GetQ (); 
		int temp = GGT (p1, p2); 
		if (ggt != temp) 
		{ 
			if ((GGT (ggt, temp)) == 1) 
				return 1; 
			else 
				ggt = GGT (ggt, temp); 
		} 
	} 
	return ggt; 
} 
 
bool AreRatioListsEqual (DList<Ratio>* list_a, DList<Ratio>* list_b)
{
    if (list_a->GetSize () != list_b->GetSize ())
	return false;

    DLink<Ratio>* a = list_a->first ();
    DLink<Ratio>* b = list_b->first ();

    DList<Ratio>* alist = new DList<Ratio>;
    DList<Ratio>* blist = new DList<Ratio>;
    for (; a != NULL && b != NULL; a = a->next, b = b->next)
    {
	Ratio* ainv = new Ratio;
	ainv->SetP (1);
	ainv->SetQ (a->data->GetP ());
	alist->append(ainv);

	Ratio* binv = new Ratio;
	binv->SetP (1);
	binv->SetQ (b->data->GetP ());
	blist->append(binv);
    }

    int lcd_a = GetGGTOfRatioNomList (*list_a);
    int lcd_b = GetGGTOfRatioNomList (*list_b);

    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << "lcd_a: " << lcd_a << " lcd_b: " << lcd_b << endl;

// if a numerator == 1 we say the list normalised
    int norm_a = 0;
    int norm_b = 0;
   
    a = list_a->first ();
    b = list_b->first ();
   
    for (; a != NULL && b != NULL; a = a->next, b = b->next)
    {
	if (a->data->GetP() == 1)
	    norm_a = 1;
	if (b->data->GetP() == 1)
	    norm_b = 1;
    }

    a = list_a->first ();
    b = list_b->first ();

    for (; a != NULL && b != NULL; a = a->next, b = b->next)
    {
      //int anum = a->data->GetP ();
      //int bnum = b->data->GetP ();
	if (norm_a && norm_b)
	{
	    cout << "\t (a->data->GetP ()) := " << (a->data->GetP ()) << " (b->data->GetP()) := " << (b->data->GetP()) << endl;
	    if ((a->data->GetP ())  != (b->data->GetP()))
		return false;
	}
	else if (norm_a && !norm_b)
	{
	    cout << "\t (a->data->GetP ()) := " << (a->data->GetP ()) << " (b->data->GetP() / lcd_b) := " << (b->data->GetP() / lcd_b) << endl;
	    if ((a->data->GetP ())  != (b->data->GetP() / lcd_b))
		return false;
	}
	else if (!norm_a && norm_b)
	{
	    cout << "\t (a->data->GetP () / lcd_a) := " << (a->data->GetP () / lcd_a) << " (b->data->GetP()) := " << (b->data->GetP()) << endl;
	    if ((a->data->GetP () / lcd_a)  != (b->data->GetP()))
		return false;
	}
	else if (!norm_a && !norm_b)
	{
	    cout << "\t (a->data->GetP () / lcd_a) := " << (a->data->GetP () / lcd_a) << " (b->data->GetP() / lcd_b) := " << (b->data->GetP() / lcd_b) << endl;
	    if ((a->data->GetP () / lcd_a)  != (b->data->GetP()  / lcd_b))
		return false;
	}
    }
    return true;
}

int GetLCDOfRatioList (DList<Ratio>& rlist) 
{ 
	DLink<Ratio>* r1; 
	DList<Power>* prime_factors = new DList<Power>; 
 
	for (r1 = rlist.first (); r1 != NULL; r1 = r1->next) 
		PrimFaktoren (r1->data->GetQ (), prime_factors); 
 
	DList<Power>* max_prime_factors = new DList<Power>; 
	DLink<Power>* p1; 
	int i = 0; 
	for (; i < MAX_PRIMES; i++) 
	{ 
	    Power cur_pow; // p^q 
	    cur_pow.SetP (primes[i]); 
	    cur_pow.SetQ (0); 
	    for (p1 = prime_factors->first (); p1 != NULL; p1 = p1->next) 
	    { 
		if (p1->data->GetP () == cur_pow.GetP ()) 
		    if (p1->data->GetQ () > cur_pow.GetQ ()) 
			cur_pow.SetQ (p1->data->GetQ ()); 
		
	    } 
	    if (cur_pow.GetQ ()) 
	    { 
		Power* p = new Power; 
		p->SetP (cur_pow.GetP ()); 
		p->SetQ (cur_pow.GetQ ()); 
		max_prime_factors->append (p); 
	    } 
		
	} 
 
	DLink<Power>* mp; 
	int result = 1; 
	for (mp = max_prime_factors->first (); mp != NULL; mp = mp->next) 
	    result *= mp->data->GetVal (); 
	delete prime_factors; 
	delete max_prime_factors; 
 
	if (result < 1) 
	    result = 1; 
	return result; 
 
} 
 
int GetFirstPrimeLower (int i) 
{ 
	int k = 0; 
	for (; k < MAX_PRIMES; k++) 
	{ 
		if (primes[k] > i) 
			return primes[k-1]; 
	} 
		 
	return primes[MAX_PRIMES-1]; 
} 

bool is_prime (int n)
{
    int k = 0;
    for (; k < MAX_PRIMES; k++)
    {
	if (primes[k] == n)
	    return true;
    }
    return false;
}
 
//******************************************************************************* 
 
void float_to_cfrac ( double r, int n, int a[], int p[], int q[] ) 
 
//******************************************************************************* 
// 
//  Purpose: 
// 
//    D_TO_CFRAC converts a double value to a continued fraction. 
// 
//  Discussion: 
// 
//    The routine is given a double number R.  It computes a sequence of 
//    continued fraction approximations to R, returning the results as 
//    simple fractions of the form P(I) / Q(I). 
// 
//  Example: 
// 
//    X = 2 * PI 
//    N = 7 
// 
//    A = [ *, 6,  3,  1,  1,   7,   2,    146,      3 ] 
//    P = [ 1, 6, 19, 25, 44, 333, 710, 103993, 312689 ] 
//    Q = [ 0, 1,  3,  4,  7,  53, 113,  16551,  49766 ] 
// 
//    (This ignores roundoff error, which will cause later terms to differ). 
// 
//  Modified: 
// 
//    09 March 2005 
// 
//  Author: 
// 
//    John Burkardt 
// 
//  Reference: 
// 
//    Norman Richert, 
//    Strang's Strange Figures, 
//    American Mathematical Monthly, 
//    Volume 99, Number 2, February 1992, pages 101-107. 
// 
//  Parameters: 
// 
//    Input, double R, the double value. 
// 
//    Input, int N, the number of convergents to compute. 
// 
//    Output, int A[N+1], the partial quotients. 
// 
//    Output, int P[N+2], Q[N+2], the numerators and denominators 
//    of the continued fraction approximations. 
// 
{ 
  int i; 
  double r_copy; 
  double x[1024];
 
  if ( r == 0.0E+00 ) 
  { 
    for ( i = 0; i <= n; i++ ) 
    { 
      a[i] = 0; 
    } 
    for ( i = 0; i <= n+1; i++ ) 
    { 
      p[i] = 0; 
    } 
    for ( i = 0; i <= n+1; i++ ) 
    { 
      q[i] = 0; 
    } 
    return; 
  } 
 
//  x = new double[n+1]; 
 
  r_copy = fabs ( r ); 
 
  p[0] = 1; 
  q[0] = 0; 
 
  p[1] = ( int ) r_copy; 
  q[1] = 1; 
  x[0] = r_copy; 
  a[0] = ( int ) x[0]; 
 
  for ( i = 1; i <= n; i++ ) 
  { 
    x[i] = 1.0E+00 / ( x[i-1] - ( double ) a[i-1] ); 
    a[i] = ( int ) x[i]; 
    p[i+1] = a[i] * p[i] + p[i-1]; 
    q[i+1] = a[i] * q[i] + q[i-1]; 
  } 
 
  if ( r < 0.0E+00 ) 
  { 
    for ( i = 0; i <= n+1; i++ ) 
    { 
      p[i] = -p[i]; 
    } 
  } 
 #if 0
  for ( i = 1; i <= n; i++ ) 
  {
      if (&x[i] != NULL)
	  delete &x[i]; 
  }
#endif

  return; 
} 
 
bool IsPowerOfTwo(int x) 
{ 
    if (x < 2) 
	return false; 
    
    if (x & (x - 1)) 
	return false; 
    
    return true; 
} 
 
int BiggestPowerOfTwoBelow (int x) 
{ 
    if (x < 2) 
	return 1; 
    while (!IsPowerOfTwo (x)) 
    { 
	--x; 
    } 
    return x; 
} 
 
void ToBinary (int x)
{
    cout << x << " = " ;
    while (x > 0) {
	int p = BiggestPowerOfTwoBelow (x);
	cout << p << " " ;
	float l = log (p) / log (2);
	cout << "(2^" << l << ") + ";
	x -= p;
    }
    cout << endl;
}

int BinaryRoot (int x)
{
    // the sum of all digits in binary mod 2
    // after Schroeder, M. (1991). Fractals, Chaos, Power Laws. Freeman , New York. ISBN 0-7167-2136-8
    int i = 0;
    while (x > 0) {
	int p = BiggestPowerOfTwoBelow (x);
	i++;
	x -= p;
    }
    return (i%2);
}

void TransIntToList (int x, DList<int>& intlist) 
{ 
	while (x > 0) 
	{ 
		int pow2 = BiggestPowerOfTwoBelow(x); 
		intlist.append (new int(pow2));	 
		x -= pow2; 
	} 
} 
 
 
void WorkListToDotted (DList<int>& intlist) 
{ 
	if (intlist.GetSize () < 2) 
		return; 
	DLink<int>* item = intlist.first (); 
	Ratio* first = new Ratio (0,1); 
	Ratio* test = new Ratio (2,1); 
	if (intlist.GetSize () < 3) 
	{		 
		first->SetP (*item->data); 
		first->SetQ (*item->next->data); 
		first->AutoReduce (); 
		if (*first == *test) 
			*item->next->data = -1; 
 
		delete first; 
		delete test; 
		return; 
	} 
	Ratio* second = new Ratio (0,1); 
 
	for (item = intlist.first (); item != NULL; item = item->next) 
	{ 
		if (item->next != NULL) 
		{ 
			int a = *item->data; 
			int b = *item->next->data; 
			if ( a < 0 || b < 0) 
				continue; 
			first->SetP (*item->data); 
			first->SetQ (*item->next->data); 
			first->AutoReduce (); 
			if (*first == *test) 
			{ 
				if (item->next->next != NULL) 
				{ 
					int c = *item->next->next->data; 
					if (c < 0) 
						break; 
					second->SetP (b); 
					second->SetQ (c); 
					second->AutoReduce (); 
					if (*second == *test) 
						*item->next->next->data = -2; 
				}	 
				*item->next->data = -1; 
			} 
		} 
	} 
 
	delete first; 
	delete second; 
	delete test; 
	return; 
} 
 
 
 
int BeatGridUnderRatioList (DList<Ratio>& rlist, Ratio& beat) 
{ 
	int result = 0; 
	DList<Ratio>* AcRat = new DList<Ratio>; 
	DList<Ratio>* AcBt = new DList<Ratio>; 
	//AcRat->append (new Ratio (0,1)); 
	Ratio* accum = new Ratio (0,1); 
	// accumulate ratios from bucket list to find out how large bucket is 
	//cout << "Accumulate Ratios:" << endl; 
	DLink<Ratio>* rlist_el = rlist.first (); 
	for (; rlist_el != NULL; rlist_el = rlist_el->next) 
	{ 
		Ratio* temp = new Ratio(*(rlist_el->data)); 
		*temp + *accum; 
		temp->AutoReduce (); 
		AcRat->append (temp); 
		*accum = *temp; 
		//cout << (temp->GetP ()) << " / " << (temp->GetQ ()) << " = " << (temp->GetFloat ()) << endl; 
	} 
 
	// find ratio of bucket frame over beat size: 
	Ratio* max = new Ratio (0,1); 
	rlist_el = AcRat->last (); 
	*max = *rlist_el->data; 
	Ratio* beatval = new Ratio (1, beat.GetQ ()); 
	*max / *beatval; 
	max->AutoReduce (); 
 
	// make a list of accumulating beats up to size of bucket 
	accum->SetP (0); accum->SetQ (1); 
	*accum + *beatval; 
	int countmax = int (max->GetFloat ()); 
	//countmax++; 
	int i = 0; 
	//cout << "Accumulate Beats:" << endl; 
	for (; i < countmax; i++) 
	{ 
		Ratio* temp2 = new Ratio (*accum);  
		AcBt->append (temp2);	 
		*accum + *beatval; 
		//cout << (temp2->GetP ()) << " / " << (temp2->GetQ ()) << " = " << (temp2->GetFloat ()) << endl; 
	 
	} 
 
	DLink<Ratio>* acbt = AcBt->first (); 
	DLink<Ratio>* acrat = AcRat->first (); 
	rlist_el = rlist.first (); 
	while (acbt != NULL && acrat != NULL) 
	{ 
		// write the vectors of beats that fall within ratio into list of ratio object 
		if (acbt->data->GetFloat () < acrat->data->GetFloat ()) 
		{ 
			Ratio* bt_in = new Ratio (*acrat->data); 
			*bt_in - *acbt->data; 
			Ratio* bt_in2 = new Ratio (*rlist_el->data); 
			*bt_in2 - *bt_in; 
			bt_in2->AutoReduce (); 
			if (bt_in2->GetP ()) // if ratio != 0 
				rlist_el->data->GetList ()->append (bt_in2); 
			acbt = acbt->next; 
			delete bt_in; 
			result++; 
		} 
		else 
		{ 
			acrat = acrat->next; 
			rlist_el = rlist_el->next; 
		} 
	} 
 
	rlist_el = rlist.first (); 
	while (rlist_el != NULL) 
	{ 
	    //cout << "Note: " << (rlist_el->data->GetP ()) << " / " << (rlist_el->data->GetQ ()) << endl; 
		if (rlist_el->data->GetList ()->GetSize () > 0) 
		{ 
			DLink<Ratio>* sublist = rlist_el->data->GetList ()->first (); 
			while (sublist != NULL) 
			{ 
			    //cout << "beat: " << (sublist->data->GetP ()) << " / " << (sublist->data->GetQ ()) << endl; 
				sublist = sublist->next;	 
			} 
		} 
		rlist_el = rlist_el->next; 
	} 
 
	delete AcRat; 
	delete AcBt; 
	delete max; 
	delete beatval; 
	delete accum; 
 
	return result; 
} 
 
void ReformRatioList (DList<void>* grouplist, DList<Ratio>* inlist) 
{ 
	DLink<Ratio>* rlist_el = inlist->first (); 
	grouplist->destroy (); 
	while (rlist_el != NULL) 
	{ 
		DList<Ratio>* sublist = new DList<Ratio>; 
		grouplist->append (sublist); 
		 
		Ratio* raframe = new Ratio(*rlist_el->data); 
		if (rlist_el->data->GetList ()->GetSize () > 0) 
		{ 
			DLink<Ratio>* subrlist_el = rlist_el->data->GetList ()->first (); 
			Ratio* rala = new Ratio (*subrlist_el->data); 
			sublist->append (rala); 
			if (subrlist_el->next == NULL) 
			{ 
				Ratio* ralb = new Ratio (*raframe); 
				*ralb - *rala; 
				ralb->AutoReduce (); 
				rala->SetTie (true); 
				sublist->append (ralb); 
				goto next; //break; 
			} 
			subrlist_el = subrlist_el->next; 
			while (subrlist_el != NULL) 
			{ 
				Ratio* ralp = new Ratio (*subrlist_el->previous->data); 
				Ratio* ralb = new Ratio (*subrlist_el->data); 
				*ralb - *ralp; 
				ralb->AutoReduce (); 
				DLink<Ratio>* curr_el = sublist->last (); 
				curr_el->data->SetTie (true); 
				sublist->append (ralb); 
				subrlist_el = subrlist_el->next; 
				delete ralp; 
			} 
			Ratio* ralb = new Ratio (*raframe); 
			//subrlist_el = rlist_el->data->GetList ()->last (); 
			DLink<Ratio>* curr_el = rlist_el->data->GetList ()->last (); 
			DLink<Ratio>* tie_el = sublist->last (); 
			tie_el->data->SetTie (true); 
			*ralb - *curr_el->data; 
			ralb->AutoReduce (); 
			sublist->append (ralb); 
		} 
		else 
			sublist->append (new Ratio (*raframe)); 
next: 
		rlist_el = rlist_el->next; 
		delete raframe; 
	} 
} 
 
void ReformRatioList2 (DList<void>* grouplist, DList<Ratio>* inlist) 
{ 
	inlist->destroy (); 
	DLink<void>* grouplist_el = grouplist->first (); 
	for (grouplist_el = grouplist->first (); grouplist_el != NULL; grouplist_el = grouplist_el->next) 
	{ 
		DList<Ratio>* slt = static_cast<DList<Ratio>*>(grouplist_el->data); 
		DLink<Ratio>* subl = slt->first (); 
		for (; subl != NULL; subl = subl->next) 
			inlist->append (new Ratio (*subl->data)); 
	} 
} 
 
void ReformRatioList3 (DList<void>* grouplist, DList<Ratio>* inlist, Ratio* beat) 
{ 
	Ratio* sum = new Ratio (0,1); 
	Ratio* beatval = new Ratio (1, beat->GetQ ()); 
	grouplist->destroy (); 
	DList<Ratio>* group = new DList<Ratio>; 
	grouplist->append (group); 
	DLink<Ratio>* inl = inlist->first (); 
	for (; inl != NULL; inl = inl->next) 
	{ 
		group->append (new Ratio (*inl->data)); 
		*sum + *inl->data; 
		sum->AutoReduce (); 
		if ((sum->GetP () == beatval->GetP ()) && (sum->GetQ () == beatval->GetQ ())) 
		{ 
			group = new DList<Ratio>; 
			grouplist->append (group); 
			sum->SetP (0); sum->SetQ (1); 
		} 
	} 
	delete sum; 
	delete beatval; 
} 
 
void ModifiedEngelExpansion (float x, DList<int>* smoothtable, DList<int>* result, int maxterms, int mode) 
{ 
	//ENgel expansion 
	// u1 = x 
	// a1 = ceiling_to_next_smooth_not_less_(1/u1) 
	// u2 = u1 * a1 - 1 
	// a2 = ceiling_to_next_smooth_not_less_(1/u2) etc. 
	result->destroy (); 
	//int smooth_length = smoothtable->GetSize (); 
	int i = 0; 
	float u = x; 
	float a = 0.f; 
	for (; i < maxterms; i++) 
	{ 
		float inter = 1.f / u; 
		float test = 0.f; 
		if (mode) 
		{ 
			DLink<int>* stable = smoothtable->first (); 
			for (; stable != NULL; stable = stable->next) 
			{ 
				test = (float)(*stable->data); 
				if (test >= inter) 
					break; 
			} 
		} 
		else 
		{ 
			DLink<int>* stable = smoothtable->last (); 
			for (; stable != NULL; stable = stable->previous) 
			{ 
				test = (float)(*stable->data); 
				if (test <= inter) 
					break; 
			} 
		} 
		a = test; 
		result->append (new int(a)); 
		u = u * a - 1.f; 
		if (u == 0.f) 
			break; 
	}	 
} 
 
void EngelExpansion (float x, DList<int>* result, int maxterms) 
{ 
	//ENgel expansion 
	// u1 = x 
	// a1 = ceiling_to_next_smooth_not_less_(1/u1) 
	// u2 = u1 * a1 - 1 
	// a2 = ceiling_to_next_smooth_not_less_(1/u2) etc. 
	result->destroy (); 
	//int smooth_length = smoothtable->GetSize (); 
	int i = 0; 
	float u = x; 
	float a = 0.f; 
	for (; i < maxterms; i++) 
	{ 
		float inter = 1.f / u; 
		inter += 1.f; 
		//int temp = (int)inter; 
		a = (float)((int)inter); 
		result->append (new int(a)); 
		u = u * a - 1.f; 
		if (u == 0.f) 
			break; 
	}	 
} 

void fomus_export (DList<DList<float> >* layers, string filename, string filepath, int meter1, int meter2, float beat_value, DList<float>* analysis)
{
    int note = 60;

    TextIO text (filename); 
    ofstream out; 
    text.TextWrite (out, filename); 

    out << "INIT :INPUT-BEAT-VALUE " << beat_value << endl;
    out << "INIT :output :lilypond" << endl;
    out << "INIT :filename \"" << filepath << "\"" << endl;
    out << "TIMESIG :off 0 :time (" << meter1 << " " << meter2 << ")" << endl << endl;

    int i = 1;
    DLink<DList<float> >* lll = layers->first ();
    if (1)
    {
	for (; lll != NULL; lll = lll->next, i++)
	{
	    float offset = 0;
	    out << "PART " << i << " :name \"layer"<< i << "\" :instr :flute" << endl << endl; 
	    DLink<float>* l = lll->data->first ();
	    float duration = *l->data;
	    note = note + 2;
	    for (; l != NULL; l = l->next)
	    {
//	    out << "*(l->next->data) " << *(l->next->data) << " *l->data " << *l->data << endl;
		//int duration = *(l->next->data) - *l->data;
	    
		if (duration > 0)
		{
		    out << "NOTE " << i << " :voice 1 :off " << offset << " :dur " << duration  << " :note " << note <<  endl;
		    analysis->append (new float (offset));
		}
		if (l->next == NULL)
		    break;
		duration = *(l->next->data) - *l->data;
		offset = *l->data;
	    } 
	    out << endl;
	}
    }

    out.close ();
    string fomus_str = "fomus -l " + filename;
    system (fomus_str.c_str());
}

void fomus_export_analysis (DList<onset_histo>* analysis, string filename, string filepath, int meter1, int meter2, float beat_value)
{
    int note = 60;

    TextIO text (filename); 
    ofstream out; 
    text.TextWrite (out, filename); 

    out << "INIT :INPUT-BEAT-VALUE " << beat_value << endl;
    out << "INIT :output :lilypond" << endl;
    out << "INIT :filename \"" << filepath << "\"" << endl;
    out << "TIMESIG :off 0 :time (" << meter1 << " " << meter2 << ")" << endl << endl;

    DList<DList<float> >* layers = new DList<DList<float> >;
    DLink<onset_histo>* ol = analysis->first ();
    int num_layers = 0;
    for (; ol != NULL; ol = ol->next)
    {
	if (ol->data->count > num_layers)
	    num_layers = ol->data->count;
    }

    int nl = num_layers;
    while (--nl >= 0)
    {
	layers->append (new DList<float>);
    }

    ol = analysis->first ();
    for (; ol != NULL; ol = ol->next)
    {
	DLink<DList<float> >* ll = layers->getAt ((ol->data->count) - 1);
	ll->data->append (new float(ol->data->onset));
    }
	
    int i = 1;
    DLink<DList<float> >* lll = layers->first ();
    for (; lll != NULL; lll = lll->next, i++)
    {
	DLink<float>* l = lll->data->first ();
	if (!l)
	    break;
	float offset = *l->data;
	out << "PART " << i << " :name \"layer"<< i << "\" :instr :flute" << endl << endl; 
	float duration = beat_value / 4.f;
	if (l->next != NULL)
	{
	    duration = *(l->next->data) - *l->data;
	}
	    
	note = 60 + i * 2;
	for (; l != NULL; l = l->next)
	{
	    if (l->next == NULL)
	    {
		duration = beat_value / 4.f;
	    }
	    else
		duration = *(l->next->data) - *l->data;
	    offset = *l->data;

	    if (duration > 0)
	    {
		out << "NOTE " << i << " :voice 1 :off " << offset << " :dur " << duration  << " :note " << note <<  endl;
	    }
	} 
	out << endl;
    }
    out.close ();

    string fomus_str = "fomus -l " + filename;
    system (fomus_str.c_str());
}

DList<onset_histo>* retention_analysis (DList<float>* analysis, string filename)
{
    TextIO text (filename); 
    ofstream out; 
    text.TextWrite (out, filename); 

    DList<onset_histo>* histo = new DList<onset_histo>;

    int total_length = analysis->GetSize ();
    float layerlist[total_length];
    cout << total_length << endl;
    memset (layerlist, 0, total_length * sizeof(float));
    DLink<float>* al = analysis->first ();
    int i = 0;
    for (; al != NULL; al = al->next)
    {
	layerlist[i++] = *al->data;
    }

    qsort (&layerlist, total_length, sizeof(float), sorting_layers);

    for (i=0; i<total_length; i++)
    {
	cout << layerlist[i] << ", ";
    }
    cout << endl;

    int k = 0;
    for (i=0; i<total_length; i++)
    {
	onset_histo* oh = new onset_histo;
	float onset = layerlist[i];
	cout << onset << " 1" ;
	oh->onset = onset;
	oh->count = 1;
	k = i+1;
	for (; k < total_length; k++)
	{
	    if (layerlist[k] == onset)
	    {
		++(oh->count); 
		cout << " " << (oh->count);  
	    
	    }
	    else
	    {
		cout << endl;
		break;
	    }
	}
	i = k-1;
	histo->append (oh);
    }
    DLink<onset_histo>* loh = histo->first ();
    for (; loh != NULL; loh = loh->next)
    {
	out << "onset: " << (loh->data->onset) << " count: " << (loh->data->count) << endl;
    }

    out.close ();
    return histo;
//    histo->destroy ();
//    delete histo;

}
 
int sorting_layers (const void* arg1, const void* arg2) 
{ 
    if (*(float*)arg1 == *(float*)arg2) 
        return 0; 
    else if (*(float*)arg1 < *(float*)arg2) 
        return -1; 
    else 
        return 1; 
}    

void proportion_series (float start, int iterations, float proportion)
{
    DList<float>* durs = new DList<float>;
    int i = 0;
    for (; i < iterations; i++)
    {
	durs->prepend (new float(start));
	cout << start << endl;
	start /= proportion;
    }
    cout << endl;
    DLink<float>* dl = durs->first ();
    cout << *dl->data << endl;
    for (; dl->next != NULL; dl = dl->next)
    {
	cout << (*dl->next->data - *dl->data) << endl;
    }
}

//****************************************************************************80

void i4_partition_next2 ( int n, int a[], int mult[], int *npart, bool *more )

//****************************************************************************80
//
//  Purpose:
//
//    I4_PARTITION_NEXT2 computes the partitions of the int N one at a time.
//
//  Discussion:
//
//    Unlike compositions, order is not important in a partition.  Thus
//    the sequences 3+2+1 and 1+2+3 represent distinct compositions, but
//    not distinct partitions.  Also 0 is never returned as one of the
//    elements of the partition.
//
//  Examples:
//
//    Sample partitions of 6 include:
//
//      6 = 4+1+1 = 3+2+1 = 2+2+2
//
//  Modified:
//
//    28 May 2003
//
//  Parameters:
//
//    Input, int N, the integer whose partitions are desired.
//
//    Output, int A[N].  A(I) is the I-th distinct part
//    of the partition, for I = 1, NPART.  Note that if a certain number
//    shows up several times in the partition, it is listed only
//    once in A, and its multiplicity is counted in MULT.
//
//    Output, int MULT[N].  MULT(I) is the multiplicity of A(I)
//    in the partition, for I = 1, NPART; that is, the number of repeated
//    times that A(I) is used in the partition.
//
//    Output, int *NPART, the number of distinct, nonzero parts in the
//    output partition.
//
//    Input/output, bool *MORE.  Set MORE = FALSE on first call.  It
//    will be reset TRUE on return with the first partition.
//    Keep calling for more partitions until MORE
//    is returned FALSE
//
{
  int iff;
  int is;
  int isum;
  static int nlast = 0;
//
//  On the first call, set NLAST to 0.
//
  if ( !( *more ) )
  {
    nlast = 0;
  }

  if ( n != nlast || ( !( *more ) ) )
  {
    nlast = n;
    *npart = 1;
    a[*npart-1] = n;
    mult[*npart-1] = 1;
    *more = mult[*npart-1] != n;
    return;
  }

  isum = 1;

  if ( a[*npart-1] <= 1 )
  {
    isum = mult[*npart-1] + 1;
    *npart = *npart - 1;
  }

  iff = a[*npart-1] - 1;

  if ( mult[*npart-1] != 1 )
  {
    mult[*npart-1] = mult[*npart-1] - 1;
    *npart = *npart + 1;
  }

  a[*npart-1] = iff;
  mult[*npart-1] = 1 + ( isum / iff );
  is = isum % iff;

  if ( 0 < is )
  {
    *npart = *npart + 1;
    a[*npart-1] = is;
    mult[*npart-1] = 1;
  }
//
//  There are more partitions, as long as we haven't just computed
//  the last one, which is N copies of 1.
//
  *more = mult[*npart-1] != n;

  return;
}

//****************************************************************************80

void i4_partition_print ( int n, int npart, int a[], int mult[] )

//****************************************************************************80
//
//  Purpose:
//
//    I4_PARTITION_PRINT prints a partition of an integer.
//
//  Discussion:
//
//    A partition of an int N is a representation of the integer as
//    the sum of nonzero integers:
//
//      N = A1 + A2 + A3 + ...
//
//    It is standard practice to gather together all the values that 
//    are equal, and replace them in the sum by a single term, multiplied
//    by its "multiplicity":
//
//      N = M1 * A1 + M2 * A2 + ... + M(NPART) * A(NPART)
//    
//    In this representation, every A is a unique positive number, and 
//    no M is zero (or negative).
//
//  Modified:
//
//    29 June 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the integer to be partitioned.
//
//    Input, int NPART, the number of "parts" in the partition.
//
//    Input, int A[NPART], the parts of the partition.  
//
//    Input, int MULT[NPART], the multiplicities of the parts.
//
{
  int i;

  cout << "  " << n << " = ";

  for ( i = 0; i < npart; i++ )
  {
    if ( 0 < i )
    {
      cout << " + ";
    }
    cout << mult[i] << " * " << a[i];
  }
  cout << "\n";


  return;
}



int partition_rhythm_print (int n, int npart, int a[], int mult[], int must_be_prime, int no_ones, int max_prime, int max_num, int min_num, int c, int ku, int div)
{
	int i;
	
	if (div) {
	  // are all parts the same?
	  if (npart != 1)
	    return 0;
	}

	if (ku)
	{
		for ( i = 0; i < npart; i++ )
		{
			if (mult[i] > 1)
				return 0;
		}
		
	}
	
	
	if (max_num)
	{
		for ( i = 0; i < npart; i++ )
		{
			if (a[i] > max_num)
				return 0;
		}
	}
	
	if (min_num)
	{
		for ( i = 0; i < npart; i++ )
		{
			if (a[i] < min_num)
				return 0;
		}
	}
	
	if (must_be_prime)
	{
		for ( i = 0; i < npart; i++ )
		{
			if (!is_prime(a[i]))
				return 0;
		}
	}
	if (max_prime)
	{
		//      cout << max_prime << endl;
		for ( i = 0; i < npart; i++ )
		{
			if (is_prime(a[i]))
			{
				//      cout << a[i] << endl;
				if (a[i] > max_prime)
					return 0;
			}
		}
	}
	if (no_ones)
	{
		for ( i = 0; i < npart; i++ )
		{
			if (a[i] == 1)
				return 0;
		}
	}
	
	cout << "  " << n << " = ";
	
	int partcount = 0;
	for ( i = 0; i < npart; i++ )
	{
		int k = 0;
		for (; k < mult[i]; k++) {
			cout << (a[i] + c) << ", ";
			++partcount;
		}
		
		//    cout << mult[i] << " * " << a[i];
	}
	float mean = n / float(partcount);
	float sum = 0.f;
	for ( i = 0; i < npart; i++ )
	{
		int k = 0;
		for (; k < mult[i]; k++) {
			float s = a[i]  - mean;
			s *= s;
			sum += s;
		}
		
		//    cout << mult[i] << " * " << a[i];
	}
    
    
    int maxpart = npart - 1;
    int not_coprime_flag = 0;
    for ( i = 0; i < maxpart; i++ )
    {
        if ( GGT(a[i], a[i+1]) > 1 )
            not_coprime_flag = 1;
            
    }
    
    int none_coprime_flag = 0;
    for ( i = 0; i < maxpart; i++ )
    {
        int test = a[i];
        int m = i+1;
        for ( ; m < npart; m++ )
        {
            if ( GGT(test, a[m]) > 1 )
                none_coprime_flag = 1;
            
        }
    }
    
	string noprime = "";
	
	if (is_prime (n))
			noprime = "prime.";
    cout << "mean: " << mean << " sigma: " << std::setprecision(6) << (sqrt(sum/double(partcount))) << " " << noprime;
    if (!not_coprime_flag)
        cout << " Coprime pairs.";
    if (!none_coprime_flag)
        cout << " Coprime sequence!";
    cout << "\n";
	
	return (!none_coprime_flag);
}

void partition (int n, int must_be_primes, int no_ones, int max_prime, int max_num, int min_num, int c, int k, int div)
{
	// n, part has to be prime only, no part to be 1, max prime to be allowed as part, max int to be allowed as part, min int allowed as part
	// c is an integer added to all parts, k is the number of parts allowed only
	int N = n;
	int a[N];
	bool more;
	int mult[N];
	int npart;
	
	more = false;
	
	int countpartition = 0;
	//int filtered_partition_count = 0;
    //int coprime_list_count = 0;
	
	for ( ; ; )
	{
		i4_partition_next2 (N, a, mult, &npart, &more);
		++countpartition;
		if (npart == k) {
		  partition_rhythm_print (N, npart, a, mult, must_be_primes, no_ones, max_prime, max_num, min_num, c, k, div);
			//++filtered_partition_count;
		}
		else {
			if (k) {
				;//cout << "there are partions of " << N << " with " << npart << " parts." << endl;
			}
			else {
			  partition_rhythm_print (N, npart, a, mult, must_be_primes, no_ones, max_prime, max_num, min_num, c, k, div);
				//++filtered_partition_count;
			}

			
		}

			
		if (!more)
		{
		  //            float coprime_percentage = (float(coprime_list_count) / float(filtered_partition_count)) * 100.f;
			cout << "p(" << N << ") = " << countpartition << "." << endl;
			break;
		}
		
	}
	return;
}

void random_rhythm (int n, double min, double max)
{
    Alea a;
    int i = 0;
    for (; i < n; i++)
    {
	cout << (a.Uniform (min, max)) << endl;
    }

}

void GetRanksFromList (DList<float>* in, DList<int>* out)
{
    //cout << "...................................." << endl;
    out->destroy ();
    DList<float>* maxs = new DList<float>;
    int in_size = in->GetSize ();
    int counter = in_size;
    float max = 0.f;
    DLink<float>* in_link = in->first ();
    for (;  in_link != NULL; in_link = in_link->next)
    {
	out->append (new int (-1));
    }

    while (counter-- > 0)
    {
	//cout << "in_size: " << in_size << endl;
	max = 0.f;
	for (in_link = in->first (); in_link != NULL; in_link = in_link->next)
	{
	    float data = *in_link->data;
	    //cout << "data : " << data << endl;
	    if (data > max && (maxs->has (in_link->data) < 0))
	    {
		max = data;
		//cout << "cur max : " << max << endl;
	    }
	}
	if (max > 0.f)
	{
//	    cout << "new max : " << max << "pos in: " << (in->has(&max))  << "rank: " << in_size << endl; 
	    maxs->append (new float (max));
	    out->replaceAt ((in->has(&max)), new int(in_size));
	    --in_size;
	}
    }
    maxs->destroy ();
    delete maxs;
    maxs = NULL;
}

bool AreListsEqual (DList<int>* l1, DList<int>* l2)
{
    if (l1->GetSize () != l2->GetSize ())
	return false;

    DLink<int>* l1link = l1->first ();
    DLink<int>* l2link = l2->first ();
    for (; l1link != NULL; l1link = l1link->next, l2link = l2link->next)
    {
	if (*l1link->data != *l2link->data)
	    return false;
    }
    return true;
}

float round_to_nearest_point_five (float x)
{
    int num = int(x * 100.f);
    if (num < 19)
	return 0.125;
    if (num <= 37)
	return 0.25;
    int mod = num % 50;
    if (num == 0)
	mod = 1;
    int mult = mod / 25;
    num = num - mod + mult * 50;
    return float (num / 100.f);
}

void temporal_density_f (DList<float>* in, DList<int>* out, float range)
{
// function for the measurment of temporal density
// <in> is a normalised list of IOIs.
// <range> is given in normalised duration.
// from each ioi_n in <in> it is measured how many onsets fall in the range:
// onset_n + range, where onset_n is equal to the sum_0^n-1 ioi_n
    float onset = 0;
    DLink<float>* inl = in->first ();
    for (; inl != NULL; inl = inl->next)
    {
	float oplusr = onset + range;
	DLink<float>* inner = inl;
	int count = 0;
	float test = onset;
	for (; inner != NULL; inner = inner->next)
	{
	    test += (*inner->data);
	    if (test <= oplusr)
		count++;
	    else
		break;
	}
	onset += (*inl->data);
	out->append (new int(count));
    }
}


float nPVI (DList<float>* in)
{
    // function to calculate the nPVI of a sequence of IOIs
    // after Patel, Music, Language and the Brain, 2008, p.131 and 177

    int m = in->GetSize () - 1;
    DLink<float>* inl = in->first ();
    float sum = 0.f;
    for (; inl->next != NULL; inl = inl->next)
    {
	float d0 = *inl->data;
	float d1 = *inl->next->data;
	sum += fabs ((d0 - d1) / ((d0 + d1) / 2.f));
    }
    return (100.f / m * sum);
}

void temporal_density (DList<int>* in, DList<int>* out, int range)
{
// function for the measurment of temporal density
// <in> is a list of IOIs in ms.
// <range> is given in ms.
// from each ioi_n in <in> it is measured how many onsets fall in the range:
// onset_n + range, where onset_n is equal to the sum_0^n-1 ioi_n
    int onset = 0;
    DLink<int>* inl = in->first ();
    for (; inl != NULL; inl = inl->next)
    {
	int oplusr = onset + range;
	DLink<int>* inner = inl;
	int count = 0;
	int test = onset;
	for (; inner != NULL; inner = inner->next)
	{
	    test += (*inner->data);
	    if (test <= oplusr)
		count++;
	    else
		break;
	}
	onset += (*inl->data);
	out->append (new int(count));
    }
}



#if 0
float round_to_nearest_point_twentyfive (float x)
{
    int num = int(x * 1000.f);
    int mod = num % 250;
    if (num == 0)
	mod = 1;
    int mult = mod / 125;
    num = num - mod + mult * 500;
    return float (num / 1000.f);
}
#endif



void GetAnglesFromSides (DList<float>* sides, DList<float>* angles)
{
    if (sides->GetSize () < 3)
	return;
    DLink<float>* sl = sides->first ();
    float a = *sl->data; sl = sl->next;
    float b = *sl->data; sl = sl->next; 
    float c = *sl->data; 
    float a2 = a*a;
    float b2 = b*b;
    float c2 = c*c;
    angles->destroy ();
    float alpha = 2*atan(sqrt((a2-(b-c)*(b-c))/((b+c)*(b+c)-a2)));
    float gamma = 2*atan(sqrt((c2-(a-b)*(a-b))/((a+b)*(a+b)-c2)));
    float beta  = 2*atan(sqrt((b2-(c-a)*(c-a))/((a+c)*(a+c)-b2)));
    angles->append (new float(alpha));
    angles->append (new float(gamma));
    angles->append (new float(beta));
}

void FilterListRange (DList<Ratio>* in, float min, float max)
{
    DLink<Ratio>* inlink = in->first ();
    for (; inlink != NULL; inlink = inlink->next)
    {
	if (inlink->data->GetFloat () < min || inlink->data->GetFloat () > max)
	{
	    in->removeElement (inlink->data);

	}
    }


}

void float2frac (float in, Ratio* out)
{
    const int N = 10; 
    int a[N+1]; 
    int p[N+2]; 
    int q[N+2]; 
    int P = 0; int Q = 0; 
    float_to_cfrac (double(in), N, a, p, q);

    for ( int i = 0; i <= N; i++ ) 
    { 
	if (!q[i+1]) 
	    continue; 
	double temp = double(p[i+1]) / double(q[i+1]); 
	float error = in - temp;
	if ((fabs(error)) < 0.00001) 
	{ 
	    P = p[i+1]; 
	    Q = q[i+1]; 
	    break; 
	} 
    }
    out->SetP (P);
    out->SetQ (Q);
}

void double2frac (double in, Ratio* out)
{
    const int N = 10; 
    int a[N+1]; 
    int p[N+2]; 
    int q[N+2]; 
    int P = 0; int Q = 0; 
    float_to_cfrac (in, N, a, p, q);
	
    for ( int i = 0; i <= N; i++ ) 
    { 
		if (!q[i+1]) 
			continue; 
		double temp = double(p[i+1]) / double(q[i+1]); 
		float error = in - temp;
		if ((fabs(error)) < 0.00001) 
		{ 
			P = p[i+1]; 
			Q = q[i+1]; 
			break; 
		} 
    }
    out->SetP (P);
    out->SetQ (Q);
}

void RemoveDuplicates (DList<Ratio>* list)
{
    DLink<Ratio>* rl = list->first ();
   
    for (; rl->next != NULL; rl = rl->next)
    {
//	cout << "compare: " << (rl->data->GetFloat ()) << endl;
	DLink<Ratio>* cur = NULL;
	if (rl->next)
	    cur = rl->next;
	else
	    break;
	
	for (; cur != NULL; cur = cur->next)
	{
	    // cout << "with: " << (cur->data->GetFloat ()) << endl;
	    if (*(rl->data) == (*cur->data))
	    {
		//cout << "remove: " << (cur->data->GetFloat ()) << endl;
		list->removeElement(cur->data);
		if (!rl->next)
		  goto bail;
	    }
	}
    }
bail:
    ;
}

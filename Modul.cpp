#define DEBUG_STR(var)
#ifndef	__Modul_h__ 
#include "Modul.h" 
#endif 

//#include "smf.h"
#include "Alea.h"
//#include "Llist1.h" 
#include "DList.h" 
#include "Farey.h" 
#include "FareyVisitor.h" 
#include "FareyFilter.h"
#include "fareytab.h" 
#include "smoothtab.h" 
#include "SmoothFilter.h"
#include "ReciprocalFilter.h"
#include "SubdivisionFilter.h"
#include "Christoffel.h"
#include <iostream>


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

#define END(array) (array + (sizeof (array) / sizeof (int)))

TextIO t("run..."); 

const int a_triangle3[3] = {2,0,1};
const int b_triangle3[3] = {1,0,2};
const int a_triangle4[4] = {3,1,0,2};           
const int b_triangle4[4] = {3,0,1,2};
const int c_triangle4[4] = {2,1,0,3};
const int d_triangle4[4] = {2,0,1,3};
const int a_triangle5[5] = {4,2,0,1,3};        
const int b_triangle5[5] = {4,1,0,2,3};
const int c_triangle5[5] = {3,2,0,1,4};        
const int d_triangle5[5] = {3,1,0,2,4};
const int a_triangle6[6] = {5,3,2,0,1,4};     
const int b_triangle6[6] = {4,3,2,0,1,5};
const int a_triangle7[7] = {6,2,1,0,3,4,5};
const int b_triangle7[7] = {5,2,1,0,3,4,6};

/*
const int group_4_1[2] = {2,2};
const int group_5_1[2] = {3,2};
const int group_5_2[2] = {2,3};
const int group_6_1[2] = {3,3};
const int group_6_2[3] = {2,2,2};
const int group_7_1[3] = {3,2,2};
const int group_7_2[3] = {2,3,2};
const int group_7_3[3] = {2,2,3};
const int group_8_1[3] = {3,3,2};
const int group_8_2[3] = {3,2,3};
const int group_8_3[3] = {2,3,3};
const int group_8_4[4] = {2,2,2,2};
const int group_9_1[3] = {3,3,3};
const int group_9_2[4] = {3,2,2,2};
const int group_9_3[4] = {2,3,2,2};
const int group_9_4[4] = {2,2,3,2};
const int group_9_5[4] = {2,2,2,3};
*/

enum {RESISTOR, RELEASE, ARCH, CATENARY, ALTERNATING, GROWTH, DECREASE, NUMFORMS};
//vector<string> g_forms
//enum {ALTERNATING, GROWTH, DECREASE, RESISTOR, RELEASE, ARCH, CATENARY, NUMFORMS };

Modul::Modul( string filtyp, unsigned long chan, unsigned long samframs, 
			unsigned long samsiz, unsigned long samrat) { 
    //prg = NULL;
	file_type = filtyp; 
	channels = chan; 
	sample_frames = samframs; 
	sample_size = samsiz; 
	sample_rate = samrat; 
	digest_list = new DList<float_digest>; 
	QGI = new quant_global_info;
	qsi = new DList<quant_solution_info>;
	result_weights = new DList<final_weights_info>;
	result_weights2 = new DList<final_weights_info>;
	df = new DList<difference_function>;
	lastrat = 0.f;
	qdurcount = 0;
	lastinteg = 0.f;
	quli = new DList<finali>;
	rhythm_database = new DList<DList<float> >;
	analysis_database = new DList<analysisentry >;
	pulse_seq = new DList<int>; 
	real_pulseq = new DList<float>;

	pack_count = 0;
	
    //vectors of partitions
	matrix = new vector <vector <float> >;
    // all_COPRIME_partitions_until_120_with_2_distinct_parts.txt:
	matrix2 = new vector <vector <float> >;
    // all_COPRIME_partitions_until_120_with_3_distinct_parts.txt:
	matrix3 = new vector <vector <float> >;
    // all_COPRIME_partitions_until_120_with_4_distinct_parts.txt:
	matrix4 = new vector <vector <float> >;
    // all_COPRIME_partitions_until_120_with_5_distinct_parts.txt:
	matrix5 = new vector <vector <float> >;
    // all_partitions_until_41_parts_only_2s_and_3s.txt:
	matrix_2s3s = new vector <vector <float> >;
    // from bracelets.txt:
	bracelets = new vector <vector <float> >;

    // for all 2-3 musical patterns
	resistor = new vector <vector <float> >;
	release = new vector <vector <float> >;
	arch = new vector <vector <float> >;
	catenary = new vector <vector <float> >;
	alternating = new vector <vector <float> >;
	growth = new vector <vector <float> >;
	decrease = new vector <vector <float> >;

    // vectors of musical triangles
	m_triangles = new vector<vector <int> >;
	vector<int> v (a_triangle3, END(a_triangle3));
	m_triangles->push_back (v);	       
        vector<int> v2 (b_triangle3, END(b_triangle3));
        m_triangles->push_back (v2);
	vector<int> v3 (a_triangle4, END(a_triangle4));
        m_triangles->push_back (v3);
	vector<int> v4 (b_triangle4, END(b_triangle4));
        m_triangles->push_back (v4);
	vector<int> v5 (c_triangle4, END(c_triangle4));
        m_triangles->push_back (v5);
	vector<int> v6 (d_triangle4, END(d_triangle4));
        m_triangles->push_back (v6);
	vector<int> v7 (a_triangle5, END(a_triangle5));
        m_triangles->push_back (v7);
	vector<int> v8 (b_triangle5, END(b_triangle5));
        m_triangles->push_back (v8);
	vector<int> v9 (c_triangle5, END(c_triangle5));
        m_triangles->push_back (v9);
        vector<int> v10 (d_triangle5, END(d_triangle5));
        m_triangles->push_back (v10);
	vector<int> v11 (a_triangle6, END(a_triangle6));
        m_triangles->push_back (v11);
        vector<int> v12 (b_triangle6, END(b_triangle6));
        m_triangles->push_back (v12);
	vector<int> v13 (a_triangle7, END(a_triangle7));
	m_triangles->push_back (v13);
	vector<int> v14 (b_triangle7, END(b_triangle7));
        m_triangles->push_back (v14);

    // the metric groupings for cycles 2-9
    // this is for testing to which of the groupings
    // rhythmic patterns belong to. See LookupGrouping ()
	m_group2 = "ab";
	m_group3 = "abb";
	m_group4 = "abab";
	m_group5.push_back("abbab");
	m_group5.push_back("ababb");
	m_group6.push_back("abbabb");
	m_group6.push_back("ababab");
	m_group7.push_back("abbabab");
	m_group7.push_back("ababbab");
	m_group7.push_back("abababb");
	m_group8.push_back("abababab");
	m_group8.push_back("abbabbab");
	m_group8.push_back("abbababb");
	m_group8.push_back("ababbabb");
	
	m_group9.push_back("abbabbabb");
	m_group9.push_back("abbababab");
	m_group9.push_back("ababbabab");
	m_group9.push_back("abababbab");
	m_group9.push_back("ababababb");

    meter_store = 0;
    vector<string> default_pitch;
    default_pitch.push_back ("69");
    mel_matrix.push_back (default_pitch);
    
	LoadForms();
} 
 
Modul::~Modul() { 
  if (matrix)
    delete matrix;
  if (matrix2)
    delete matrix2;
  if (matrix3)
    delete matrix3;
  if (matrix4)
    delete matrix4;
  if (matrix5)
    delete matrix5;
  if (matrix_2s3s)
    delete matrix_2s3s;
  if (bracelets)
    delete bracelets;
  if (resistor)
    delete resistor;
  if (release)
    delete release;
  if (arch)
    delete arch;
  if (catenary)
    delete catenary;
  if (alternating)
    delete alternating;
  if (growth)
    delete growth;
  if (decrease)
    delete decrease;
  if (m_triangles)
    delete m_triangles;
} 

void Modul::CircleMap () {
  
  // theta_n+1 = theta_n + Omega - K / TWOPI x sin (TWOPI theta_n)
  // where theta is computed mod 1 and K is a constant. 
  // Note that the circle map has two parameters: Omega and K.  
  // Omega can be interpreted as an externally applied frequency, 
  // and K as a strength of nonlinearity. 
  // The circle map exhibits very unexpected behavior as a function of parameters.

  int i = 0;
  float theta = 0.f;
  float Omega = 0.196078f;
  float K = 1.f;

  TextIO text ("cm.txt");
  ofstream out;
  text.TextWrite (out, "cm.txt");

  for (; i < 50; i++) {
    theta = fmod((theta + Omega - (K/TWOPI) * sin (TWOPI*theta)), 1);
    cout << theta << endl;
    out << theta << endl;
  }
}


	
void Modul::FareyToBinaryRhythm (int farey_index, int dig, int flag) {
		
	Farey* afar; 
	afar = new Farey (); 
	afar->CreateFareySeq (farey_index); 
	
	if (flag) {
		//s2,
		//s2_3,
		//s2_3_5,
		//s2_3_5_7,
		SmoothFilter* sf = new SmoothFilter; 
		sf->SetFilterVal (s2_3);
		Visitor* v = sf;
		afar->Accept (*v); 
		afar->SetFareySeq (sf->GetRatioList ()); // override Ratio list in Farey object
	
		cout << "Filtered Farey Sequence " << farey_index <<  " according to smooth number filtering :" << endl;
		DLink<Ratio>* r; 
		for (r = afar->GetFirst (); r != NULL; r = r->next) 
			cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
		cout << endl;
		
//		afar->CreateDiffList (); 
//		afar->CreateCommonDenomList (); 
		afar->CreateCommonDenomList2 (); 
		cout << endl << "Filtered Farey Sequence with common denominator:" << endl;
		
		for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
			cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
		cout << endl;
		
		cout << endl << "in integer distance notation:" << endl;
		for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
			cout << (r->data->GetP ()) << " " ; 
		cout << endl;
		
#if 0
		cout << endl << "and translated into binary rhythm: " << endl;
		for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) {
			cout << 1;
			int zeros = r->data->GetP ();
			while (--zeros > 0) {
				cout << " " << 0;
			} 
			cout << " ";
		}
#endif	
		cout << endl << endl;		
		
		return;	
	}

	
	Visitor* v = new FareyVisitor (dig); 
	afar->Accept (*v, 1); 
	FareyVisitor* fv = static_cast<FareyVisitor*>(v); 
	afar->SetFareySeq (fv->GetRatioList ());
	
	cout << "Filtered Farey Sequence " << farey_index <<  " according to max. Digestibility value " << dig << " :" << endl;
	DLink<Ratio>* r; 
	for (r = afar->GetFirst (); r != NULL; r = r->next) 
		cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
	cout << endl;
	
//	afar->CreateDiffList (); 
//	afar->CreateCommonDenomList (); 
	afar->CreateCommonDenomList2 (); 
	cout << endl << "Filtered Farey Sequence with common denominator:" << endl;
	
	for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
		cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
	cout << endl;
	
	cout << endl << "in integer distance notation:" << endl;
	for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
		cout << (r->data->GetP ()) << " " ; 
	cout << endl;

#if 0	
	cout << endl << "and translated into binary rhythm: " << endl;
	for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) {
		cout << 1;
		int zeros = r->data->GetP ();
		while (--zeros > 0) {
			cout << " " << 0;
		} 
		cout << " ";
	}
#endif	
	cout << endl << endl;
			
}
	
void Modul::Divisors () {
#if 0
	
	int i = 0;
	for (; i < 87; i++)
	{
		int b = smooth2_3_5[i];
		cout << "Divisors of " << b << ": ";
		int max = b / 2 + 1;
		while (max-- > 2) {
			if (!(b % max)) 
				cout << max << " ";
		}
		cout << endl;
	}
#endif
	
	int i = 0;
	for (; i < 500; i++)
	{
		int b = i;//smooth2_3_5[i];
		cout << "Divisors of " << b << ": ";
		int max = b / 2 + 1;
		while (max-- > 2) {
			if (!(b % max)) 
				cout << max << " ";
		}
		cout << endl;
	}
}
	
void Modul::Permutations () {
	int i = 1;
	for (; i < 21; i++)
	{
		int b = smooth2_3_5_7[i];
		int count = 0;
        cout << "ratios with " << b << ": " << endl;
		int k = 21;
		while (k-- > 1) {
			int q = smooth2_3_5_7[k];
			Ratio* r = new Ratio (b,q);
			r->AutoReduce ();
			if (b == r->GetP () && q == r->GetQ ()) {
				if (b < 20 && q < 20) {
                    cout << "---------------" << endl;
					cout << b << ":" << q << endl;
                    string s = r->Christoffel (true);
                    Christoffel c;
                    c.SetWord (s);
                    c.display_all ();
                    //c.print_words ();
                    //cout << c << " | ";
					++count;
				}
			}
		}
		cout << count << " coprime ratios" << endl;	
	}
    
}
	
void Modul::Permutations2 () {
		int i = 1;
		Ratio* r = new Ratio (1,1);
		for (; i < 143; i++)
		{
			int b = smooth2_3_5_7[i];

			cout << "ratios with " << b << ": ";
			int k = 143;
			while (k-- > 1) {
				int q = smooth2_3_5_7[k];
				r->SetP(b);
				r->SetQ(q);
				r->AutoReduce ();
				if (b == r->GetP () && q == r->GetQ ()) {
					if (b < 17 && q < 17) {
						FareyPolyrhythm ((b*q), b, q);
#if 0
						cout << b << ":" << q << ", ";
						++count;
#endif
					}
				}
			}
#if 0
			cout << count << " coprime ratios" << endl;	
#endif
		}
	}
	
void Modul::FareyPolyrhythm (int f, int p, int q) {  

	Farey* afar3; 
	afar3 = new Farey (); 
	afar3->CreateFareySeq (f);
	SubdivisionFilter* sdf = new SubdivisionFilter; 
	DList<int>* subdivs = new DList<int>;
	subdivs->append (new int(f/p));
	subdivs->append (new int(f/q));
	
	cout << "F_" << f << " filtered by subdivisions:" << endl;
	DLink<int>* si = subdivs->first ();
	for (; si != NULL; si = si->next) {
		cout << (f / *si->data) << " ";
	}
	cout << endl;
	
	sdf->SetFilterVal (subdivs);
	Visitor* v = sdf;
	afar3->Accept (*v); 
	sdf->GetRatioList ()->prepend (new Ratio(0,1));
	sdf->GetRatioList ()->append (new Ratio(1,1));
	afar3->SetFareySeq (sdf->GetRatioList ()); // override Ratio list in Farey object
	//afar3->PrintFareyTree ();
	
	afar3->CreateCommonDenomList2 (); 
	DLink<Ratio>* r;	
	cout << endl << "Filtered F_" << f << " in integer distance notation:" << endl;
	for (r = afar3->GetFirstCommonDenom (); r != NULL; r = r->next) 
		cout << (r->data->GetP ()) << " " ; 
	cout << endl;
	
	cout << endl << "and translated into binary rhythm: " << endl;
	for (r = afar3->GetFirstCommonDenom (); r != NULL; r = r->next) {
		cout << 1;
		int zeros = r->data->GetP ();
		while (--zeros > 0) {
			cout << " " << 0;
		} 
		cout << " ";
	}
	cout << endl;
	DLink<Ratio>* z = afar3->GetFirstCommonDenom ();
	for (r = afar3->GetFirst (); r->next != NULL ; r = r->next, z = z->next) {
		cout << r->data->GetQ ();
#if 1
		int zeros = z->data->GetP ();
		while (--zeros > 0) {
			cout << " " << 0;
		} 
#endif	
		cout << " ";
	}
	cout << endl;
	delete sdf;
	delete afar3;
	
} 

void Modul::DatabaseCompare (DLink<DList<float> >* entry, DList<DList<float> >* input, int input_index, int length) {
		// loop through first cells of input starting at input_index for length (entry_length_of_list / 3) number of cells 
		// find out absolute timespan of input section and scale db entry accordingly
		// then perform disctance measures
		// best to create two local DList<float>
		// write results to an internal Modul:: database
	
	int index = input_index;
	DLink<float>* rowlink = entry->data->first ();
	DLink<float>* inlink = input->getAt (index++)->data->first ();
	float dbentrylength = 0.f;
	float musiclength = 0.f;
	float musicoverdb = 0.;
	
	int count = 0;
	cout << endl << "pat/in: ";
	for (rowlink = entry->data->first (); rowlink != NULL && inlink != NULL; rowlink = rowlink->next, count++) {
		if (!(count%3)) {
			float db = (*rowlink->data);
			float mu = (*inlink->data);
			cout << db << " " << mu << " ";	
			inlink = input->getAt (index++)->data->first ();
			dbentrylength += db;
			musiclength += mu;
		}
	}
	musicoverdb = musiclength / dbentrylength;
	//cout << dbentrylength << " " << musiclength << " " << (musiclength / dbentrylength) << endl;
	
	index = input_index;
	rowlink = entry->data->first ();
	inlink = input->getAt (index++)->data->first ();
	count = 0;
	cout << endl << "norm pat/in: ";
	double dE = 0;
	double dE2 = 0;
	for (rowlink = entry->data->first (); rowlink != NULL && inlink != NULL; rowlink = rowlink->next, count++) {
		if (!(count%3)) {
			float db = (*rowlink->data);
			float mu = (*inlink->data);
			float dbscaled = musicoverdb * db;
			cout << (dbscaled) << " " << mu << " ";	
			inlink = input->getAt (index++)->data->first ();
			dE += (dbscaled * log(dbscaled/mu));
			dE2 += ((dbscaled - mu) * (dbscaled - mu));
		}
	}
	cout << " KL dist.: " << dE << " Eucl. dist.: " << dE2 << endl; 
	if (dE < 0.001) {
		analysisentry* ae = new analysisentry;
		ae->musicindex = input_index;
		ae->kldist = dE;
		ae->ecldist = dE2;
		DList<int>* dbe = new DList<int>;
		DList<float>* muse = new DList<float>;
		index = input_index;
		rowlink = entry->data->first ();
		inlink = input->getAt (index++)->data->first ();
		count = 0;

		for (rowlink = entry->data->first (); rowlink != NULL && inlink != NULL; rowlink = rowlink->next, count++) {
			if (!(count%3)) {
				float db = (*rowlink->data);
				float mu = (*inlink->data);
				inlink = input->getAt (index++)->data->first ();
				dbe->append (new int(db));
				muse->append (new float(mu));
			}
		}
		ae->dbentry = dbe;
		ae->musicentry = muse;
		analysis_database->append (ae);
	}
		
}
	
void Modul::DisplayDatabase () {
		
	cout << "Analysis Results........." << endl;
	DLink<analysisentry>* ael = analysis_database->first ();
	for (; ael != NULL; ael = ael->next) {
		cout << "------------------" << endl;
		cout << ael->data->musicindex << " " << ael->data->kldist << " " << ael->data->ecldist << endl;
		DLink<int>* dbl = ael->data->dbentry->first ();
		for (; dbl != NULL; dbl = dbl->next) {
			cout << (*dbl->data) << " ";
		}
		cout << endl;
		DLink<float>* ml = ael->data->musicentry->first ();
		for (; ml != NULL; ml = ml->next) {
			cout << (*ml->data) << " ";
		}
		cout << endl;
	}
}

void Modul::LoadRhythmDatabase (string filename) {
		ifstream       file( filename.c_str() );
		string                line;
		string                cell;
		DList<DList<float> >* matrix;
		DList<float>* row;	
		matrix = new DList<DList<float> >;
		
		int linecount = 0;
		int cellcount = 0;
		int singlecolumnflag = 0;
		//rhythm_database->destroy ();
		// you can append to the database
		
		while( file )
		{
			getline (file,line);
			linecount++;
			stringstream lineStream (line);
			row = new DList<float>;
			while (getline( lineStream, cell, ',')) {
				row->append(new float(atof(cell.c_str())));
				cellcount++;
			}
			if( row->GetSize() ) {
				matrix->append (row);
			} else {
				row->destroy ();
				delete row;
			}
			
		}
		
#if 0
			// the csv file...
		1,,,,,,
		1,2,,,,,
		1,1,2,,,,
		1,1,1,2,,,
		1,1,1,1,2,,
		2,2,1,2,2,2,1
#endif
		cout << linecount << " " << cellcount << endl;
		if (cellcount <= linecount)
			singlecolumnflag = 1;
		
		DLink<DList<float> >* link = matrix->first ();
		float lastf = 0.;
		for (; link!= NULL; link = link->next) {
			
			int fn = link->data->GetSize ();
			if (fn > 0) {
				DLink<float>* rowlink = link->data->first ();
				//int length = 0;
				if (!singlecolumnflag) {
					//cout << "-------" << endl;
					lastf = 0;
				}
				
				row = new DList<float>;
				for (; rowlink != NULL; rowlink	= rowlink->next) {
					
					float cur = *rowlink->data;
					if (cur) {
						//cout << (cur) << "\t" << ((cur > lastf) ? ">" : "<") << "\t" << ((cur == lastf) ? "=" : "!") << endl;
						// every row is an analysed entry into the rhythm database
						
						row->append(new float(cur));
						((cur > lastf) ? row->append(new float(1)) : row->append(new float(0)));
						((cur == lastf) ? row->append(new float(1)) : row->append(new float(0)));
						
						
						
						lastf = cur;
					}
				}		
				rhythm_database->append (row);

			}
		}
		
		//also include the reverse patterns from database:
		
		link = matrix->first ();
		lastf = 0.;
		for (; link!= NULL; link = link->next) {
			
			int fn = link->data->GetSize ();
			if (fn > 0) {
				DLink<float>* rowlink = link->data->last ();
				//int length = 0;
				if (!singlecolumnflag) {
					//cout << "-------" << endl;
					lastf = 0;
				}
				
				row = new DList<float>;
				for (; rowlink != NULL; rowlink	= rowlink->previous) {
					
					float cur = *rowlink->data;
					if (cur) {
						//cout << (cur) << "\t" << ((cur > lastf) ? ">" : "<") << "\t" << ((cur == lastf) ? "=" : "!") << endl;
								
						row->append(new float(cur));
						((cur > lastf) ? row->append(new float(1)) : row->append(new float(0)));
						((cur == lastf) ? row->append(new float(1)) : row->append(new float(0)));
						
						lastf = cur;
					}
				}
				rhythm_database->append (row);
				
			}
		}
		
		matrix->destroy ();
		delete matrix;
	}
	
void Modul::AnalyseIntegerRhythmStrings (string filename, string filename2) {
		ifstream       file (filename.c_str());
		ifstream       file2 (filename2.c_str());
		string                line;
		string                cell;
		DList<DList<int> >* matrix;
		DList<DList<int> >* matrix2;	
		DList<int>* row;
		
		DList<DList<Ratio> >* rmatrix;
		DList<DList<Ratio> >* rmatrix2;
		DList<Ratio>* fsq;
		
		DList<Farey>* fareylist;
		DList<Farey>* fareylist2;
	
		fareylist = new DList<Farey>;
		matrix = new DList<DList<int> >;
		rmatrix = new DList<DList<Ratio> >;
		fareylist2 = new DList<Farey>;
		matrix2 = new DList<DList<int> >;
		rmatrix2 = new DList<DList<Ratio> >;
		
		while (file) {
			getline (file,line);
			stringstream lineStream (line);
			row = new DList<int>;
			while (getline(lineStream, cell, ','))
				row->append (new int(atoi(cell.c_str())));
			
			if (row->GetSize()) {
				matrix->append (row);
			} else {
				row->destroy ();
				delete row;
			}
		}
	
		while (file2) {
			getline (file2,line);
			stringstream lineStream (line);
			row = new DList<int>;
			while (getline(lineStream, cell, ','))
				row->append (new int(atoi(cell.c_str())));
		
			if (row->GetSize()) {
				matrix2->append (row);
			} else {
				row->destroy ();
				delete row;
			}
		}
		
		DLink<DList<int> >* link = matrix->first ();
		
		for (; link!= NULL; link = link->next) {
			int fn = link->data->GetSize ();
			//cout << "size: " << fn << endl;
			if (fn > 0) {
				fsq = new DList<Ratio>;
				fsq->append (new Ratio(0, 1));
				//int count = 0;
				DLink<int>* rowlink = link->data->first ();
				int length = 0;
				for (; rowlink != NULL; rowlink	= rowlink->next) {
					int cur = *rowlink->data;
					cout << (cur) << " ";
					length += cur;
				}	
				cout << endl;
				rowlink = link->data->first ();
				int last = 0;
				if (length == 1) {
					fsq->append (new Ratio(1, 1));
					rmatrix->append (fsq);
					continue;
				} else {
					rowlink = link->data->first ();
					for (; rowlink != NULL; rowlink = rowlink->next) {
						int cur = *rowlink->data;
						if (cur) {
							fsq->append (new Ratio((cur+last), length));
							last += cur;
						}
					}
				}
				//fsq->append (new Ratio(1, 1));
				rmatrix->append (fsq);
			}
		}
		
		cout << endl;
	
		for (link = matrix2->first (); link!= NULL; link = link->next) {
			int fn = link->data->GetSize ();
			//cout << "size: " << fn << endl;
			if (fn > 0) {
				fsq = new DList<Ratio>;
				fsq->append (new Ratio(0, 1));
				//int count = 0;
				DLink<int>* rowlink = link->data->first ();
				int length = 0;
				for (; rowlink != NULL; rowlink	= rowlink->next) {
					int cur = *rowlink->data;
					cout << (cur) << " ";
					length += cur;
			}	
			cout << endl;
			rowlink = link->data->first ();
			int last = 0;
			if (length == 1) {
				fsq->append (new Ratio(1, 1));
				rmatrix2->append (fsq);
				continue;
			} else {
				rowlink = link->data->first ();
				for (; rowlink != NULL; rowlink = rowlink->next) {
					int cur = *rowlink->data;
					if (cur) {
						fsq->append (new Ratio((cur+last), length));
						last += cur;
					}
				}
			}
			//fsq->append (new Ratio(1, 1));
			rmatrix2->append (fsq);
			}
		}
	
		cout << endl;
		
		Farey* afar;
		//	afar = new Farey ();
		//	afar->CreateFareySeq (3);
		
		DLink<DList<Ratio> >* flink = rmatrix->first ();
		for (; flink != NULL; flink = flink->next) {
			DLink<Ratio>* rlink = flink->data->first ();
			int maxden = 1;
			for (; rlink != NULL; rlink = rlink->next) {
				rlink->data->AutoReduce ();
				int cden = rlink->data->GetQ ();
				cout << (rlink->data->GetP ()) << "/" << (cden) << " ";
				if (cden > maxden)
					maxden = cden;
			}
			cout << "(F_" << maxden << ")";
			cout << endl;
			
			afar = new Farey ();
			afar->CreateFareySeq (3);
			afar->SetFareySeq(flink->data);	
			//afar->GetRatioList ()->append (new Ratio(1,1));
			afar->CreateCommonDenomList2 (); 
			fareylist->append (afar);
			
			DLink<Ratio>* r; 
			
			cout << endl << "Filtered Farey Sequence orig.:" << endl;
			for (r = afar->GetFirst (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
			cout << endl;
			
			cout << endl << "Filtered Farey Sequence Diff. orig.:" << endl;
			for (r = afar->GetFirstDiff (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
			cout << endl;
			
			cout << endl << "Common Denominator: ";
			cout << afar->GetCommonDenominator () << endl;
			
			cout << endl << "Filtered Farey Sequence with common denominator:" << endl;
			for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
			cout << endl;
			
			cout << endl << "in integer distance notation:" << endl;
			for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << " " ; 
			
			cout << endl << "and translated into tik rhythm: " << endl;
			for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) {
				cout << 1;
				int zeros = r->data->GetP ();
				while (--zeros > 0) {
					cout << " " << 0;
				} 
				cout << " ";
			}
			
			cout << endl << endl;
			cout << "---------------------------------------------------" << endl;
		}
	
	
		flink = rmatrix2->first ();
		for (; flink != NULL; flink = flink->next) {
			DLink<Ratio>* rlink = flink->data->first ();
			int maxden = 1;
			for (; rlink != NULL; rlink = rlink->next) {
				rlink->data->AutoReduce ();
				int cden = rlink->data->GetQ ();
				cout << (rlink->data->GetP ()) << "/" << (cden) << " ";
				if (cden > maxden)
					maxden = cden;
			}
			cout << "(F_" << maxden << ")";
			cout << endl;
		
			afar = new Farey ();
			afar->CreateFareySeq (3);
			afar->SetFareySeq(flink->data);	
			//afar->GetRatioList ()->append (new Ratio(1,1));
			afar->CreateCommonDenomList2 (); 
			fareylist2->append (afar);
		
			DLink<Ratio>* r; 
		
			cout << endl << "Filtered Farey Sequence orig.:" << endl;
			for (r = afar->GetFirst (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
			cout << endl;
		
			cout << endl << "Filtered Farey Sequence Diff. orig.:" << endl;
			for (r = afar->GetFirstDiff (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
			cout << endl;
		
			cout << endl << "Common Denominator: ";
			cout << afar->GetCommonDenominator () << endl;
		
			cout << endl << "Filtered Farey Sequence with common denominator:" << endl;
			for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << "/" << (r->data->GetQ ()) << " " ; 
			cout << endl;
		
			cout << endl << "in integer distance notation:" << endl;
			for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) 
				cout << (r->data->GetP ()) << " " ; 
		
			cout << endl << "and translated into tik rhythm: " << endl;
			for (r = afar->GetFirstCommonDenom (); r != NULL; r = r->next) {
				cout << 1;
				int zeros = r->data->GetP ();
				while (--zeros > 0) {
					cout << " " << 0;
				} 
				cout << " ";
			}
		
			cout << endl << endl;
			cout << "---------------------------------------------------" << endl;
		}
	
		
/// Anaysis Section ///////// --------------------------------------------------------
	
		DLink<Farey>* farlink2 = fareylist2->first ();
		for (; farlink2 != NULL; farlink2 = farlink2->next) {
			DLink<Farey>* farlink = fareylist->first ();
			for (; farlink != NULL; farlink = farlink->next) {
				cout << "-----------" << endl;
				farlink->data->AnalyseChronotonic (farlink2->data);
				farlink->data->Analyse (farlink2->data);
				farlink->data->OnsetMatches (farlink2->data);
			}
			cout << "===============================================" << endl;
		}
		
		matrix->destroy ();
		delete matrix;
		fareylist->destroy ();
		delete fareylist;
		matrix2->destroy ();
		delete matrix2;
		fareylist2->destroy ();
		delete fareylist2;
		//	delete afar;
	}

bool Modul::StringToInt (string s, int* val) {
  stringstream str(s);
  str >> (*val);

  if (!str) {
    return false;
  }
  return true;
}

bool Modul::StringToFloat(string s, float* val) {
  stringstream str(s);
  str >> (*val);

  if (!str) {
    return false;
  }
  return true;
}

void Modul::LoadAllPartitions () {
    //called by GetPartitionVector (int n, int& k, int cond, vector<float>* v)
    /*
  LoadPartitions ("./text/all_partitions_until_41_parts_only_2s_and_3s.txt", 1);
  LoadPartitions ("./text/all_COPRIME_partitions_until_120_with_2_distinct_parts.txt", 2);
  LoadPartitions ("./text/all_COPRIME_partitions_until_120_with_3_distinct_parts.txt", 3);
  LoadPartitions ("./text/all_COPRIME_partitions_until_120_with_4_distinct_parts.txt", 4);
  LoadPartitions ("./text/all_COPRIME_partitions_until_120_with_5_distinct_parts.txt", 5);
*/
    LoadPartitions ("/usr/local/share/chunking/all_partitions_until_41_parts_only_2s_and_3s.txt", 1);
    LoadPartitions ("/usr/local/share/chunking/all_COPRIME_partitions_until_120_with_2_distinct_parts.txt", 2);
    LoadPartitions ("/usr/local/share/chunking/all_COPRIME_partitions_until_120_with_3_distinct_parts.txt", 3);
    LoadPartitions ("/usr/local/share/chunking/all_COPRIME_partitions_until_120_with_4_distinct_parts.txt", 4);
    LoadPartitions ("/usr/local/share/chunking/all_COPRIME_partitions_until_120_with_5_distinct_parts.txt", 5);

}

void Modul::LoadPartitions (string filename, int k) {
  // called by LoadAllPartitions ()
  if (k < 1 || k > 5) {
    cout << k << " must be in range {1, 2, 3, 4, 5}" << endl;
    return;
  }

  ifstream file (filename.c_str());
  string line;
  string cell;

  while (file) {
      getline (file,line);
      stringstream lineStream (line);
      
      vector <float> allp;
      while (getline (lineStream, cell, ',')) {
	allp.push_back (atof(cell.c_str()));
      }
      if (k == 1) matrix_2s3s->push_back (allp);
      if (k == 2) matrix2->push_back (allp);
      if (k == 3) matrix3->push_back (allp);
      if (k == 4) matrix4->push_back (allp);
      if (k == 5) matrix5->push_back (allp);
  }

#if 0
  int i = 0;
  int size = matrix2->size ();
  for (; i < size; i++) {
    int j = 0;
    int vsize = matrix2->at(i).size();
    for (; j < vsize; j++) {
      cout << matrix2->at(i).at(j) << " ";
    }
    cout << endl;
  }
#endif
}


void Modul::GetPartition (int n, int k, int cond) {
  LoadAllPartitions ();
  int index = 0;
  switch (cond) {
  case 1:
    index = GetPartitionSmallestSigma (n, k);
    if (index < 0) {
      cout << "partition of " << n << " into " << k << " unique parts not available as coprime list." << endl;
      
      return;
    }
    break;
  default:
    cout << "condition not in range." << endl;
    return;
  }
  
  //cout << "GetPartition index: " << index << endl;

  int vsize = 0;
  int i = 0;
  switch (k) {
  case 2:
    vsize = matrix2->at(index).size ();
    i = 0;
    for (; i < vsize; i++)
      cout << matrix2->at(index).at(i) << " ";
    cout << endl;
    break;
  case 3:
    vsize = matrix3->at(index).size ();
    i = 0;
    for (; i < vsize; i++)
      cout << matrix3->at(index).at(i) << " ";
    cout << endl;
    break;
  case 4:
    vsize = matrix4->at(index).size ();
    i = 0;
    for (; i < vsize; i++)
      cout << matrix4->at(index).at(i) << " ";
    cout << endl;
    break;
  case 5:
    vsize = matrix5->at(index).size ();
    i = 0;
    for (; i < vsize; i++)
      cout << matrix5->at(index).at(i) << " ";
    cout << endl;
    break;

  default:
    break;
  }

}


void Modul::GetPartitionVector (int n, int& k, int cond, vector<float>* v) {
    //called by StartSentence (int n, int k)
  LoadAllPartitions ();
  int index = 0;
  switch (cond) {
  case 1:
    k++;
    index = -1;
    while (index < 0) {
      k--;
      if (k < 2) {
	cout << "partition of " << n << " in " << k+1 << " coprime parts not available." << endl;
	v->push_back(float(n));
	v->push_back(float(n));
	v->push_back(float(k));
	v->push_back(0.0f);
	return;
      }
        //if cond == 1,
        //returns the index into vector of partition with smallest sigma
        // that is the partition with the distinct parts being closest together
        // extreme case is arithmetic progression with delta = 1
      index = GetPartitionSmallestSigma (n, k);
    }
    break;
  default:
    cout << "condition not in range." << endl;
    return;
  }
  
  //cout << "GetPartitionVector index: " << index << endl;

  int vsize = 0;
  int i = 0;
  switch (k) {
  case 2:
    vsize = matrix2->at(index).size ();
    i = 0;
    for (; i < vsize; i++) {
      //cout << matrix2->at(index).at(i) << " ";
      v->push_back(matrix2->at(index).at(i));
    }
    //cout << endl;
    break;
  case 3:
    vsize = matrix3->at(index).size ();
    i = 0;
    for (; i < vsize; i++) {
      //cout << matrix3->at(index).at(i) << " ";
      v->push_back(matrix3->at(index).at(i));
    }
    //cout << endl;
    break;
  case 4:
    vsize = matrix4->at(index).size ();
    i = 0;
    for (; i < vsize; i++) {
      //cout << matrix4->at(index).at(i) << " ";
      v->push_back(matrix4->at(index).at(i));
    }
    //cout << endl;
    break;
  case 5:
    vsize = matrix5->at(index).size ();
    i = 0;
    for (; i < vsize; i++) {
      //cout << matrix5->at(index).at(i) << " ";
      v->push_back(matrix5->at(index).at(i));
    }
    //cout << endl;
    break;

  default:
    break;
  }

}

int Modul::GetPartitionSmallestSigma (int n, int k) {
    //returns the index into vector of partition with smallest sigma
    // that is the partition with the distinct parts being closest together
    // extreme case is arithmetic progression woth delta = 1
  int size = 0;
  int i = 0;
  int index = -1;
  if (k == 2) size = matrix2->size ();
  if (k == 3) size = matrix3->size ();
  if (k == 4) size = matrix4->size ();
  if (k == 5) size = matrix5->size ();

  //  cout << size << endl;

  float sigma = 1000.f;
  switch (k) {
  case 2:
    for (; i < size; i++) {
      if (matrix2->at(i).at(0) == n) {
	//cout << matrix2->at(i).at(0) << endl;
	if (matrix2->at(i).at(k+2) < sigma) {
	  sigma = matrix2->at(i).at(k+2);
	  index = i;
	  //cout << sigma << endl;
	}
      }
    }
    break;
  case 3:
    for (; i < size; i++) {
      if (matrix3->at(i).at(0) == n) {
        if (matrix3->at(i).at(k+2) < sigma) {
          sigma = matrix3->at(i).at(k+2);
          index = i;
        }
      }
    }
    break;
  case 4:
    for(; i < size; i++) {
      if (matrix4->at(i).at(0) == n) {
        if (matrix4->at(i).at(k+2) < sigma) {
          sigma = matrix4->at(i).at(k+2);
          index = i;
        }
      }
    }
    break;
  case 5:
    for(; i < size; i++) {
      if (matrix5->at(i).at(0) == n) {
          //if (matrix5->at(i).size() - 3 > 9)
          //    continue;
        if (matrix5->at(i).at(k+2) < sigma) {
          sigma = matrix5->at(i).at(k+2);
          index = i;
        }
      }    
    }
    break;
  default:
    break;
  }
  return index;
}


int Modul::GetPartitionHighestSigma (int n) {
    //returns index into partition into 2s and 3s with highest sigma
  // matrix_2s_3s contains only partitions into 2s and 3s
  // the most balanced distribution has a sigma of 0.5 (standard deviation)
  // all other partitions in matrix_2s_3s have lower values for sigma!
    // this is to make sure distribution of 2s and 3s is balanced in partition
  int size = 0;
  int i = 0;
  int index = -1;
  size = matrix_2s3s->size ();
  
  float sigma = -1.f;
  for (; i < size; i++) {
    if (matrix_2s3s->at(i).at(0) == n) {
        if (matrix_2s3s->at(i).size () - 3 > 9) {
            continue;
        }
      int last_elem = matrix_2s3s->at(i).size () - 1;
      if (matrix_2s3s->at(i).at(last_elem) > sigma) {
          sigma = matrix_2s3s->at(i).at(last_elem);
          index = i;
      }
    }
  }
  return index;
}

void Modul::LoadForms () {
// loads all musical forms into corresponding vectors
    // called by ctor of Modul()
  vector<string> s;
    /*
  s.push_back("./text/resistor.txt");
  s.push_back("./text/release.txt");
  s.push_back("./text/arch.txt");
  s.push_back("./text/catenary.txt");
  s.push_back("./text/alternating.txt");
  s.push_back("./text/growth.txt");
  s.push_back("./text/decrease.txt");
    */
    s.push_back("/usr/local/share/chunking/resistor.txt");
    s.push_back("/usr/local/share/chunking/release.txt");
    s.push_back("/usr/local/share/chunking/arch.txt");
    s.push_back("/usr/local/share/chunking/catenary.txt");
    s.push_back("/usr/local/share/chunking/alternating.txt");
    s.push_back("/usr/local/share/chunking/growth.txt");
    s.push_back("/usr/local/share/chunking/decrease.txt");
    
  int k = 0;
  int size = s.size();
  vector<float>* b =  new vector<float>;
  for (; k < size; k++) {
    fstream file (s[k].c_str());
    if (!file)
      cout << "error with files in LoadForms." << endl;
    //    cout << file << " " << s[k] <<endl;
    string line;
    string cell;
    
    while (file) {
      getline (file,line);
      if (line == "") {
	//cout << "error in " << s[k].c_str() << endl;
	continue;
      }
      stringstream lineStream (line);
      while (getline (lineStream, cell, ' ')) {
	if (cell == "")
	  continue;
	if (cell[0] == 'n') {
	  int array[8], count=0, data;
	  const char *s = cell.c_str();
	  char *p;
	  while(*s) {
	    if(isdigit(*s) || (*s=='-' && isdigit(s[1]))){
	      data = strtol(s, &p, 10);
	      s = p;
	      array[count++] = data;
	    } else
	      ++s;
	  }
	  char buffer [8];
	  sprintf (buffer, "%d", array[count-1]);
	  //cout << (buffer) << endl;
	  b->push_back (atof(buffer));
	} else {
	  b->push_back (atof(cell.c_str()));
	}
      }
      int len = b->size();
      int d, a = b->at(0);
      int i = 1;
      float cplx = 0.f;
      for (; i < len; i++) {
	d = b->at(i);
	Ratio r(a,d);
	r.AutoReduce ();
	a = d;
	cplx += r.Indig_ab();
      }
      cplx /= float(len);
      b->push_back(cplx);
      //PrintFloatVector (&b);
      switch (k) {
      case RESISTOR:
	resistor->push_back (*b);
	break;
      case RELEASE:
	release->push_back (*b);
	break;
      case ARCH:
	arch->push_back (*b);
	break;
      case CATENARY:
        catenary->push_back (*b);
	break;
      case ALTERNATING:
        alternating->push_back (*b);
	break;
      case GROWTH:
        growth->push_back (*b);
	break;
      case DECREASE:
        decrease->push_back (*b);
	break;
      default:
	break;
      }
      b->erase(b->begin(),b->end());
    }
  }
  delete b;
}

void Modul::LoadBracelets () {
//  ifstream file ("./text/bracelets.txt");
  ifstream file ("/usr/local/share/chunking/bracelets.txt");
  string line;
  string cell;

  while (file) {
    getline (file,line);
    stringstream lineStream (line);
    vector<float> b;
    
    while (getline (lineStream, cell, ' ')) {
      if (cell[0] == 'n') {
	int array[8], count=0, data;
	const char *s = cell.c_str();
	char *p;
	while(*s) {
	  if(isdigit(*s) || (*s=='-' && isdigit(s[1]))){
	    data = strtol(s, &p, 10);
	    s = p;
	    array[count++] = data;
	  } else
	    ++s;
	}
	char buffer [8];
	sprintf (buffer, "%d", array[count-1]);
	//cout << (buffer) << endl;
	b.push_back (atof(buffer));       
      } else {
	b.push_back (atof(cell.c_str()));
      }
    }

    int len = b.size();
    int d, a = b.at(0);
    int i = 1;
    float cplx = 0.f;
    for (; i < len; i++) {
      d = b.at(i);// << " ";
      Ratio r(a,d);
      r.AutoReduce ();
      //      cout << a << " " << d << " " << r.Indig_ab() << endl;
      a = d;
      cplx += r.Indig_ab();
    }
    cplx /= float(len);
    b.push_back(cplx);
    //PrintFloatVector (&b);
    bracelets->push_back (b);
  }
}

void Modul::ApplyMusicalTriangle (vector<float>* phrase) {
  //called by StartSentence (int n, int k) to change order
    // in vector of phrases to be in line with musical principles
  if (phrase->size () < 1) {
    cout << "error in ApplyMusicalTriangle: phrase has no content" << endl;
    return;
  }
    
  if (phrase->size () > 10) {
      cout << "error in ApplyMusicalTriangle: phrase can only have up to 7 elements" << endl;
      return;
    }

  //    cout << "triangle: " << endl;
  //PrintFloatVector (phrase);
  int psize = phrase->size () - 3;
  //cout << "psize " << psize << endl;
  int m_tri_size = m_triangles->size();
  //  cout << "m_tri_size: " << m_tri_size << endl;
  int i = 0;
  vector<int> indices;
  for (; i < m_tri_size; i++) {
    //cout << m_triangles->at(i).size() << " ";
    if (m_triangles->at(i).size() == psize)
      indices.push_back (i);
  }
  //cout << "indices size: " << indices.size() << endl;
  vector<float> t;
  srand (time(NULL));
  int isize = indices.size();
  if (isize) {
    int r = rand() % indices.size();
    vector<int> sel(m_triangles->at(indices[r]));
    t.push_back(phrase->at(0));
    int tsize = sel.size();
    for (i=0; i < tsize; i++) {
      t.push_back (phrase->at(sel[i]+1));
    }
    t.push_back (phrase->at(phrase->size()-2));
    t.push_back (phrase->at(phrase->size()-1));
    
  } else {
    if (psize == 2) {
            // if partition only has 2 parts then randomly swap their position
      t.push_back(phrase->at(0));
      //cout << "phrase size: " << phrase->size () << endl;
      int r = rand() % 2;
      if (r) {
	t.push_back (phrase->at(2)); t.push_back (phrase->at(1));
      } else {
	t.push_back (phrase->at(1)); t.push_back (phrase->at(2));
      }
      t.push_back(phrase->at(phrase->size()-2));
      t.push_back (phrase->at(phrase->size()-1));
    } 
    //    else if (psize == 1) {
    //}
  } 
  //PrintFloatVector (&t);
  if (psize > 1)
    phrase->swap (t);
  //cout << endl << "end triangle -- " << endl;
}

void Modul::StartSentence (int n, int k) {
  // subdivide n pulses into k phrases
  // each phrase into k patterns
  // each pattern into chunks of 2s or 3s
  // max 120 pulses into max 7 phrases
  if (n < 1 || n > 120) { 
    cout << "error in StartSentence: n must be in the range [1...120]" << endl; 
    return;
  }
  int num_pulses = n;
  // sentence
  // phrase
  // patterns
  // 2s and 3s
  // chunks
    // output shorthand strings to text file
    ofstream fptrt;
    string textsfile = "sentence_" + to_string(n) + "_" + to_string(k) + ".txt";
    fptrt.open (textsfile.c_str(), ios_base::out);
    if (!fptrt)
        cerr << "cannot write file: " << textsfile << endl;

  //output of lilypond file
  ofstream fptr; 
  string lilyfile = "sentence_" + to_string(n) + "_" + to_string(k) + ".ly";
  fptr.open (lilyfile.c_str(), ios_base::out);
  if (!fptr)
    cerr << "cannot write file: " << lilyfile << endl;
  fptr << "\\version \"2.18.2\"" << endl; 
  //output of csound score file
  ofstream fptr2;
  string orcfile = "sentence_" + to_string(n) + "_" + to_string(k) + ".sco";
  fptr2.open (orcfile.c_str(), ios_base::out );
  if (!fptr2)
    cerr << "cannot write file: " << orcfile << endl;
  float onset = 0.f; float onset_sentence = 0.f; float onset_phrase = 0.f;
  float period = 1.f;

  int num_trans = 6; // number of transcriptions of one sentence calculation
  bool init_ly_file = true;
  vector<vector<float > >* selected_chunks = new vector<vector<float > >;
  vector<vector<float > >* selected_chunks2 = new vector<vector<float > >;
  int check_n = 0;
  int sc_size = 0; //selected_chunks->size ();
  int psize = 0; //pattern_chunks->size();
  // vector to store various possible phrases:
  vector<vector<float > >* vec = new vector<vector<float > >;
  vector<vector<string> >* matrix = new vector<vector<string> >;

  //for csound score phrase envelopes:
  //vector<vector<float> > phrase_envs;

  // allow only 1 - 7 distinct parts in partition
  if (k > 6) k = 7;
  if (k < 1) k = 1;
  int reset_k = k;
  vector<float> phrases;
    //copy all (n,k) partitions into phrases
  GetPartitionVector (n, k, 1, &phrases);
  // change order in phrases according to musical principles 
  ApplyMusicalTriangle (&phrases);
  vec->push_back(phrases);
  cout << "Sentence with n = " << n << " pulses and " << k << " parts:" << endl;
  PrintFloatVector (&phrases, true);
  //store csound instrument statement:
  // for each transcription it needs to be repeated with its onset updated

    //apply subdivision of sentence into phrases (partitions)
    // and apply musical triangle shapes to resulting vectors
  int size = k+1;
  int i = 1;
  for (; i < size; i++) {
    vector<float> patterns;
    k = reset_k;
    GetPartitionVector (phrases[i], k, 1, &patterns);
    // change order in patterns according to musical principles  
    ApplyMusicalTriangle (&patterns);
    vec->push_back (patterns);
    cout << "Phrases with n = " << phrases[i] << " pulses and " << k << " parts:" << endl;
    PrintFloatVector (&patterns, true);
    //store csound instrument statement:  
    // for each transcription they need to be repeated with onsets updated                                                                                       
    patterns.erase (patterns.begin (), patterns.end ());
  }
  
  vector<vector<float > >* pattern_chunks = new vector<vector<float > >;
  size = vec->size ();
  for (i = 1; i < size; i++) {
    // go over the patterns and create 2-3 chunks
    //cout << i << ": " << endl;
    //PrintFloatVector (&vec->at(i));
    int length = vec->at(i).size () - 2;
    //cout << length << endl;
    int j = 1;
    for (; j < length; j++) {
      // GetPartitionHighestSigma returns index into partition into 2s and 3s with highest sigma
      // matrix_2s_3s contains only partitions into 2s and 3s
      // the most balanced distribution has a sigma of 0.5 (standard deviation)
      // all other partitions in matrix_2s_3s have lower values for sigma!
      // this is to make sure distribution of 2s and 3s is balanced in partition              
      // maximum balance of number of 2s and 3s is enabling a greater probability of
      // transitions between 2 and 3.
      int index = GetPartitionHighestSigma (vec->at(i).at(j));
      //cout << "GetPartitionHighestSigma index: " << index << endl;
        if (index < 0) {
            cout << "partition not available, try using a smaller n or a higher k." << endl;
            goto cleanup;
        }
      //PrintFloatVector(&matrix_2s3s->at(index));
      int sec = matrix_2s3s->at(index).size () - 2;
      int t = 0;
      vector<float> a_pattern;
      for (; t < sec; t++) {
	// 2s 3s chunks of patterns
	//cout << matrix_2s3s->at(index).at(t) << " ";
        a_pattern.push_back (matrix_2s3s->at(index).at(t));
      }
      pattern_chunks->push_back (a_pattern);
      //cout << endl;
    }    
  } 

//  vector<vector<float > >* selected_chunks = new vector<vector<float > >;
  // old: pick one of the matching bracelets then pick a random rotation                                              
  // MatchBracelets (pattern_chunks, selected_chunks);

  // Pick one bracelet according to one of the patterns of musical tension
  // 1. resistor 2 2 2 3 3
  // 2. resistor-release 3 3 2 2 2
  // 3. arch 2 2 3 3 2  
  // 4. catenary 3 3 2 2 2 3
  // 5. alternating 2 3 2 3 2 3
  // 6. growth 2 3 2 2 3 2 2 2 3
  // 7. decreasing 2 2 2 3 2 2 3 2 3

  psize = pattern_chunks->size();
  cout << "Patterns using partitions into 2s and 3s:" << endl;
  for (i = 0; i < psize; i++) {
    PrintFloatVector(&pattern_chunks->at(i));
  }

  // 1. take first element (n) from each pattern in pattern_chunks
  // 2. search the musical forms, if n is contained push back musical form into list of ints
  // 3. make a random selection from that list
  // 4. pick the pattern from the appropriate form vector (there might be another random choice to make within the vector)
  // 5. store the pattern
  // 6. store the form selection
  // 7. go to the next pattern in pattern_chunks. 
  // 8. in step 3. try to exclude repetition of previous form pattern 

  PickMusicalForm (pattern_chunks, selected_chunks);

  //vector<vector<float > >* selected_chunks2 = new vector<vector<float > >;

  srand (time(NULL));
  sc_size = selected_chunks->size ();
  //cout << "selected chunks: ----------------------" << endl;
  n = 0;
  for (i = 0; i < sc_size; i++) {
    //PrintFloatVector(&selected_chunks->at(i));
    int s = selected_chunks->at(i).size();
    if (s == 1) {
      n = selected_chunks->at(i).at(0);
      if (n==2 || n==3) {
          vector<float> scv;
          PickMusicalFormViaIndex (n, &scv, selected_chunks->at(i).at(0), 0);
          selected_chunks2->push_back(scv);
      }
    }
    if (s > 1) {
    	if (selected_chunks->at(i).at(1) > -1) {
 	vector<float> scv;
	int r = rand() % s;
	int aform = selected_chunks->at(i).at(r);
	//cout << "length " << n << " selecting form " << aform << " at index " << r << endl;
	PickMusicalFormViaIndex (n, &scv, aform, r);
	if (aform == RELEASE || aform == DECREASE) {
	  float temp = scv.back ();
	  scv.pop_back ();
      reverse(scv.begin(), scv.end());
	  scv.push_back (temp);
	}
	selected_chunks2->push_back(scv);
      }
    }
  }

  sc_size = selected_chunks2->size ();
  cout << "Partitions of patterns transformed into musical patterns:" << endl;
  for (i = 0; i < sc_size; i++) {
    int scsize = selected_chunks2->at(i).size();
    if (scsize > 1)
      selected_chunks2->at(i).pop_back ();
    PrintFloatVector(&selected_chunks2->at(i));
  }

  check_n = 0;
  for (i = 0; i < sc_size; i++) {
    int scsize = selected_chunks2->at(i).size();
    int j = 0;
    for (; j<scsize; j++) {
      check_n += selected_chunks2->at(i).at(j);
    }
  }
    cout << "Combined number of pulses: " << num_pulses << endl; // << " check: " << check_n << endl;
  if (num_pulses != check_n)
    cout << "hm... something wrong?" << endl;

  //translate to shorthand and print out
    
  init_ly_file = true;
  cout << "Transcriptions:" << endl;
  onset = 0.f;
  num_trans = 8;
  period = .22f;
  while (num_trans-- > 0) {
    for (i = 0; i < sc_size; i++) {
      int scsize = selected_chunks2->at(i).size();
      int j = 0;
      string outpattern = "";
      for (; j<scsize; j++) {
          outpattern += PickRhythmChunk (selected_chunks2->at(i).at(j));
          outpattern += " ";
      }
      cout << outpattern << endl;
        fptrt << outpattern << endl;
        
      WriteToLilyfile (fptr, outpattern, init_ly_file, false); 
      if (init_ly_file == true)
        init_ly_file = false;
      
      WriteToCsoundScore (fptr2, outpattern, &onset, period);
    }
    WriteToLilyfile (fptr, " ", false, true);
    init_ly_file = true;
    cout << "---------------" << endl;

    //this is for the envelope control of whole sentence i3:
    // use fptr2 to write envelope instruments to csound score: 
    PrintSentenceStatement (fptr2, &phrases, &onset_sentence, period, 3);
    
    size = vec->size ();
    int q = 1;
    for (q = 1; q < size; q++) {
      //this is for the phrases i2:
      PrintSentenceStatement (fptr2, &vec->at(q), &onset_phrase, period, 2);
      //PrintFloatVector(&vec->at(i), true);
    }
  }

#if 0
  // for loading melody lines  in midi pitch format, can be float for micro-tuning                                                                                                     
  LoadMelodyFromFile("melody.txt", *matrix);

  for (int i=0; i < int (matrix->size()); i++) {
    for (int j=0; j < int (matrix->at(i).size()); j++) {
      cout << matrix->at(i).at(j) << " ";
    }
    cout << endl;
  }
#endif

#if 0
  // for loading template instrument lines
  SentenceToCsound("instr_string.txt", *matrix);
  
  for (int i=0; i < int (matrix->size()); i++) {
    for (int j=0; j < int (matrix->at(i).size()); j++) {
      cout << matrix->at(i).at(j) << " ";
    }
    cout << endl;
  }
#endif

cleanup:
  delete matrix;
  delete pattern_chunks;
  delete vec;
  delete selected_chunks;
  delete selected_chunks2;

}

void Modul::WriteToCsoundScore (ofstream& s, string pattern, float* onset, float period) {
  Decoder* dec = new Decoder;
  int meter = 0;
  string csound_code = "";
  string measure_grouping = "; grouping: ";
  vector<float> notes;
  
  //  float period = 1.f; // eighth = 240 BPM

  for ( string::iterator it=pattern.begin(); it!=pattern.end(); ++it) {
    if (char(*it) != ' ') {
      int code = dec->decode_shorthand_length (int(*it));
      meter += code;
      measure_grouping = measure_grouping + to_string(code) + " ";
      dec->decode_for_csound2 (int(*it), period, onset, notes);
      //int notes_size = notes.size();
      //int i = 0;
      //for (; i < notes_size; i+=2) {
      //csound_code += "i1 " + to_string(notes[i]) + " " + to_string(notes[i+1]) + "\n"; 
      //}
    }
  }

  int notes_size = notes.size();
  int i = 0;
  for (; i < notes_size; i+=3) {
    csound_code += "i1 " + to_string(notes[i]) + " " + to_string(notes[i+1]) + " " + to_string(notes[i+2]) + "\n";
  }
  s <<  measure_grouping; 
  s << endl;
  s << csound_code << endl;
  
  delete dec;
}

void Modul::WriteToCsoundScore2 (ofstream& s, string pattern, float* onset, float period) {
    Decoder* dec = new Decoder;
    
    dec->SetPitches (GetPitches ());
    dec->SetPitchLine (GetPitchLine ());

    int meter = 0;
    string csound_code = "";
    string measure_grouping = "; grouping: ";
    vector<float> notes;
    
    //  float period = 1.f; // eighth = 240 BPM
    
    for ( string::iterator it=pattern.begin(); it!=pattern.end(); ++it) {
        if (char(*it) != ' ') {
            int code = dec->decode_shorthand_length (int(*it));
            meter += code;
            measure_grouping = measure_grouping + to_string(code) + " ";
            dec->decode_for_csound3 (int(*it), period, onset, notes);
        }
    }
    
    int notes_size = notes.size();
    int i = 0;
    for (; i < notes_size; i+=4) {
        csound_code += "i1 " + to_string(notes[i]) + " " + to_string(notes[i+1]) + " " + to_string(notes[i+2]) + " " + to_string(notes[i+3]) + "\n";
    }
    s << measure_grouping << endl;
    s << csound_code << endl;
    
    delete dec;
}

void Modul::WriteToLilyfile (ofstream& s, string pattern, bool init, bool finish, bool grouping) {
  if (finish) {
    s << " \\bar \"||\" "; 
    s << "}" << endl;
      if (grouping) {
          s << "\\layout {\\context {\\Staff \\consists \"Measure_grouping_engraver\" }}" << endl;
          //s << "\\midi {\\tempo 4 = 120 }" << endl << "}" << endl;
      } else {
          s << "\\layout {}" << endl;
          s << "\\midi {\\tempo 4 = 120 }" << endl;
      }
    s << "}" << endl;
    return;
  }
  
  if (init) {
//      s << "\\score {" << endl << "\t" << "\\new Staff \\relative c\' {";
      s << "\\score {" << endl << "\t" << "\\new Staff  {";
  }

  Decoder* dec = new Decoder;
  dec->SetPitches (GetPitches ());
  dec->SetPitchLine (GetPitchLine ());
  int meter = 0;
  string lilypond_code = "";
  string measure_grouping = "#\'(";
  for (string::iterator it=pattern.begin(); it!=pattern.end(); ++it) {
    if (char(*it) != ' ') { //ignore empty spaces                                                                                                    
      //s << *it;
      int code = dec->decode_shorthand_length (int(*it));
        if (code > 0) {
            meter += code;
            if (grouping)
                measure_grouping = measure_grouping + to_string(code) + " ";
        }
        lilypond_code += dec->decode_for_lilypond (int(*it));
        lilypond_code += " ";
        //cout << (int(*it)) << "=" << *it << endl; //lilypond_code << endl;
            //s << " " << code << " ";
    }
  }
  //  lilypond_code += "\\bar \"||\"";
    if (grouping) {
        measure_grouping += ")";
        if (meter > 0) {
            s << "\\time " << measure_grouping << " " << meter << "/" << 8 << " " << lilypond_code;
        }
    } else {
        if (meter > 0 && meter != meter_store) {
            s << "\\time " << meter << "/" << 8 << " ";
            meter_store = meter;
        }
        s << lilypond_code << " ";
    }
  
  s << endl;
  
  //  s << pattern << endl;
  delete dec;

}

string Modul::PickRhythmChunk (int g) {
  //takes either 2 or 3 from input g
  //translates into random rhythm chunk of length 2 or 3
  //returns the shorthand symbol as a string

  string binary_chunks = "vIII::";
  int bchunks_len = binary_chunks.length ();
  string ternary_chunks = "w---ii>><+XX";
  int tchunks_len = ternary_chunks.length ();
  //srand (time(NULL));
  int select = 0;
  string outcode = "";
  switch (g) {
  case 2:
    select = rand () % bchunks_len;
    outcode = binary_chunks[select];//cout << g << ": " << select << " ";
    break;
  case 3:
    select = rand () % tchunks_len;
    outcode = ternary_chunks[select];//cout << g << ": " << select << " ";
    break;
  case 4:
    outcode = "H";
  default:
    break;

  } 
  return outcode;
}

void Modul::PickMusicalForm (vector<vector<float > >* pattern_chunks, vector<vector<float > >* selected_chunks){
    // called by StartSentence (int n, int k)
    
  //cout << "pick musical form -----------" << endl;
  vector<float> forms;
  int psize = pattern_chunks->size ();
  int i = 0;
  for (; i < psize; i++) {
    int n = pattern_chunks->at(i).at(0);
    vector<float> a;
    a.push_back(n);
 
    if (n < 4) {
      vector<float> b;
      b.push_back(n);
      selected_chunks->push_back(b);
      continue;
    }

    selected_chunks->push_back(a); // save the size of the pattern chunk  
 
    int k =0 ,m = 0; 
    bool match = false;
    for (; k < NUMFORMS; k++) {
      switch (k) {
      case RESISTOR:
	for (m=0; m < resistor->size (); m++) {
	  if (n == resistor->at(m).at(0)) {
	    match = true;
            int j = 1;
        //cout << "resistor===================" << endl;
	    //PrintFloatVector (&pattern_chunks->at(i));
	    //PrintFloatVector (&resistor->at(m));
	    while (match) {
	      //PrintFloatVector (&resistor->at(m+j));
            forms.push_back (RESISTOR);
            j++;
            if (j == resistor->size () || (m+j) == resistor->size ()) {
                match = false;
                break;
            }
            int first = resistor->at(m+j).at(0);
            if (first > 3)
                match = false;
	    }
	  }
	}
	break;
      case RELEASE:
        for (m=0; m < release->size (); m++) {
          if (n == release->at(m).at(0)) {
            match = true;
            int j = 1;
            //cout << "release===================" << endl;
            //PrintFloatVector (&pattern_chunks->at(i));
            //PrintFloatVector (&release->at(m));
            while (match) {
              //PrintFloatVector (&release->at(m+j));
              forms.push_back (RELEASE);
              j++;
              if (j == release->size () || (m+j) == release->size ()) {
                match = false;
                break;
              }
              int first = release->at(m+j).at(0);
              if (first > 3)
                match = false;
            }
          }
        }
        break;
      case ARCH:
	for (m=0; m < arch->size (); m++) {
          if (n == arch->at(m).at(0)) {
            match = true;
            int j = 1;
            //cout << "arch===================" << endl;
            //PrintFloatVector (&pattern_chunks->at(i));
            //PrintFloatVector (&arch->at(m));
            while (match) {
              //PrintFloatVector (&arch->at(m+j));
              forms.push_back (ARCH);
              j++;
              if (j== arch->size () || (m+j) == arch->size ()) {
                match = false;
                break;
              }
              int first = arch->at(m+j).at(0);
              if (first > 3) 
		match = false;
            }
          }
	}
        break;
      case CATENARY:
        for (m=0; m < catenary->size (); m++) {
          if (n == catenary->at(m).at(0)) {
            match = true;
            int j = 1;
            //cout << "catenary===================" << endl;
            //PrintFloatVector (&pattern_chunks->at(i));
            //PrintFloatVector (&catenary->at(m));
            while (match) {
              //PrintFloatVector (&catenary->at(m+j));
              forms.push_back (CATENARY);
              j++;
              if (j== catenary->size () || (m+j) == catenary->size ()) {
                match = false;
                break;
              }
              int first = catenary->at(m+j).at(0);
              if (first > 3)
                match = false;
            }
          }
        }
        break;
      case ALTERNATING:
        for (m=0; m < alternating->size (); m++) {
          if (n == alternating->at(m).at(0)) {
            match = true;
            int j = 1;
            //cout << "alternating===================" << endl;
            //PrintFloatVector (&pattern_chunks->at(i));
            //PrintFloatVector (&alternating->at(m));
            while (match) {
              //PrintFloatVector (&alternating->at(m+j));
              forms.push_back (ALTERNATING);
              j++;
              if (j == alternating->size () || (m+j) == alternating->size ()) {
                match = false;
                break;
              }
              int first = alternating->at(m+j).at(0);
              if (first > 3)
                match = false;
            }
          }
        }
        break;
      case GROWTH:
        for (m=0; m < growth->size (); m++) {
          if (n == growth->at(m).at(0)) {
            match = true;
            int j = 1;
            //cout << "growth===================" << endl;
            //PrintFloatVector (&pattern_chunks->at(i));
            //PrintFloatVector (&growth->at(m));
            while (match) {
              //PrintFloatVector (&growth->at(m+j));
              forms.push_back (GROWTH);
              j++;
              if (j== growth->size () || (m+j) == growth->size ()) {
                match = false;
                break;
              }
              int first = growth->at(m+j).at(0);
              if (first > 3)
                match = false;
            }
          }
        }
        break;
      case DECREASE:
        for (m=0; m < decrease->size (); m++) {
          if (n == decrease->at(m).at(0)) {
            match = true;
            int j = 1;
            //cout << "decrease===================" << endl;
            //PrintFloatVector (&pattern_chunks->at(i));
            //PrintFloatVector (&decrease->at(m));
            while (match) {
              //PrintFloatVector (&decrease->at(m+j));
              forms.push_back (DECREASE);
              j++;
              if (j== decrease->size () || (m+j) == decrease->size ()) {
                match = false;
                break;
              }
              int first = decrease->at(m+j).at(0);
              if (first > 3)
                match = false;
            }
          }
        }
	break;
      default:
        break;
      }
    }

#if 0
      //cout << "forms size: " << forms.size() << endl;
    int f = 0;
    for (; f < forms.size(); f++) {
      cout << forms[f] << " ";
    }
    if (forms.size())
      cout << endl;
#endif    
    selected_chunks->push_back(forms);
    forms.erase (forms.begin(), forms.end());
  }
  //cout << "end ------------" << endl;
}


void Modul::PickMusicalFormViaIndex (int n, vector<float>* selected_chunks, int form, int form_index) {
// called by StartSentence (int n, int k)
  
  if (n == 2 || n== 3) {
    vector<float> a;
    a.push_back(n);
    *selected_chunks =  (a);
    return;
  }

  int fc = 0;  
  //  cout << "n: " << n << " form: " << form << " index: " << form_index << endl;

  int k =0 ,m = 0;
  bool match = false;
  for (; k < NUMFORMS; k++) {
    switch (k) {
    case RESISTOR:
      for (m=0; m < resistor->size (); m++) {
	if (n == resistor->at(m).at(0)) {
	  match = true;
	  int j = 1;
	  //cout << "resistor===================" << endl;
	  //PrintFloatVector (&pattern_chunks->at(i));
	  //PrintFloatVector (&resistor->at(m));
	  while (match) {
	    //PrintFloatVector (&resistor->at(m+j));
	    //cout << RESISTOR << " " << fc << endl;
	    if (form == RESISTOR && form_index == fc) {
	      *selected_chunks = (resistor->at(m+j));
	      return;
	    }
	    fc++;
	    j++;
	    if (j == resistor->size () || (m+j) == resistor->size ()) {
	      match = false;
	      break;
	    }
	    int first = resistor->at(m+j).at(0);
	    if (first > 3)
	      match = false;
	  }
	}
      }
      break;
    case RELEASE:
      for (m=0; m < release->size (); m++) {
	if (n == release->at(m).at(0)) {
          match = true;
          int j = 1;
          while (match) {
            //cout << RELEASE << " " << fc << endl;
            if (form == RELEASE && form_index == fc) {
              *selected_chunks = (release->at(m+j));
	      return;
	    }
            fc++;
            j++;
            if (j == release->size () || (m+j) == release->size ()) {
              match = false;
              break;
            }
            int first = release->at(m+j).at(0);
            if (first > 3)
              match = false;
          }
        }
      }
      break;
    case ARCH:
      for (m=0; m < arch->size (); m++) {
	if (n == arch->at(m).at(0)) {
          match = true;
          int j = 1;
          while (match) {
            //cout << ARCH << " " << fc << endl;
            if (form == ARCH && form_index == fc) {
              *selected_chunks = (arch->at(m+j));
	      return;
	    }
	    fc++;
            j++;
            if (j == arch->size () || (m+j) == arch->size ()) {
              match = false;
              break;
            }
            int first = arch->at(m+j).at(0);
            if (first > 3)
              match = false;
          }
        }
      }
      break;
    case CATENARY:
      for (m=0; m < catenary->size (); m++) {
	if (n == catenary->at(m).at(0)) {
          match = true;
          int j = 1;
          while (match) {
            //cout << CATENARY << " " << fc << endl;
            if (form == CATENARY && form_index == fc) {
              *selected_chunks = (catenary->at(m+j));
	      return;
	    }
            fc++;
            j++;
            if (j == catenary->size () || (m+j) == catenary->size ()) {
              match = false;
              break;
            }
            int first = catenary->at(m+j).at(0);
            if (first > 3)
              match = false;
          }
        }
      }
      break;
    case ALTERNATING:
      for (m=0; m < alternating->size (); m++) {
	if (n == alternating->at(m).at(0)) {
          match = true;
          int j = 1;
          while (match) {
            //cout << ALTERNATING << " " << fc << endl;
            if (form == ALTERNATING && form_index == fc) {
              *selected_chunks = (alternating->at(m+j));
	      return;
	    }
            fc++;
            j++;
            if (j == alternating->size () || (m+j) == alternating->size ()) {
              match = false;
              break;
            }
            int first = alternating->at(m+j).at(0);
            if (first > 3)
              match = false;
          }
        }
      }
      break;
    case GROWTH:
      for (m=0; m < growth->size (); m++) {
        if (n == growth->at(m).at(0)) {
          match = true;
          int j = 1;
          while (match) {
            //cout << GROWTH << " " << fc << endl;
            if (form == GROWTH && form_index == fc) {
              *selected_chunks = (growth->at(m+j));
	      return;
	    }
            fc++;
            j++;
            if (j == growth->size () || (m+j) == growth->size ()) {
              match = false;
              break;
            }
            int first = growth->at(m+j).at(0);
            if (first > 3)
              match = false;
          }
        }
      }
      break;
    case DECREASE:
      for (m=0; m < decrease->size (); m++) {
        if (n == decrease->at(m).at(0)) {
          match = true;
          int j = 1;
          while (match) {
            //cout << DECREASE << " " << fc << endl;
            if (form == DECREASE && form_index == fc) {
              *selected_chunks = (decrease->at(m+j));
	      return;
	    }
            fc++;
            j++;
            if (j == decrease->size () || (m+j) == decrease->size ()) {
              match = false;
              break;
            }
            int first = decrease->at(m+j).at(0);
            if (first > 3)
              match = false;
          }
        }
      }
      break;
    default:
      break;
    }
  }
}


void Modul::MatchBracelets (vector<vector<float > >* pattern_chunks, vector<vector<float > >* selected_chunks) {
    // currently not used by StartSentence(), older design.
  LoadBracelets ();
  int size = pattern_chunks->size ();
  for (int i=0; i < size; i++) {
    int pattern_length = pattern_chunks->at(i).at(0);
    int bsize = bracelets->size ();
    int k = 0;
    bool match = false;
    for (; k < bsize;  k++) {
      int b0 = bracelets->at(k).at(0);
      if (b0 == pattern_length) {
        match = true;
        int j = 1;
        cout << "===================" << endl;
        PrintFloatVector (&pattern_chunks->at(i));
        while (match) {
          PrintFloatVector (&bracelets->at(k+j));
          //push pattern length for later processing                                                                           
          vector<float>::iterator it = bracelets->at(k+j).begin();
          it = bracelets->at(k+j).insert(it, pattern_length);
          selected_chunks->push_back (bracelets->at(k+j));
          //remove pattern length from bracelets                                                                               
          bracelets->at(k+j).erase(it);
          j++;
	  if (j == bsize) {
	    match = false;
	    break;
	  }
          int first = bracelets->at(k+j).at(0);
          if (first > 3) match = false;
        }
      }
    }
  }
}

void Modul::PickBracelet (vector<float>* v, int n) {


}

void Modul::PrintSentenceStatement (ofstream& s, vector<float>* v, float* onset, float period, int instr) {
  //prints an instrument statement "i3" for a csound score
  s << ";    p3 = sentence length, p4 = ascending, p5 = descending phrase lengths in secs" << endl;
  int size = v->size() - 2;
  int i = 0;
  float dur = v->at(0) * period;
  s << "i" << instr << " " << (*onset) << " " << dur << " ";
  *onset += dur;
  float divide = (size-1) / 2.f + 0.5f;
  int peak = int(divide); float ascend = 0.f; float descend = 0.f;
  for (i=1; i <= peak; i++) ascend += v->at(i);

  for (i=peak+1; i < size; i++) descend += v->at(i);

  ascend *= period; descend *= period;

  s << ascend << " " << descend << endl;
  //cout << "onset after: " << *onset << endl;
}

void Modul::PrintFloatVector (vector<float>* v, bool flag) {
  //if flag is set, the last two elements are ignored
  int size = v->size();
    if (flag) {
        size -= 2;
    }
  int i = 0;
  cout << "v: ";
  for (; i < size; i++) {
    cout << v->at(i) << " ";
  }
  cout << endl;
}

void Modul::BWT (string word) {
    string bwtfile = "bwt_phrases.txt";
    ofstream fptr;
    fptr.open (bwtfile.c_str(), ios_base::out );
    if (!fptr)
        cerr << "cannot write file: " << bwtfile << endl;

    cout << "BWT of " << word << endl;
    Christoffel c;
    c.SetAsciiPitchWord (word);
    c.burrows_wheeler_trans ();
    int len = c.length_word ();
    cout << "length = " << len << endl;
    int j = 1;
    for (; j <= len; j++) {
        string temp = c.burrows_wheeler_inverse2 (j);
        cout << "$ Block #" << j << " " << temp << endl;
        fptr << "$ Block #" << j << " " << temp << endl;
        stringstream strs (temp);
        string pat;
        while (getline (strs, pat, ',')) {
            cout << pat << endl;
            fptr << pat << endl;
        }
    }
    cout << endl;
    //fptr << endl;
}

void Modul::BWTmelodies (string word, int trans, string gestalt) {
    string bwtfile = "bwt_melody.txt";
    ofstream fptr;
    fptr.open (bwtfile.c_str(), ios_base::out );
    if (!fptr)
        cerr << "cannot write file: " << bwtfile << endl;
    
    string bwtfile2 = "bwt_ones.txt";
    ofstream fptr2;
    fptr2.open (bwtfile2.c_str(), ios_base::out );
    if (!fptr2)
        cerr << "cannot write file: " << bwtfile2 << endl;
    
    cout << "BWT of " << word << endl;
    Decoder* dec = new Decoder;
    vector<int> pitches;
    for (string::iterator it=word.begin(); it!=word.end(); ++it)
    {
        if (char(*it) != ' ') { //ignore empty spaces
            //cout << *it;
            int code = dec->asciipitch_to_midi (int(*it)) + trans;
            pitches.push_back (code);
        }
    }
    
    cout << "MIDI: " << endl;
    for (vector<int>::iterator it=pitches.begin() ; it!=pitches.end(); ++it) {
        cout << *it << " = " << char(dec->midi_to_asciipitch(*it)) << ", ";
    }
    cout << endl;
    // calculate intervals
    vector<int> dx(pitches.size());
    adjacent_difference (pitches.begin(), pitches.end(), dx.begin());
    /*
    for (vector<int>::iterator it=dx.begin() ; it!=dx.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;
    */
    cout << "Inversion:" << endl;
    int count = pitches.size(); string inversion = "";
    int cur = pitches[0]; int i=1;
    while (count--) {
        inversion += char(dec->midi_to_asciipitch(cur));
        cout << cur << " = " << char(dec->midi_to_asciipitch(cur)) << ", ";
        cur -= dx[i++];
    }
    cout << endl;
    cout << "Retrograde:" << endl;
    string retrograde = "";
    for (vector<int>::iterator it=pitches.end()-1 ; it>=pitches.begin(); --it) {
        retrograde += char(dec->midi_to_asciipitch(*it));
        cout << *it << " = " << char(dec->midi_to_asciipitch(*it)) << ", ";
    }
    cout << endl;
    cout << "Inversion of Retrograde:" << endl;
    string inv_retrograde = "";
    count = pitches.size();
    cur = pitches[count-1]; i=count-1;
    while (count--) {
        inv_retrograde += char(dec->midi_to_asciipitch(cur));
        cout << cur << " = " << char(dec->midi_to_asciipitch(cur)) << ", ";
        cur += dx[i--];
    }
    cout << endl;
    
    if (gestalt == "u") {
        word = inversion;
    }
    if (gestalt == "k") {
        word = retrograde;
    }
    if (gestalt == "q") {
        word = inv_retrograde;
    }
    //word = inversion;
    //word = retrograde;
    //word = inv_retrograde;
    
    Christoffel c;
    c.SetAsciiPitchWord (word);
    c.burrows_wheeler_trans ();
    int len = c.length_word ();
    cout << "length = " << len << endl;
    int j = 1;
    for (; j <= len; j++) {
        string temp = c.burrows_wheeler_inverse2 (j);
        //fptr << "$ Block #" << j << " " << temp << endl;
        cout << "Block #" << j << endl << temp << endl;
        stringstream strs (temp);
        string pat;
        while (getline (strs, pat, ',')) {
            cout << pat << endl;
            //fptr << pat << endl;
            for (string::iterator it=pat.begin(); it!=pat.end(); ++it) {
                if (char(*it) != ' ') { //ignore empty spaces
                    int midinote = dec->asciipitch_to_midi (int(*it));
                    fptr << midinote;
                    fptr2 << "I";
                    if (it!=pat.end()-1)
                        fptr << ", ";
                    cout << dec->midi_to_notename (midinote) << ", ";
                }
            }
            cout << endl;
            fptr << endl;
            fptr2 << endl;
        }
    }
    cout << endl;
    delete dec;
}

void Modul::AnalysePhrases (string filename, int minbeat, int maxbeat) {
	ifstream file (filename.c_str());
	string line;
	string cell;
	
	DList<DList<string> >* smatrix;
	DList<DList<int> >* imatrix;
	DList<string>* cmatrix;
	DList<string>* srow;
	DList<int>* irow;
	
	DList<string>* shorthand_matrix;
	
	smatrix = new DList<DList<string> >;
	imatrix = new DList<DList<int> >;
	cmatrix = new DList<string>;
	
	shorthand_matrix = new DList<string>;
	
	while (file)
	{
		getline (file,line);
		stringstream lineStream (line);
		srow = new DList<string>;
		while (getline( lineStream, cell, '\t')) {
			srow->append(new string(cell.c_str()));
		}
		
		if( srow->GetSize() ) {
			smatrix->append (srow);
		} else {
			srow->destroy ();
			delete srow;
		}
		
	}
	
	Decoder* dec = new Decoder;	
	string s = "I-II";
	//cout << "Enter rhythmic shorthand pattern to analyse: ";
	//getline(cin, s);
	
	DLink<DList<string> >* slink = smatrix->first ();
	
	for (; slink!= NULL; slink = slink->next) {
		int fn = slink->data->GetSize ();
		if (fn > 0) {
		  //			int count = 0;
			DLink<string>* rowlink = slink->data->first ();
			string test;
			string shstring;
			string temp = "";
			if (atoi(rowlink->data->c_str()) == 0) {
                if (rowlink->data->find ("$") == string::npos) {
                
                
				irow = new DList<int>;
				for (; rowlink != NULL; rowlink	= rowlink->next) {
					string cur = *rowlink->data;
					test += cur;
					shstring += (cur + " ");
					if (atoi(cur.c_str()) == 0) {
						
						for ( string::iterator it=cur.begin(); it!=cur.end(); ++it)
						{
                            if (char(*it) != ' ') { //ignore empty spaces
                                cout << *it;
                                int code = dec->decode_shorthand_length (int(*it));
                                irow->append (new int(code));
                                temp += dec->decode_shorthand_symbol (int(*it));
                            }
						}
						cout << " | ";
					}
				}
				imatrix->append (irow);					
				shorthand_matrix->append(new string(shstring));
				
				//cout << " levenshtein:" << (levenshtein((char*)test.c_str(), (char*)s.c_str()));
				//cout << endl;
				cmatrix->append (new string(temp));
            }
			}
		}
	}
	
	cout << endl;
	
	DLink<DList<int> >* ilink = imatrix->first ();
	DList<int>* durations = new DList<int>;
	// Analysis of group lengths and transitions between them, i.e. 2 2 3 3 2
	for (; ilink!= NULL; ilink = ilink->next) {
        int fn = ilink->data->GetSize ();
		if (fn > 0) {
			int accum = 0;
			DLink<int>* rowlink = ilink->data->first ();

			int ncur = 0;
			for (; rowlink->next != NULL; rowlink = rowlink->next) {
                cout << *rowlink->data << ",";
                int cur = *rowlink->data;
                ncur = *rowlink->next->data;
                if (ncur == -2) ncur = -1;
                if (cur > 0 && (ncur == -1)) accum += cur;
                if (cur > 0 && ncur != -1) {
                    if (accum > 0) {
                        accum += cur;
                        durations->append (new int(accum));
                        accum = 0;
                    } else durations->append (new int(cur));
                }
            }
			if (ncur > 0) durations->append (new int(ncur));
			cout << ncur << endl;
			DLink<int>* durs = durations->first ();
			for (; durs != NULL; durs = durs->next) {
			  cout << *durs->data << " ";
			}
			cout << endl;
    
			rowlink = durations->first ();
            int a = *rowlink->data;
			float cplx = 0.f;
			for (; rowlink->next != NULL; rowlink = rowlink->next) {
                int b = *rowlink->next->data;
                Ratio r(a,b);
                r.AutoReduce ();
                cout << r.Indig_ab() << ",";
                a = b;
                cplx += r.Indig_ab();
            }
            cout << endl << "Av. Local Complexity = " << (cplx/float(fn)) << endl;
			durations->destroy ();
			cout << "-----------------------" << endl;
		}
	}

	DList<Ratio>* rlist = new DList<Ratio>;
	DList<Ratio>* patlist = new DList<Ratio>;
	DLink<string>* clink = cmatrix->first ();
	DLink<string>* shlink = shorthand_matrix->first ();
    int filecount = 0;
    
    for (; clink!= NULL; clink = clink->next, shlink = shlink->next, filecount++) {
        // output to text files
        ofstream fptrt;
        string textsfile = "phrase_iBWT_" + to_string(filecount) + ".txt";
        fptrt.open (textsfile.c_str(), ios_base::out);
        if (!fptrt)
            cerr << "cannot write file: " << textsfile << endl;

        
        //output of lilypond file
        ofstream fptr;
        string lilyfile = "phrase_iBWT_" + to_string(filecount) + ".ly";
        fptr.open(lilyfile.c_str(), ios_base::out );
        if( !fptr )
            cerr << "cannot write file: " << lilyfile << endl;
        fptr << "\\version \"2.18.2\"" << endl;
        WriteToLilyfile (fptr, *shlink->data, true, false, false);
        
	  cout << "shorthand " << *shlink->data << endl;
	  string cur = *clink->data;
	  cout << "cmatrix " << cur << endl;
	  int count = 0;
	  for (string::iterator it=cur.begin(); it!=cur.end(); ++it) {
          char test = *it;
	      if (test == '1') {
              if (count > 0) {
                  durations->append(new int(count));
                  count = 1;
              }
              else count++;
          }
          else count++;
	  }
        
	  durations->append(new int(count));
	  DLink<int>* durs = durations->first ();
	  for (; durs != NULL; durs = durs->next) {
	    cout << *durs->data << " ";
	  }
	  cout << endl;
	  durations->destroy ();

        cout << "BWT of input" << endl;
        Christoffel c;
        c.SetWord (cur);
        c.SetMinMaxBeatCount (minbeat, maxbeat);
        c.display_all ();
        vector<string> shorthand = c.GetShorthand ();
        vector<string> sh2;
        //remove duplicates:
        while (!shorthand.empty ()) {
            string temp = shorthand.back();
            shorthand.pop_back ();
            shorthand.erase (remove (shorthand.begin (), shorthand.end (), temp), shorthand.end ());
            sh2.push_back (temp);
        }
        reverse (sh2.begin (), sh2.end ());
        int slen = sh2.size ();

        for (int i = 0; i < slen; i++) {
            string sh_string = sh2[i];
            WriteToLilyfile (fptr, sh_string, false, false, false);
            fptrt << sh_string << endl;
        }
        cout << endl;
        WriteToLilyfile (fptr, " ", false, true, false);
        fptr.close ();

        int n = int(cur.length());
		CreateFareyPulses (n, rlist);
		FilterFareyPulsesWithBinary (rlist, patlist, cur);
		DLink<Ratio>* rl = patlist->first ();
		for (; rl != NULL; rl = rl->next) {
			cout << (rl->data->GetP()) << "/" <<  (rl->data->GetQ()) << " ";
		}
		cout << endl;
		// output each onset and associated rhythmic impact value (syncopation amount)
		rl = patlist->first ();
		for (; rl != NULL; rl = rl->next) {
		  cout << rl->data->Indig_ab () << ", ";
        }
		cout << endl;
#if 0
        cout << "Christoffel Words:" << endl;
        rl = patlist->first ();
        for (; rl != NULL; rl = rl->next) {
            Christoffel c;
            c.SetWord (rl->data->Christoffel (true));
            c.display_all ();
        }
        cout << endl;
#endif        
		float ac = 0.f;
		rl = patlist->first ();
		float patlen = patlist->GetSize ();
		
#if 1
		for (; rl != NULL; rl = rl->next) {
			ac += rl->data->Indig_ab ();
		}
#endif
#if 0
		for (; rl != NULL; rl = rl->next) {
			cout << (rl->data->Harmon_ab ()) << " ";
			ac += rl->data->Harmon_ab ();
		}
#endif
		
		cout << endl << "n: " << n << " num beats: " << patlen << " density: " << (patlen/n) << " abs. impact: " << ac << " rel. impact: " << (ac/patlen);
		cout << endl << "====================================================================" << endl;
		rlist->destroy ();
		patlist->destroy ();
	}
    
	smatrix->destroy ();
	delete smatrix;
	imatrix->destroy ();
	delete imatrix;
	cmatrix->destroy ();
	delete cmatrix;
	rlist->destroy ();
	delete rlist;
	durations->destroy ();
	delete durations;
	patlist->destroy ();
	delete patlist;
	shorthand_matrix->destroy ();
	delete shorthand_matrix;
}



void Modul::PrintPhrases (string filename, string pitches) {
    
    ifstream file (filename.c_str());
    string line;
    string cell;
    
    DList<DList<string> >* smatrix;
    DList<DList<int> >* imatrix;
    DList<string>* cmatrix;
    DList<string>* srow;
    DList<int>* irow;
    
    DList<string>* shorthand_matrix;
    
    smatrix = new DList<DList<string> >;
    imatrix = new DList<DList<int> >;
    cmatrix = new DList<string>;
    
    shorthand_matrix = new DList<string>;
    
    //output of csound score file
    ofstream fptr2;
    string orcfile = "print_phrase.sco";
    fptr2.open (orcfile.c_str(), ios_base::out );
    if (!fptr2)
        cerr << "cannot write file: " << orcfile << endl;
    float onset = 0.f;
    //float onset_sentence = 0.f; float onset_phrase = 0.f;
    float period = .22f;

    while (file) {
        getline (file,line);
        stringstream lineStream (line);
        srow = new DList<string>;
        while (getline( lineStream, cell, '\t')) {
            srow->append(new string(cell.c_str()));
        }
        if( srow->GetSize() ) {
            smatrix->append (srow);
        } else {
            srow->destroy ();
            delete srow;
        }
    }
    
    Decoder* dec = new Decoder;
    
    //dec->printmap ();
    
    DLink<DList<string> >* slink = smatrix->first ();
    
    for (; slink!= NULL; slink = slink->next) {
        int fn = slink->data->GetSize ();
        if (fn > 0) {
            DLink<string>* rowlink = slink->data->first ();
            string test;
            string shstring;
            string temp = "";
            if (atoi(rowlink->data->c_str()) == 0) {
                if (rowlink->data->find ("$") == string::npos) {
                    irow = new DList<int>;
                    for (; rowlink != NULL; rowlink	= rowlink->next) {
                        string cur = *rowlink->data;
                        test += cur;
                        shstring += (cur + " ");
                        if (atoi(cur.c_str()) == 0) {
                            for ( string::iterator it=cur.begin(); it!=cur.end(); ++it) {
                                if (char(*it) != ' ') { //ignore empty spaces
                                    cout << *it;
                                    int code = dec->decode_shorthand_length (int(*it));
                                    irow->append (new int(code));
                                    temp += dec->decode_shorthand_symbol (int(*it));
                                }
                            }
                            cout << " | ";
                        }
                    }
                    imatrix->append (irow);
                    shorthand_matrix->append(new string(shstring));
                    cmatrix->append (new string(temp));
                }
            }
        }
    }
    
    cout << endl;
    
    DList<int>* durations = new DList<int>;

    mel_matrix.erase (mel_matrix.begin (), mel_matrix.end ());
    // for loading melody lines  in midi pitch format, can be float for micro-tuning
    LoadMelodyFromFile(pitches, mel_matrix);
    
    for (int i=0; i < int (mel_matrix.size()); i++) {
        for (int j=0; j < int (mel_matrix.at(i).size()); j++) {
            cout << mel_matrix.at(i).at(j) << " ";
        }
        cout << endl;
    }

    DList<Ratio>* rlist = new DList<Ratio>;
    DList<Ratio>* patlist = new DList<Ratio>;
    DLink<string>* clink = cmatrix->first ();
    DLink<string>* shlink = shorthand_matrix->first ();
    int linecount = 0;
    ofstream fptr;
    string lilyfile = "print_phrase.ly";
    fptr.open(lilyfile.c_str(), ios_base::out );
    if( !fptr )
        cerr << "cannot write file: " << lilyfile << endl;
    fptr << "\\version \"2.18.2\"" << endl;
    WriteToLilyfile (fptr, " ", true, false, false);
   
    for (; clink!= NULL; clink = clink->next, shlink = shlink->next, linecount++) {
        if (linecount > (mel_matrix.size()-1)) linecount = 0;
        SetPitchLine (linecount);
        
        //output of lilypond file
        WriteToLilyfile (fptr, *shlink->data, false, false, false);
        
        //output to csound orc
        WriteToCsoundScore2 (fptr2, *shlink->data, &onset, period);
        
        //cout << "shorthand " << *shlink->data << endl;
        string cur = *clink->data;
        //cout << "cmatrix " << cur << endl;
        int count = 0;
        for (string::iterator it=cur.begin(); it!=cur.end(); ++it) {
            char test = *it;
            if (test == '1') {
                if (count > 0) {
                    durations->append(new int(count));
                    count = 1;
                }
                else {
                    count++;
                }
            }
            else {
                count++;
            }
        }
        durations->append(new int(count));
        
        durations->destroy ();
        rlist->destroy ();
        patlist->destroy ();
    }
    WriteToLilyfile (fptr, " ", false, true, false);
    
    smatrix->destroy ();
    delete smatrix;
    imatrix->destroy ();
    delete imatrix;
    cmatrix->destroy ();
    delete cmatrix;
    rlist->destroy ();
    delete rlist;
    durations->destroy ();
    delete durations;
    patlist->destroy ();
    delete patlist;
    shorthand_matrix->destroy ();
    delete shorthand_matrix;
}

void Modul::CreateFareyPulses (int n, DList<Ratio>* rlist) {
		
	Ratio r(0,1);
	
	double step = 1./n;
	double cur = 0.f;
	while (cur <= 1.2) {
		double2frac (cur, &r);
		//cout << (r.GetP()) << "/" << (r.GetQ()) << " ";
		rlist->append (new Ratio (r.GetP(), r.GetQ()));
		cur += step;
		if (r.GetP() == 1 && r.GetQ() == 1) {
			break;
		}
	}
		
	cout << endl;
}

void Modul::FilterFareyPulsesWithBinary (DList<Ratio>* rlist, DList<Ratio>* patlist, string pattern) {
	
	DLink<Ratio>* rl = rlist->first ();
	
	//cout << "pattern = " << pattern.length() << " pulses " << rlist->GetSize () << " " << rl << endl;
	
	for (string::iterator it=pattern.begin(); it!=pattern.end() && rl != NULL; ++it, rl = rl->next)
	{
		char c = *it;
		//cout << c << " " << rl << endl;
		if (c == '1') {
			patlist->append (new Ratio (rl->data->GetP(), rl->data->GetQ()));
		}
	}
	
}


void Modul::PrintFareySeq (int n) {
    
    Farey a;
    
    a.CreateFareySeq (n);
    
    DLink<Ratio>* l;
    l = a.GetFirst ();
    for ( ; l != NULL; l = l->next) {
        string c1 = l->data->Christoffel (true);
        int length = l->data->GetP() + l->data->GetQ();
        cout << length << "\t : " << l->data->GetP() << "/" << l->data->GetQ() << "\t : " << c1 << endl;
        Christoffel c;
        c.SetWord (c1);
        c.display_all ();
        c.word_to_rhythm_chunks3 (c1);
    }
    
}

void Modul::CompareCRhythms (int m, int n, int m2, int n2) {
  //this->Cbaum (m, n);
  //cout << "---------------------------" << endl;
  Ratio r;
  r.SetP(m);
  r.SetQ(n);
  string cs = r.Christoffel (true);
  cout << "length: " << (m+n) << ", slope: " << m << "/" << n << ", Christoffel word #1: " << cs << endl;
  
  r.SetP(m2);
  r.SetQ(n2);
  string cs2 = r.Christoffel (true);
  cout << "length: " << (m2+n2) << ", slope: " << m2 << "/" << n2 << ", Christoffel word #2: " << cs2 << endl;


  Christoffel c;
  c.SetWord (cs);

  Christoffel c2;
  c2.SetWord (cs2);

  int len = c.length_word ();
  int len2 = c2.length_word ();
  int limit = 0;

  if (len < len2)
    limit = len;
  else
    limit = len2;

  int i = limit - 1;
  
  c.burrows_wheeler_trans ();
  c2.burrows_wheeler_trans ();
  int c_num_elem = 0;
  int c2_num_elem = 0;
  int intersection_elem = 0;

  // while loop:

  while (i-- > 0) {
    string b1 = c.display_all2 (limit - i);
    string b2 = c2.display_all2 (limit - i);
    cout << b1 << endl << b2 << endl << "------------" << endl;
    stringstream ss(b1);
    vector<string> r1;
    while (ss.good()) {
      string substr;
      getline (ss, substr, ',');
      r1.push_back (substr);
    }
    stringstream ss2(b2);
    vector<string> r2;
    while (ss2.good()) {
      string substr;
      getline (ss2, substr, ',');
      r2.push_back (substr);
    }

    //remove duplicates:                                                                                                                              
    for(size_t i = 0; i < r1.size (); i++) {
      for(size_t j = 0; j < r1.size(); j++) {
	if(r1[i] == r1[j] && i != j) {
	  r1.erase(r1.begin()+j);
	  j--;
	}
      }
    }

    // remove empty strings:

    for(size_t i = 0; i < r1.size (); i++) {
      if (r1[i] == "") {
	r1.erase(r1.begin()+i);
	i--;
      }
    }
    for(size_t i = 0; i < r1.size (); i++) {
      cout << r1[i] << " ";
    }
    cout << endl << "===" << endl;

    for(size_t i = 0; i < r2.size (); i++) {
      for(size_t j = 0; j < r2.size(); j++) {
	if(r2[i] == r2[j] && i != j) {
	  r2.erase(r2.begin()+j);
	  j--;
	}
      }
    }
    
    for(size_t i = 0; i < r2.size (); i++) {
      if (r1[i] == "") {
        r2.erase(r2.begin()+i);
	i--;
      } 
    }
    for(size_t i = 0; i < r2.size (); i++) {
      cout << r2[i] << " ";
    }
    cout << endl << "===" << endl;

    cout << (r1.size ()) << " " << (r2.size()) << endl << "------------" << endl;
    c_num_elem += r1.size ();
    c2_num_elem += r2.size ();

    // intersection:
    
    vector<string> r3;
    //sort(v1.begin(), v1.end());
    //sort(v2.begin(), v2.end());
    set_intersection(r1.begin(),r1.end(),r2.begin(),r2.end(),back_inserter(r3)); 

    cout << "intersection: " << endl;
    for(int i = 0; i < r3.size(); i++)
      cout << r3[i] << " ";

    cout << endl << "-----------------" << endl;
    intersection_elem += r3.size();

    /*

      compare strings with encoded metric groupings (e.g. string('ababb')
      apply metric grouping with highest match number (or random from multiple possibilities with equal match number)
      find shorthand symbol that match metric grouping

     */

  }

  cout << "There are " << c_num_elem << " unique elements in C(" << m << "/" << n << ") from sub-string size 2 to " <<  limit << endl;
  float c_perc = float(c_num_elem) / (float(limit - 1) * float(m+n));
  cout << (c_perc * 100.f) << " \%" << endl;
  cout << "There are " << c2_num_elem << " unique elements in C(" << m2 << "/" << n2 << ") from sub-string size 2 to " <<  limit << endl;
  float c2_perc = float(c2_num_elem) / (float(limit - 1) * float(m2+n2));
  cout << (c2_perc * 100.f) << " \%" << endl;
  cout << "There are " << intersection_elem << " common elements." << endl;
  c_perc = float(intersection_elem) / (float(limit - 1) * float(m+n));
  cout << (c_perc * 100.f) << " \% of C(" << m << "/" << n << ") from sub-string size 2 to " <<  limit << endl;
  c2_perc = float(intersection_elem) / (float(limit - 1) * float(m2+n2));
  cout << (c2_perc * 100.f) << " \% of C(" << m2 << "/" << n2 << ") from sub-string size 2 to " <<  limit << endl;

  cout << "Ratio of the number of common elements over the unique elements in C(" << m << "/" << n << "): " << (float(intersection_elem)/float(c_num_elem)) << endl;
  cout << "Ratio of the number of common elements over the unique elements in C(" << m2 << "/" << n2 << "): " << (float(intersection_elem)/float(c2_num_elem)) << endl;

}


float Modul::CompareStrings (string& s1, string& s2) {

  /* compare strings with encoded metric groupings (e.g. string('ababb')                                                                                                    apply metric grouping with highest match number (or random from multiple possibilities with equal match number)                                                            find shorthand symbol that match metric grouping */

  int len1 = s1.length();
  int len2 = s2.length();

  if (len1 != len2)
    return 0.f;

  int count = 0;
  for (string::iterator it=s1.begin(); it!=s1.end(); ++it) {
    for (string::iterator it2=s2.begin(); it2!=s2.end(); ++it2) {
      if (*it == *it2)
	count++;
    }
  }
  return (float(count)/float(len1));

}

vector<int> Modul::LookupGrouping (string& in) {
  //input is a word over alphabet {a,b} from BWT/iBWT analysis.
  //returns a vector of 2s and 3s according to the match with a specific
  //metric grouping encoded as words over alphabet {a,b}, see m_group5, etc
  //idea is to transcribe using chunks of metric grouping 2 or 3
  vector<int> result;
  int len = in.length();
  float max = 0.f;
  string group;
  switch (len) {
  case 2:
    result.push_back(2);
    break;
  case 3:
    result.push_back(3);
    break;
  case 4:
    result.push_back(2);
    result.push_back(2);
    break;
  case 5:
    group = m_group5[0];
    for (vector<string>::iterator it = m_group5.begin() ; it != m_group5.end(); ++it) {
      float perc = CompareStrings (in, *it);
      if (perc > max) {
        max = perc;
        group = *it;
      }
    }
    if (group == "ababb") {
      result.push_back(2);
      result.push_back(3);
    }
    if (group == "abbab") {
      result.push_back(3);
      result.push_back(2);
    }
    break;
  case 6:
    group = m_group6[0];
    for (vector<string>::iterator it = m_group6.begin() ; it != m_group6.end(); ++it) {
      float perc = CompareStrings (in, *it);
      if (perc > max) {
        max = perc;
        group = *it;
      }
    }
    if (group == "abbabb") {
      result.push_back(3);
      result.push_back(3);
    }
    if (group == "ababab") {
      result.push_back(2);
      result.push_back(2);
      result.push_back(2);
    }
    break;
  case 7:
    group = m_group7[0];
    for (vector<string>::iterator it = m_group7.begin() ; it != m_group7.end(); ++it) {
      float perc = CompareStrings (in, *it);
      if (perc > max) {
        max = perc;
        group = *it;
      }
    }
    if (group == "abbabab") {
      result.push_back(3);
      result.push_back(2);
      result.push_back(2);
    }
    if (group == "ababbab") {
      result.push_back(2);
      result.push_back(3);
      result.push_back(2);
    }
    if (group == "abababb") {
      result.push_back(2);
      result.push_back(2);
      result.push_back(3);
    }
    break;
  case 8:
    group = m_group8[0];
    for (vector<string>::iterator it = m_group8.begin() ; it != m_group8.end(); ++it) {
      float perc = CompareStrings (in, *it);
      if (perc > max) {
        max = perc;
        group = *it;
      }
    }
    if (group == "abababab") {
      result.push_back(2);
      result.push_back(2);
      result.push_back(2);
      result.push_back(2);
    }
    if (group == "abbabbab") {
      result.push_back(3);
      result.push_back(3);
      result.push_back(2);
    }
    if (group == "abbababb") {
      result.push_back(3);
      result.push_back(2);
      result.push_back(3);
    }
    if (group == "ababbabb") {
      result.push_back(2);
      result.push_back(3);
      result.push_back(3);
    }
    break;
  case 9:
    group = m_group9[0];
    for (vector<string>::iterator it = m_group9.begin() ; it != m_group9.end(); ++it) {
      float perc = CompareStrings (in, *it);
      if (perc > max) {
        max = perc;
        group = *it;
      }
    }
    if (group == "abbabbabb") {
      result.push_back(3);
      result.push_back(3);
      result.push_back(3);
    }
    if (group == "abbababab") {
      result.push_back(3);
      result.push_back(2);
      result.push_back(2);
      result.push_back(2);
    }
    if (group == "ababbabab") {
      result.push_back(2);
      result.push_back(3);
      result.push_back(2);
      result.push_back(2);
    }
    if (group == "abababbab") {
      result.push_back(2);
      result.push_back(2);
      result.push_back(3);
      result.push_back(2);
    }
    if (group == "ababababb") {
      result.push_back(2);
      result.push_back(2);
      result.push_back(2);
      result.push_back(3);
    }
    break;
  default:
    break;
  }

  return result;
}

int Modul::LoadMelodyFromFile (string filename, vector<vector<string> >& matrix) {
    ifstream file (filename.c_str());
    if (!file.is_open()) {
        cout << "error opening file: " << filename << endl; return 0;
    }
    vector<string> row;
    string line;
    string cell;

    while (file) {
        getline (file,line);
        stringstream lineStream (line);
        row.clear();
    
    while (getline(lineStream, cell, ',' ))
        row.push_back (cell);
    
    if (!row.empty ())
        matrix.push_back (row);
    }
    return 1;
}

void Modul::CRhythm (int m, int n) {
	
    // output shorthand strings to text file
    ofstream fptrt;
    string textsfile = "crhythm_" + to_string(m) + "_" + to_string(n) + ".txt";
    fptrt.open (textsfile.c_str(), ios_base::out);
    if (!fptrt)
        cerr << "cannot write file: " << textsfile << endl;

    this->Cbaum (m, n);
    cout << "---------------------------" << endl;
	Ratio r; 
	r.SetP(m);
	r.SetQ(n);
	string cs = r.Christoffel (true);
	cout << "length: " << (m+n) << ", slope: " << m << "/" << n << ", Christoffel word: " << cs << endl;
	Christoffel c;
	c.SetWord (cs);
	c.display_all ();
	string complet = c.word_to_rhythm_chunks3 (cs);
    vector<string> shorthand = c.GetShorthand ();
    vector<string> sh2;
    //remove duplicates:
    while (!shorthand.empty ()) {
        string temp = shorthand.back();
        shorthand.pop_back ();
        shorthand.erase (remove (shorthand.begin (), shorthand.end (), temp), shorthand.end ());
        sh2.push_back (temp);
    }
    sh2.push_back (complet);
    reverse (sh2.begin (), sh2.end ());
    int slen = sh2.size ();
    
    for (int i = 0; i < slen; i++) {
        string sh_string = sh2[i];
        fptrt << sh_string << endl;
    }
}


void Modul::LookupRhythm (string s) {
    
    Decoder* dec = new Decoder;
//	string s = "I-II";
	cout << "Shorthand pattern to analyse: ";
//	getline(cin, s);

    cout << s << endl;

    string temp = "";
    
    if (atoi(s.c_str()) == 0) {
        
      //   int length = 0;
        for ( string::iterator it=s.begin(); it!=s.end(); ++it)
        {
            if (char(*it) != ' ') { //ignore empty spaces
                temp += dec->decode_shorthand_symbol (int(*it));
		//cout << dec->decode_shorthand_symbol (int(*it)) << endl;
		//cout << "temp: " << temp << endl;
	    }
        }
        cout << endl;
        
        cout << temp << " " << temp.length () << endl;
    }
    
    cout << "[" << temp.length () << " ";

    for (string::iterator it=temp.begin(); it!=temp.end(); ++it)
    {
      cout << (char(*it)) << ", ";

    }
    cout << "]" << endl;

    int m,n = 1;
    int e = 50;
    
    int once = 1;
    int count_contain = 0;
    for (m = 1; m < e; m++) {
        for (n = 1; n < e; n++) {
            Ratio r;
            r.SetP(m);
            r.SetQ(n);
            string cs = r.Christoffel (true);
            Christoffel* c = new Christoffel ();
            c->SetWord (cs);
            string w = "";
            ostringstream ss;
            DLink<int>* l = c->GetBin1 ();
            for (; l != NULL; l = l->next) {
                ss << (*l->data);
            }
            w = ss.str ();
			//cout << m << "," << n << ": " << w << endl;
            if (w.compare (temp) == 0) {
                cout << temp << " is C(" << m << "," << n << ")" << endl;
            }
			
			ostringstream rs;
			for (string::reverse_iterator rit=w.rbegin(); rit!=w.rend(); ++rit)
				rs << *rit;
			w = rs.str ();
            if (w.compare (temp) == 0) {
                cout << temp << " is reverse-C(" << m << "," << n << ")" << endl;
            }
			
			stringstream ss2;
			l = c->GetBin2 ();
            for (; l != NULL; l = l->next) {
                ss2 << (*l->data);
            }
            w = ss2.str ();
            //cout << m << "," << n << ": " << w << endl;
            if (w.compare (temp) == 0) {
                cout << temp << " is NOT-C(" << m << "," << n << ")" << endl;
            }
			
			ostringstream rs2;
			for (string::reverse_iterator rit=w.rbegin(); rit!=w.rend(); ++rit)
				rs2 << *rit;
			w = rs2.str ();
            if (w.compare (temp) == 0) {
                cout << temp << " is reverse-NOT-C(" << m << "," << n << ")" << endl;
            }
			
			stringstream ss3;
			l = c->GetBin3 ();
            for (; l != NULL; l = l->next) {
                ss3 << (*l->data);
            }
            w = ss3.str ();
            //cout << m << "," << n << ": " << w << endl;
            if (w.compare (temp) == 0) {
                cout << temp << " is modC-OR-NOT-C(" << m << "," << n << ")" << endl;
            }
			
			ostringstream rs3;
			for (string::reverse_iterator rit=w.rbegin(); rit!=w.rend(); ++rit)
				rs3 << *rit;
			w = rs3.str ();
            if (w.compare (temp) == 0) {
                cout << temp << " is reverse-modC-OR-NOT-C(" << m << "," << n << ")" << endl;
            }
			
			stringstream ss4;
			l = c->GetBin4 ();
            for (; l != NULL; l = l->next) {
                ss4 << (*l->data);
            }
            w = ss4.str ();
            //cout << m << "," << n << ": " << w << endl;
            if (w.compare (temp) == 0) {
                cout << temp << " is NOT-modC-OR-NOT-C(" << m << "," << n << ")" << endl;
            }
			
			ostringstream rs4;
			for (string::reverse_iterator rit=w.rbegin(); rit!=w.rend(); ++rit)
				rs4 << *rit;
			w = rs4.str ();
            if (w.compare (temp) == 0) {
                cout << temp << " is reverse-NOT-modC-OR-NOT-C(" << m << "," << n << ")" << endl;
            }
            
            if (1) {
                once = 0;
                c->burrows_wheeler_trans2 ();
                int len = ss.str ().length ();
                int i = 1;
                for (; i <= len; i++) {
                    string res = c->burrows_wheeler_inverse2 (i);
                    
                    istringstream bwt(res);
                    string buf;
                    int pos = 1;
                    while(std::getline(bwt, buf, ',')) {
                        //cout << buf << '\n';
                        string::iterator it=buf.begin();
                        string ab_string = "";
                        for (; it!=buf.end(); ++it) {
                            if (char(*it) == 'a') {
                                ab_string = ab_string + "1";
                            }
                            if (char(*it) == 'b') {
                                ab_string = ab_string + "0";
                            }
                            
                        }
                        if (ab_string.compare (temp) == 0) {
                            cout << temp << " is at pos. #" << pos << " in iBWT block #" << i << " of C(" << m << "," << n << ")" << endl;
			    
                            if (++count_contain > 12) {
                                delete c;
                                goto stop1;
                            }
                        }
                        pos++;
                        
                    }
                
                    //cout << "====================== " << m << "/" << n <<  endl;
                    
                    bwt.clear();
                    bwt.str(string ());

                }
            }
			
			
            delete c;
        }
    }
    
stop1:

/*
 
 relationships:
 
 1. container
 1.1 word is contained in other words
 1.1.1 word is a C word or one of its bit transforms
 1.2 word contains itself other words
 
 2. Christoffel (C) word
 2.1 word is a (pseudo-)C word
 2.2 word is a (pseudo-)C word conjugate
 2.2.1 string position in lexicographic order of set of conjugates
 
 3.1 word is one of the stings of the iBWT  of a C word
 3.1.1 string length
 3.1.2 string position in lexicographic order
 
 */
    
    delete dec;
//    delete c;
    
}

void Modul::Cbaum (int p, int q) {
    
    int greater_one = 0;
    
    if (p > q) {
        greater_one = 1;
        int temp = p;
        p = q;
        q = temp;
    }
    Ratio* r = new Ratio (p, q);
    DList<Ratio>* l = new DList<Ratio>;
    r->GetNeighbours (l, greater_one);
    DLink<Ratio>* rl = l->first ();
    for (; rl != NULL; rl = rl->next) {
        if (!(rl->data->GetP()==1 && rl->data->GetQ() == 1) && !(rl->data->GetP()==0 && rl->data->GetQ() == 1))
            rl->data->GetNeighbours(l, greater_one);
    }
    
//    SternBrocot*sb = new SternBrocot ();
//    sb->CreateSternBrocotSeq (q);
//    sb->PrintSternBrocotSeq ();

}

void Modul::notenames2asciinames (string notes) {
    Decoder dec;
    dec.notenames2asciinames (notes);
}





///////////////////////////////////////////
// Interpret.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __Interpret_h__
#include "Interpret.h"
#endif

#include <stdint.h>
#include <sqlite3.h>

#include <dirent.h>
#include <errno.h>

#include "AlgoComp.h"

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

Interpret::Interpret()
{
	i = k = w = wk = wc = we = wl = ck = 0;
	int loop = 0;
	int loop2 = 0;
	while( loop < MAXLINES )
		{
		loop2 = 0;
		while( loop2 < MAXZEILEN )
			{
			args_obj[loop].text[loop2] = '\0';
			loop2++;
			}
		loop++;
		}
	prompt = "chunking";
    add_flag = 0;
    user_session = "";
    
    
    DetermineInstallDirectory ();
    cout << prompt << " v" << version_number << " shared material installed in: " << GetInstallDirectory () << endl;
    
    string rhydb_path = install_dir + "/rhy.db";
    db_err = sqlite3_open(rhydb_path.c_str(), &rhy);
    
    if (db_err) {
        fprintf (stderr, "Error opening database in Interpret ctor: %s\n", sqlite3_errmsg(rhy));
    }

    sqlite3_stmt *statement;
    string query = "SELECT name FROM session ORDER BY ID DESC LIMIT 1";
    if (sqlite3_prepare (rhy, query.c_str(), -1, &statement, 0) == SQLITE_OK) {
        if (sqlite3_step(statement) == SQLITE_ROW) {
            user_session = (char*)sqlite3_column_text(statement, 0);
            cout << "$ctor user_session: " << user_session << endl;
            add_flag = 1;
        } else {
            add_flag = 0;
            user_session = "";
        }
        
    } else {
        cout << "error in Interpret ctor database query of session." << endl;
    }
    sqlite3_finalize (statement);

 }

string Interpret::install_dir = "unknown path or incomplete installation (share files missing).";

string Interpret::version_number = "1.2.6";

Interpret::~Interpret()
{
    if (rhy) {
        db_err = sqlite3_close (rhy);
        if (db_err) {
            fprintf (stderr, "Error closing database in ~Interpret(): %s\n", sqlite3_errmsg(rhy));
        }
    }
}

int Interpret::DetermineInstallDirectory ()
{
    string default_dir = "/usr/local/share/chunking";
    string homebrew_dir = "/usr/local/Cellar/chunking";
    //install_dir = "unknown path or incomplete installation (share files missing).";
    int retcode = -1;
    
    DIR* dir = opendir(default_dir.c_str());
    if (dir) {
        install_dir = "/usr/local/share/chunking";
        return 0;
    } else if (ENOENT == errno) {
        dir = opendir(homebrew_dir.c_str());
        if (dir) {
            install_dir = "/usr/local/Cellar/chunking/" + version_number + "/share";
            return 1;
        }
        else if (ENOENT == errno) {
            cerr << "Warning! Installation directory not found." << endl;
        } else {
            cerr << "Warning! Problem locating installation directory." << endl;
        }
    } else {
        cerr << "Warning! Problem locating installation directory." << endl;
    }
    return retcode;
}


void Interpret::Dispatch(Modul& mdl)
{
    user_method = ms;
    
	if (ms == modulTable[kPropSeries])
	{
	    if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[2].text[0] != '\0' &&
            args_obj[3].text[0] == '\0')
	    {
            const char* c1 = args_obj[0].text;
            float f1 = atof (c1);
            const char* c2 = args_obj[1].text;
            float i1 = atof (c2);
            const char* c3 = args_obj[2].text;
            float f2 = atof (c3);
            proportion_series (f1, i1, f2);
        } else {
            cout << "Usage: chunking -m propseries <chunk to divide iteratively: float> <number of iterations: int> <divisor: float>" << endl;
        }
	}
	
	if (ms == modulTable[kPartition])
	{
	    if (args_obj[0].text[0] != '\0' &&
			args_obj[1].text[0] != '\0' &&
			args_obj[2].text[0] != '\0' &&
			args_obj[3].text[0] != '\0' &&
			args_obj[4].text[0] != '\0' &&
			args_obj[5].text[0] != '\0' &&
			args_obj[6].text[0] != '\0' &&
			args_obj[7].text[0] != '\0' &&
            args_obj[8].text[0] != '\0' &&
			args_obj[9].text[0] == '\0' )
	    {
			const char* c1 = args_obj[0].text;
			int i1 = atoi (c1);
			const char* c2 = args_obj[1].text;
			int i2 = atoi (c2);
			const char* c3 = args_obj[2].text;
			int i3 = atoi (c3);
			const char* c4 = args_obj[3].text;
			int i4 = atoi (c4);
			const char* c5 = args_obj[4].text;
			int i5 = atoi (c5);
			const char* c6 = args_obj[5].text;
			int i6 = atoi (c6);
			const char* c7 = args_obj[6].text;
			int i7 = atoi (c7);
			const char* c8 = args_obj[7].text;
			int i8 = atoi (c8);
			const char* c9 = args_obj[8].text;
            int i9 = atoi (c9);
			partition (i1, i2, i3, i4, i5, i6, i7, i8, i9);
        } else {
            cout << "Usage: chunking -m partition <n> <flag parts-must-be-prime> <flag parts-not-’1’>" << endl;
            cout << "<max prime in parts> <max int in parts>" << endl;
            cout << "<min int in parts>" << endl;
            cout << "<int to add to all parts>" << endl;
            cout << "<number of distinct parts, 0 := print all partitions>" << endl;
            cout << "<flag for p. with all parts being equal>" << endl;
            return;
        }
	}
	
	if (ms == modulTable[kanaphrases])
	{
		if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[2].text[0] != '\0' &&
            args_obj[4].text[0] == '\0')
	    {
			string s1 = args_obj[0].text;
            int i2 = atoi (args_obj[1].text);
            int i3 = atoi (args_obj[2].text);
            int i4 = 1; // default is to print the ibwt matrix to the shell
            if (args_obj[3].text[0] != '\0')
                i4 = atoi (args_obj[3].text);
			mdl.AnalysePhrases (s1, i2, i3, i4);
        } else if (args_obj[0].text[0] != '\0' &&
                   args_obj[1].text[0] == '\0')
        {
            string s1 = args_obj[0].text;
            int i2 = 1;
            int i3 = 1000;
            mdl.AnalysePhrases (s1, i2, i3, 1);
            
        } else {
            cout << "usage: chunking -m anaphrases <shorthand.txt>" << endl;
            cout << "or: chunking -m anaphrases <shorthand.txt> <min beats> <max beats>" << endl;
        }
	}
	
    if (ms == modulTable[kprintphrases])
    {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[4].text[0] == '\0')
        {
            string s1 = args_obj[0].text;
            string s2 = args_obj[1].text;
            float f1 = 90.f;
            if (args_obj[2].text[0] != '\0')
                f1 = atof(args_obj[2].text);
            int i1 = 1;
            if (args_obj[3].text[0] != '\0')
                i1 = atoi(args_obj[3].text);
            mdl.PrintPhrases (s1, s2, f1, i1);
        } else if (args_obj[0].text[0] != '\0' &&
                   args_obj[1].text[0] == '\0')
        {
            cout << "Usage: chunking -m printphrases <file1: shorthand notation> <file2: midi pitches> <int: bpm (optional)> <int: flag (optional)>" << endl;
        }
    }
    
	if (ms == modulTable[kintstrings])
	{
		if (args_obj[0].text[0] != '\0' &&
			args_obj[1].text[0] != '\0' &&
			args_obj[2].text[0] == '\0')
	    {
			string s1 = args_obj[0].text;
			string s2 = args_obj[1].text;
			
			mdl.AnalyseIntegerRhythmStrings (s1, s2);
        } else {
            cout << "Usage: chunking -m intstrings <file1> <file2>" << endl;
            cout << "Input: Two ascii text files with lines of comma-separated rhythms in integer distance notation." << endl;
            cout << "Output: various distance measurements between all pairs of rhythms be- tween file1 and file2" << endl;
        }
	}
	
	
	if (ms == modulTable[kfarey2binary])
	{
		if (args_obj[0].text[0] != '\0' &&
			args_obj[1].text[0] != '\0' &&
			args_obj[2].text[0] != '\0' &&
			args_obj[3].text[0] == '\0')
	    {
			char* c1 = args_obj[0].text;
			int i1 = atoi (c1);
			char* c2 = args_obj[1].text;
			int i2 = atoi (c2);
			char* c3 = args_obj[2].text;
			int i3 = atoi (c3);
			mdl.FareyToBinaryRhythm (i1, i2, i3);
		}
        else {
            cout << "Usage: chunking -m farey2binary <Farey Sequence n> <Digestibility threshold f> <int flag activates smooth filter 2 3>" << endl;
        }
	}
	
	if (ms == modulTable[kdivisors])
	{
        // lists all divisors of n in {1,2,3,...,499}
		mdl.Divisors ();
	}
	
	if (ms == modulTable[kpermutations])
	{
        // Outputs the Christoffel words and BWTs of ratios built by the first twenty-one 7-smooth numbers.
		mdl.Permutations ();
	}
	
	if (ms == modulTable[kpermutations2])
	{
		mdl.Permutations2 ();
	}
	
	if (ms == modulTable[kfpoly])
	{
		if (args_obj[0].text[0] != '\0' &&
			args_obj[1].text[0] != '\0' &&
			args_obj[2].text[0] != '\0' &&
			args_obj[3].text[0] == '\0')
	    {
			char* c1 = args_obj[0].text;
			int i1 = atoi (c1);
			char* c2 = args_obj[1].text;
			int i2 = atoi (c2);
			char* c3 = args_obj[2].text;
			int i3 = atoi (c3);
			mdl.FareyPolyrhythm (i1, i2, i3);
        } else {
            cout << "Usage: chunking -m fpoly <Farey Seq. N> <first subdivision> <second subdivision>" << endl;
        }
	}
    
    if (ms == modulTable[kprintfarey])
    {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] == '\0')
        {
            char* c1 = args_obj[0].text;
            int i1 = atoi (c1);
            mdl.PrintFareySeq (i1);
        }
        else {
            cout << "Usage: chunking -m printfarey <Farey Sequence n>" << endl;
            cout << "Prints all members of Farey Sequence n, " << endl;
            cout << "with each ratio also interpreted as slope of Christoffel word," << endl;
            cout << "including bit pattern operations, BWT, and shorthand notations." << endl;
        }
        
    }
	
	if (ms == modulTable[kcrhythm])
    {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[2].text[0] == '\0')
        {
            char* c1 = args_obj[0].text;
            int i1 = atoi (c1);
            char* c2 = args_obj[1].text;
            int i2 = atoi (c2);
            mdl.CRhythm (i1, i2);
        }
        else {
            cout << "Usage: chunking -m crhythm <m: integer> <n: integer>" << endl;
            cout << "Outputs a Christoffel word C(m,n), its ancestors in the Stern-Brocot tree, and various other transformations." << endl;
        }
        
    }

	if (ms == modulTable[kcrhythm2])
	  {
	    if (args_obj[0].text[0] != '\0' &&
		args_obj[1].text[0] != '\0' &&
		args_obj[2].text[0] != '\0' &&
		args_obj[3].text[0] != '\0' &&
		args_obj[4].text[0] == '\0')
	      {
		char* c1 = args_obj[0].text;
		int i1 = atoi (c1);
		char* c2 = args_obj[1].text;
		int i2 = atoi (c2);
		char* c3 = args_obj[2].text;
                int i3 = atoi (c3);
                char* c4 = args_obj[3].text;
                int i4 = atoi (c4);

		mdl.CompareCRhythms (i1, i2, i3, i4);
          } else {
              cout << "Usage: chunking -m compc <m1: int> <n1: int> <m2: int> <n2: int>" << endl;
              cout << "Compares two Crhistoffel rhythms with each other to find intersections of their inverse Burrows-Wheeler matrix, i.e. comparing all of their possible cyclic substrings." << endl;
          }

	  }



	
	if (ms == modulTable[klookup])
    {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] == '\0')
        {
            string s1 = args_obj[0].text;
            
            mdl.LookupRhythm (s1);
        } else {
            cout << "Usage: chunking -m lookup <shorthand pattern>" << endl;
            cout << "Searches all Christoffel words C(m,n), from C(1,1) to C(20,20), for a matching rhythmic pattern" << endl;
        }
        
    }
	if (ms == modulTable[kloadpartition]) {
	  if (args_obj[0].text[0] != '\0' &&
	      args_obj[1].text[0] != '\0' &&
	      args_obj[2].text[0] == '\0') {
	  string s1 = args_obj[0].text;
	  char* c1 = args_obj[1].text;
	  int i1 = atoi (c1);
	  cout << s1 << " " << i1 << endl;
	  mdl.LoadPartitions (s1, i1);
	  }
	}

	if (ms == modulTable[kgetpartition]) {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[2].text[0] != '\0') {
            char* c1 = args_obj[0].text;
            int i1 = atoi (c1);
            char* c2 = args_obj[1].text;
            int i2 = atoi (c2);
            char* c3 = args_obj[2].text;
            int i3 = atoi (c3);
            mdl.GetPartition (i1, i2, i3);
        } else {
            cout << "Usage: chunking -m getpart <n: integer> <k: integer> <1>" << endl;
            cout << "returns the partition of n into k unique parts with the lowest standard deviation," << endl;
            cout << "with n <= 120 and k <= 5. The output format is: n part_1 part_2 ... part_k mean k" << endl;
        }
    }

	if (ms == modulTable[ksentence]) {
	      char* c1 = args_obj[0].text;
	      int i1 = atoi (c1);
	      char* c2 = args_obj[1].text;
	      int i2 = atoi (c2);
            //cout << i1 << " " << i2 << endl;
        if (i1 == 0 || i2 == 0) {
            cout << "Usage: chunking -m sentence n k" << endl;
            cout << "with n = number of pulses <= 120," << endl;
            cout << "and k = number of distinct parts <= 5" << endl;
        } else mdl.StartSentence (i1, i2);
    }
    
    if (ms == modulTable[kbwt]) {
      if (args_obj[0].text[0] != '\0') {
        string s1 = args_obj[0].text;
        mdl.BWT (s1);
      }
      else {
          cout << "Usage: chunking -m bwt <string>" << endl;
      }
    }

    if (ms == modulTable[kbwtmel]) {
      if (args_obj[2].text[0] != '\0') {
        string s1 = args_obj[0].text;
        char* c1 = args_obj[1].text;
        int i1 = atoi (c1);
        string s2 = args_obj[2].text;
        mdl.BWTmelodies (s1, i1, s2);
      }
      else {
          cout << "Usage: chunking -m bwtmel <string of ascii notes> <integer denoting semitones for transposition> <optional: character denoting a type of transformation (g (original),u (inversion),k (retrograde),q (retrograde of inversion)>" << endl;
          cout << "Example: chunking -m bwtmel 'c6ef' 0 g" << endl;
      }
    }
    
    if (ms == modulTable[knotenames]) {
      if (args_obj[0].text[0] != '\0') {
        string s1 = args_obj[0].text;
        mdl.notenames2asciinames (s1);
      }
      else {
        cout << "Usage: chunking -m notenames <string>" << endl;
        cout << "Returns: ascii code for pitches as one character per pitch, useful for Burrows-Wheeler." << endl;
        cout << "Returns also a list of MIDI note numbers." << endl;
        cout << "Example: chunking -m notenames 'C4 C#4 D4 D#4'" << endl;
        cout << "c6d7" << endl;
        cout << "60, 61, 62, 63" << endl;
      }

    }
    
    if (ms == modulTable[knotes2midi]) {
      if (args_obj[0].text[0] != '\0') {
        string s1 = args_obj[0].text;
        mdl.notenames2midinotes (s1);
      }
      else {
        cout << "Usage: chunking -m notes2midi <file name>" << endl;
        cout << "Input: Name of a text file containing lines of note names, for example:" << endl;
        cout << "C4 C4 G4 G4 A4 A4 G4" << endl;
        cout << "F4 F4 E4 E4 D4 D4 C4" << endl;
        cout << "Output: Lines of comma-separated Midi note numbers, for example:" << endl;
        cout << "60, 60, 67, 67, 69, 69, 67" << endl;
        cout << "65, 65, 64, 64, 62, 62, 60" << endl;
        cout << "After being saved as a file, the output can be used together with printphrases to merge the pitches with rhythmic phrases." << endl;
      }
    }
    
    if (ms == modulTable[kmidi2notes]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            mdl.midinotes2notenames (s1);
        }
        else {
            cout << "Usage: chunking -m midi2notes <file name>" << endl;
            cout << "Input: Name of a text file containing lines of comma-separated Midi note numbers, for example:" << endl;
            cout << "60, 60, 67, 67, 69, 69, 67" << endl;
            cout << "65, 65, 64, 64, 62, 62, 60" << endl;
            cout << "Output: Lines of note names, for example:" << endl;
            cout << "C4 C4 G4 G4 A4 A4 G4" << endl;
            cout << "F4 F4 E4 E4 D4 D4 C4" << endl;
            
        }
    }
    if (ms == modulTable[kbwtpath]) {
      if (args_obj[1].text[0] != '\0') {
        string s1 = args_obj[0].text;
        string s2 = args_obj[1].text;
        mdl.iBWTpathway (s1, s2);
      }
      else {
        cout << "Usage: chunking -m bwtpath <shorthand string> <file name>" << endl;
        cout << "Input: 1. A string of rhythm shorthand, for example:" << endl;
        cout << "'IXIIXIIIXX'" << endl;
        cout << "Internally, the algorithm converts the shorthand into a word over the alphabet {a,b}, " << endl;
        cout << "where 'a' represents a note onset, and 'b' represents inter-onset pulses" << endl;
        cout << "2. A file containing a random list of row numbers of the inverse Burrows Wheeler (iBWT) matrix." << endl;
        cout << "The iBWT matrix has as many rows as the word has characters." << endl;
        cout << "An example file of row numbers may contain: 14, 10, 7, 5, 3, 1." << endl;
      }
    }
    
    if (ms == modulTable[kbwtmatrix]) {
      if (args_obj[0].text[0] != '\0' &&
          args_obj[1].text[0] == '\0') {
        string s1 = args_obj[0].text;
        mdl.iBWTspecific (s1, 0, 0);
      }
      else if (args_obj[0].text[0] != '\0' &&
               args_obj[1].text[0] != '\0') {
          string s1 = args_obj[0].text;
          int i1 = atoi(args_obj[1].text);
          mdl.iBWTspecific (s1, i1, 0);
      }
    else{
        cout << "Usage: chunking -m bwtmatrix <shorthand string>" << endl;
        cout << "Usage: chunking -m bwtmatrix <shorthand string> <integer: length>" << endl;
      }
    }

    if (ms == modulTable[kdb]) {
      if (args_obj[0].text[0] != '\0') {
          string s1 = args_obj[0].text;
          cout << mdl.DB_search (s1) << endl;
      }
      else {
          cout << "Usage: chunking -m db <search string in shorthand notation>" << endl;
          cout << "The search string may contain '%' for extended search." << endl;
      }
    }
    
    if (ms == modulTable[kdb_insert]) {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[3].text[0] != '\0') {
            string s1 = args_obj[0].text;
            string s2 = args_obj[1].text;
            string s3 = args_obj[2].text;
            string s4 = args_obj[3].text;
            mdl.DB_insert_from_file (s1,s2,s3,s4);
        }
        else {
            cout << "Usage: chunking -m dbinsert <filename> <name> <origin> <composer>" << endl;
            cout << "File containing shorthand notation. One line creates new entry in the table rhythm of rhy.db." << endl;
        }
    }
    
    if (ms == modulTable[kextract]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            mdl.extract_from_analysephrases_output (s1);
        }
        else {
            cout << "Usage: chunking -m extract_local_comp <filename>" << endl;
        }
        
    }

    if (ms == modulTable[kshortening]) {
        if (args_obj[1].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            string result = mdl.Shortening (s1, i1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m shortening <shorthand string> <from_top? 0 (no) or 1 (yes)>" << endl;
        }
    }
    
    if (ms == modulTable[ksproc]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            mdl.ShorteningProcess (s1);
        }
        else {
            cout << "Usage: chunking -m sproc <shorthand string>" << endl;
        }
    }
    
    if (ms == modulTable[kjump]) {
        if (args_obj[3].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            int i2 = atoi (args_obj[2].text);
            int i3 = atoi (args_obj[3].text);
            string result = mdl.Jumping (s1, i1, i2, i3);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m jump <shorthand string> <n_symbols int> <k_times int> <from_start? 0 (no) or 1 (yes)>" << endl;
        }
    }
    
    if (ms == modulTable[kmutate]) {
        if (args_obj[1].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            string result = mdl.Mutation (s1, i1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m mutate <shorthand string> <k_times int>" << endl;
        }
    }
    
    if (ms == modulTable[kswap]) {
        if (args_obj[1].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            string result = mdl.Swap (s1, i1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m swap <shorthand string> <k_times int>" << endl;
        }
    }
    
    if (ms == modulTable[ksilence]) {
        if (args_obj[2].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            int i2 = atoi (args_obj[2].text);
            string result = mdl.Silence (s1, i1, i2);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m silence <shorthand string> <from_pos int> <to_pos int>" << endl;
        }
    }
    
    if (ms == modulTable[kproc2shapes]) {
        if (args_obj[1].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            string result = mdl.ProcessToShapes (s1, i1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m shape <shorthand string> <flag int>" << endl;
        }
    }
    
    if (ms == modulTable[kfragment]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            string result = mdl.Fragment (s1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m fragment <shorthand string>" << endl;
        }
    }
    
    if (ms == modulTable[krotate]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            string result = mdl.Rotation (s1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m rotate <shorthand string>" << endl;
        }
    }
    
    if (ms == modulTable[kfragrotate]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            string result = mdl.FragmentRotation (s1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m fragrotate <shorthand string>" << endl;
        }
    }
    
    if (ms == modulTable[kcompose]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            mdl.Compose (s1);
        }
        else {
            cout << "Usage: chunking -m compose <shorthand string>" << endl;
        }
    }
    
    if (ms == modulTable[kreverse]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            string result = mdl.Reverse (s1);
            if (add_flag)
                InsertIntoDB (result);
            cout << result << endl;
        }
        else {
            cout << "Usage: chunking -m reverse <shorthand string>" << endl;
        }
    }
    
    if (ms == modulTable[kaddrep]) {
        if (args_obj[2].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            int i2 = atoi (args_obj[2].text);
            mdl.AddAndRepeat (s1, i1, i2);
            
        }
        else {
            cout << "Usage: chunking -m addrep <shorthand string> <n int> <k int>" << endl;
        }
    }
    
    if (ms == modulTable[krepeat]) {
        if (args_obj[1].text[0] != '\0') {
            string s1 = args_obj[0].text;
            int i1 = atoi (args_obj[1].text);
            mdl.Repeat (s1, i1);
            
        }
        else {
            cout << "Usage: chunking -m repeat <shorthand string> <n int>" << endl;
        }
    }


    if (ms == modulTable[knest]) {
      if (args_obj[0].text[0] != '\0') {
	string s1 = args_obj[0].text;
	mdl.Nest (s1);
      }
    }

    if (ms == modulTable[kstartsession]) {
        if (args_obj[0].text[0] != '\0') {
            user_session = args_obj[0].text;
            /*adds a new session to rhy.db->sessions with user providing the name
             all string returning methods have their values
             appended to the rhythm table of rhy.db with the session name as name.
             */
            add_flag = 1;
            string sql = "INSERT INTO session VALUES (\"" + user_session + "\", NULL); ";
            char *err_msg = 0;
            cout << sql << endl;
            int rc = sqlite3_exec(rhy, sql.c_str(), 0, 0, &err_msg);
            if (rc != SQLITE_OK)
                cerr << "error " << err_msg << " in startsession when inserting name in session." << endl;

        }
        else {
            cout << "Usage: chunking -m startsession <session_name string>" << endl;
        }
    }
    
    if (ms == modulTable[kstopsession]) {
        add_flag = 0;
        sqlite3_stmt *statement;
        string user_session;
        string query = "SELECT name FROM session ORDER BY ID DESC LIMIT 1";
        if (sqlite3_prepare (rhy, query.c_str(), -1, &statement, 0) == SQLITE_OK) {
            if (sqlite3_step(statement) == SQLITE_ROW) {
                user_session = (char*)sqlite3_column_text(statement, 0);
                cout << "$kstopsession: " << user_session << endl;
            }
        }
        sqlite3_finalize (statement);
        
        string sql = "DELETE FROM session WHERE name = \"" + user_session + "\"";
        char *err_msg = 0;
        cout << sql << endl;
        int rc = sqlite3_exec(rhy, sql.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK)
            cerr << "error " << err_msg << " in kstopsession when deleting name in session." << endl;
        
        
    }
    
    if (ms == modulTable[ksession]) {
        cout << "Current session: " << user_session << endl;
    }
    
    if (ms == modulTable[klistsessions]) {
        
    }
    
    if (ms == modulTable[kprintsession]) {
        if (args_obj[0].text[0] != '\0') {
            string s1 = args_obj[0].text;
            PrintSession (s1);
        }
        else {
            cout << "Usage: chunking -m printsession <session_name string>" << endl;
        }
    }
    
    if (ms == modulTable[kbendf]) {
        if (args_obj[0].text[0] != '\0') {
            int i1 = atoi(args_obj[0].text);
            mdl.BendFarey (i1);
        }
        else {
            cout << "Usage: chunking -m bendf <farey_number int>" << endl;
        }
    }
    
    if (ms == modulTable[ktsnmr]) {
        if (args_obj[1].text[0] != '\0') {
            string s1 = args_obj[0].text;
            string s2 = args_obj[1].text;
            mdl.Translate_Shorthand (s1, s2);
        } else {
            cout << "Usage: chunking -m tsnmr <string snmr_file> <string pitch_file>" << endl;
        }
    }
    
	for (int i = 0; i < MAXLINES; i++)
		args_obj[i].text[0] = '\0';

}

void Interpret::InsertIntoDB (string rhythm) {
    if (!add_flag)
        return;
    string sql = "INSERT INTO rhythm VALUES (\"" + rhythm + "\", \"" + user_session + "\", \"" + user_method + "\" , \"user\", NULL); ";
    cout << sql << endl;
    char *err_msg = 0;
    int rc = sqlite3_exec(rhy, sql.c_str(), 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        cerr << "error " << err_msg << " when inserting into table rhythm. Called by InsertIntoDB (string rhythm)." << endl;
    }
}

void Interpret::PrintSession (string session_name) {
    
    sqlite3_stmt *statement;
    
    string sql = "PRAGMA case_sensitive_like = true";
    if (sqlite3_prepare (rhy, sql.c_str(), -1, &statement, 0) != SQLITE_OK) {
        cerr << "error when setting case_sensitive_like = true." << endl;
    }
    sqlite3_finalize (statement);
    
    sql = "SELECT pattern, name, origin, composer, ID FROM rhythm WHERE name LIKE '" + session_name + "'";
    int countrow = 0;
    if (sqlite3_prepare (rhy, sql.c_str(), -1, &statement, 0) == SQLITE_OK) {
        int res = 0;
        while (1) {
            res = sqlite3_step(statement);
            if (res == SQLITE_ROW) {
                countrow++;
                string rhythm = (char*)sqlite3_column_text(statement, 0);
                string name = (char*)sqlite3_column_text(statement, 1);
                string origin = (char*)sqlite3_column_text(statement, 2);
                string composer = (char*)sqlite3_column_text(statement, 3);
                int id = sqlite3_column_int(statement, 4);
                cout << "$ " << name << " " << origin << " " << composer << " ID: "<< id << " " << countrow << endl;
                cout << rhythm << endl;
            }
            if (res == SQLITE_DONE || res==SQLITE_ERROR) {
                break;
            }
        }
    }
    sqlite3_finalize (statement);
}

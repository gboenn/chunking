#ifndef __Interpret_h__
#include "Interpret.h"
#endif

#include <stdint.h>

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
	prompt = "SoundShell";
}

Interpret::~Interpret()
{
}

void Interpret::DoInterpret(TextIO& coms, Modul& mdl )
{
	ofstream textout;
	time_t now;
	struct tm *date;
	char *stamp;
	time( &now );
	
	char appendstring[11];
	sprintf(appendstring, "%ju", (uintmax_t)now);
	
	string bodyname = "logSSH";
	string logfilename =  bodyname + appendstring;
	coms.TextWrite( textout, logfilename);
	
	date = localtime( &now );
	stamp = asctime( date );
	textout << stamp << endl << endl;
	
	while( i < MAXLINES )
	{
		cout << prompt << ">";
		//isfptr.getline( (char *) &text_obj[count], sizeof(struct TextBuf), '\n' );
		
		cin.getline(zeile,sizeof(zeile),'\n');
		args[i] = (string)zeile;
		nchars = strlen(zeile); 
		
		if( args[i] == "exit" )
		{
			cout << "bye!" << endl;
			break;
		}
		
		/////////////////////////////////////
		//
		//	Zeilennummer, Zeileneingabe und Zeilenlaege:
		//  k: index des ersten zeichens der zeile
		//
		/////////////////////////////////////
	
		
		k = 0; 
		
		/////////////////////////////////////
		//
		// wenn man nur zeilenweise woerter speichen moechte,
		// w auf 0 und alte woerter durch null-string loeschen ( s.u.)
		//
		/////////////////////////////////////
		
		w = 0;
		//		int result = 0;
		
		if( args[i] != " " ) // wenn in der Zeile was steht,...
		{
			while( k < nchars ) // geh die ganze Zeile durch:
			{
				while( args[i][k] == ' '  ) // FOUND WHITESPACE
				{
					k++;
					if( k == ( nchars - 1 ) ) // zeilenende erreicht
						break;
					if( args[i][k] != ' ' ) // character gefunden?
						break;
				}
				
				while( args[i][k] != ' ' ) // found non-whitespace
				{
					wort[w][wk++] = args[i][k++]; // copy non-whitespaces to wort
					
					if( k == ( nchars ) ) // if there aren't any chars left 
					{
						++w;	// next word
						wk = 0; // reset char index for new word 
						break;
					}
					
					if( args[i][k] == ' ' ) // or if whitespace separates
					{
						++w;	// next word
						wk = 0; // reset char index for new word 
						break;
					}
				}
				
				if( k == ( nchars - 1 ) ) // if there aren't any chars left 
					break;
			}
			
			int result = 0;
			nullcount = 0;
			
			for( ck = 0; ck <= coms.GetCount (); ck++ )
			{	
				if( ck == coms.GetCount () )
				{
					we = 0;
					while( we < MAXWORTE )
					{
						wort[0][we++] = "\0";
					}
					we = 0;
					break;
				}
				
				while( we < MAXWORTE )
				{
					if( wort[0][we] == "\0" )
					{
						we = 0;
						break;
					}
					else
					{
						if( coms.GetTextBufChar (ck, we) != '\0' )
						{
							#if  1
							
							 	char ctemp1 = coms.GetTextBufChar (ck, we); //coms.text_obj[ck].text[we];
							 	char ctemp3 = *wort[0][we].c_str();
								
								if( ctemp1 == ctemp3 )
								{	
									result = 1;
									wl++;	
								}
								else
									result = 0;	
							
							#endif
							#if  _VISUAL
							{
								unsigned char ctemp1 = coms.GetTextBufChar (ck, we);
								unsigned char ctemp3 = unsigned char(*wort[0][we].c_str());
								
								if( ctemp1 == ctemp3 )
								{	
									result = 1;
									wl++;
								}
								else
									result = 0;
									
							}
							#endif
							#if  _GNU
							{
							 	char ctemp1 = coms.text_obj[ck].text[we];
							 	char ctemp3 = *wort[0][we].c_str();
								
								if( ctemp1 == ctemp3 )
								{	
									result = 1;
									wl++;
								}
								else
									result = 0;
									
							}
							#endif
							
							we++;
							
						}
						else
						{
							we = 0;
							result = 0;
							break;
						}
					}

				} // end while( we < MAXWORTE)...
				
				if( result )
				{
					if( wl == coms.GetTextBufLength (ck) )
					{	
						Dispatch(coms, mdl);
						textout << zeile << endl;
					}
					else
						nullcount++;
				}
				else
				{
					//cout << "command not found" << endl;
					nullcount++;
				}
				
				if( nullcount == coms.GetCount () )
					{
					const char* test = "\0";
					if( test[0] != zeile[0] )
						cout << "command not found" << endl;
				
					for( wc = 1; wc < w; wc++ )
						{
							we = 0;
							while( we < MAXWORTE )
							{	
								wort[wc][we] = "\0";
								we++;
							}
						}
					}

				wl = we = 0;

			} // end for( ck = 0; ck <= coms.count; ck++ )...
			
		} // end if( args[i] != " " )...
			
		++i;
		if( i >= MAXLINES )
			i = 0;
	}
}

void Interpret::Dispatch(TextIO& coms, Modul& mdl, int from_cmd_line)
{
	if (!from_cmd_line)
	{
		for( wc = 1; wc < w; wc++ )
		{
			we = 0;
			while( we < MAXWORTE )
			{	
				args_obj[wc-1].text[we] = char(*wort[wc][we].c_str());
				wort[wc][we++] = "\0";
			}
		}
		ms = coms.GetTextBufText (ck);
	}
        

	if (ms == modulTable[kPropSeries])
	{
	    if (args_obj[0].text[0] != '\0' ||
		args_obj[1].text[0] != '\0' ||
		args_obj[2].text[0] != '\0' ||
		args_obj[3].text[0] == '\0')
	    {
		const char* c1 = args_obj[0].text;
		float f1 = atof (c1);
		const char* c2 = args_obj[1].text;
		float i1 = atof (c2);
		const char* c3 = args_obj[2].text;
		float f2 = atof (c3);
		proportion_series (f1, i1, f2);
	    }
	}
	
	if (ms == modulTable[kPartition])
	{
	  if (args_obj[0].text[0] == '\0') {
	    cout << "partition n must-be-prime no-ones max prime max_int min_int int-to-add num-distinct-parts (0=all parts) [all-parts-equal]" << endl;
	    return;
	  }

	    if (args_obj[0].text[0] != '\0' ||
			args_obj[1].text[0] != '\0' ||
			args_obj[2].text[0] != '\0' ||
			args_obj[3].text[0] != '\0' ||
			args_obj[4].text[0] != '\0' ||
			args_obj[5].text[0] != '\0' ||
			args_obj[6].text[0] != '\0' ||
			args_obj[7].text[0] != '\0' ||
		        args_obj[8].text[0] != '\0' ||
			args_obj[9].text[0] != '\0' || 
		        args_obj[10].text[0] == '\0')
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
	    }
	}
	
	if (ms == modulTable[kanaphrases])
	{
		if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[2].text[0] != '\0' &&
            args_obj[3].text[0] == '\0')
	    {
			string s1 = args_obj[0].text;
            int i2 = atoi (args_obj[1].text);
            int i3 = atoi (args_obj[2].text);
            
			mdl.AnalysePhrases (s1, i2, i3);
        } else if (args_obj[0].text[0] != '\0' &&
                   args_obj[1].text[0] == '\0')
        {
            string s1 = args_obj[0].text;
            int i2 = 1;
            int i3 = 1000;
            mdl.AnalysePhrases (s1, i2, i3);
            
        } else {
            cerr << "usage: chunking -m anaphrases <shorthand.txt>" << endl;
            cerr << "or: chunking -m anaphrases <shorthand.txt> <min beats> <max beats>" << endl;
        }
	}
	
    if (ms == modulTable[kprintphrases])
    {
        if (args_obj[0].text[0] != '\0' &&
            args_obj[1].text[0] != '\0' &&
            args_obj[3].text[0] == '\0')
        {
            string s1 = args_obj[0].text;
            string s2 = args_obj[1].text;
            float f1 = 90.f;
            if (args_obj[2].text[0] != '\0')
                f1 = atof(args_obj[2].text);
            mdl.PrintPhrases (s1, s2, f1);
        } else if (args_obj[0].text[0] != '\0' &&
                   args_obj[1].text[0] == '\0')
        {
            cout << "error: please provide a valid text filename as the second argument." << endl;
        }
    }
    
	if (ms == modulTable[kintstrings])
	{
		if (args_obj[0].text[0] != '\0' ||
			args_obj[1].text[0] != '\0' ||
			args_obj[2].text[0] == '\0')
	    {
			string s1 = args_obj[0].text;
			string s2 = args_obj[1].text;
			
			mdl.AnalyseIntegerRhythmStrings (s1, s2);
	    }
	}
	
	
	if (ms == modulTable[kfarey2binary])
	{
		if (args_obj[0].text[0] != '\0' ||
			args_obj[1].text[0] != '\0' ||
			args_obj[2].text[0] != '\0' ||
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
	}
	
	if (ms == modulTable[kdivisors])
	{
		mdl.Divisors ();
	}
	
	if (ms == modulTable[kpermutations])
	{
		mdl.Permutations ();
	}
	
	if (ms == modulTable[kpermutations2])
	{
		mdl.Permutations2 ();
	}
	
	if (ms == modulTable[kfpoly])
	{
		if (args_obj[0].text[0] != '\0' ||
			args_obj[1].text[0] != '\0' ||
			args_obj[2].text[0] != '\0' ||
			args_obj[3].text[0] == '\0')
	    {
			char* c1 = args_obj[0].text;
			int i1 = atoi (c1);
			char* c2 = args_obj[1].text;
			int i2 = atoi (c2);
			char* c3 = args_obj[2].text;
			int i3 = atoi (c3);
			mdl.FareyPolyrhythm (i1, i2, i3);
		}
	}
    
    if (ms == modulTable[kprintfarey])
    {
        if (args_obj[0].text[0] != '\0' ||
            args_obj[1].text[0] == '\0')
        {
            char* c1 = args_obj[0].text;
            int i1 = atoi (c1);
            
            mdl.PrintFareySeq (i1);
        }
        
    }
	
	if (ms == modulTable[kcrhythm])
    {
        if (args_obj[0].text[0] != '\0' ||
	    args_obj[1].text[0] != '\0' ||
            args_obj[2].text[0] == '\0')
        {
            char* c1 = args_obj[0].text;
            int i1 = atoi (c1);
	    char* c2 = args_obj[1].text;
            int i2 = atoi (c2);

            
            mdl.CRhythm (i1, i2);
        }
        
    }

	if (ms == modulTable[kcrhythm2])
	  {
	    if (args_obj[0].text[0] != '\0' ||
		args_obj[1].text[0] != '\0' ||
		args_obj[2].text[0] != '\0' ||
		args_obj[3].text[0] != '\0' ||
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
	      }

	  }



	
	if (ms == modulTable[klookup])
    {
        if (args_obj[0].text[0] != '\0' ||
            args_obj[1].text[0] == '\0')
        {
            string s1 = args_obj[0].text;
            
            mdl.LookupRhythm (s1);
        }
        
    }
	if (ms == modulTable[kloadpartition]) {
	  if (args_obj[0].text[0] != '\0' ||
	      args_obj[1].text[0] != '\0' ||
	      args_obj[2].text[0] == '\0') {
	  string s1 = args_obj[0].text;
	  char* c1 = args_obj[1].text;
	  int i1 = atoi (c1);
	  cout << s1 << " " << i1 << endl;
	  mdl.LoadPartitions (s1, i1);
	  }
	}

	if (ms == modulTable[kgetpartition]) {
	  char* c1 = args_obj[0].text;
          int i1 = atoi (c1);
	  char* c2 = args_obj[1].text;
          int i2 = atoi (c2);
	  char* c3 = args_obj[2].text;
          int i3 = atoi (c3);
          mdl.GetPartition (i1, i2, i3);
        }

	if (ms == modulTable[ksentence]) {
	      char* c1 = args_obj[0].text;
	      int i1 = atoi (c1);
	      char* c2 = args_obj[1].text;
	      int i2 = atoi (c2);
            //cout << i1 << " " << i2 << endl;
        if (i1 == 0 || i2 == 0) {
            cout << "USAGE: chunking -m sentence n k" << endl;
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
	cout << "Usage: chunking -m bwtmel <string> <int> <string>" << endl;
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
	cout << "After being saved as a file, the output can be used together with printphtases to merge the pitches with rhythmic phrases." << endl;
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
      if (args_obj[0].text[0] != '\0') {
        string s1 = args_obj[0].text;
        mdl.iBWTspecific (s1, 0, 0);
      }
      else {
	cout << "Usage: chunking -m bwtmatrix <shorthand string>" << endl;
      }
    }
    
	for (int i = 0; i < MAXLINES; i++)
		args_obj[i].text[0] = '\0';

}



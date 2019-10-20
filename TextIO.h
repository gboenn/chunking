///////////////////////////////////////////
// TextIO.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __TextIO_h__

#define __TextIO_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif

#ifndef __DList_h__
#include "DList.h"
#endif


enum
{
    kPropSeries=0,
    kPartition,
	kfarey2binary,
	kdivisors,
	kpermutations,
	kfpoly,
	kpermutations2,
	kintstrings,
	kconcatq,
	kanaphrases,
    kprintfarey,
	kcrhythm,
    klookup,
	kloadpartition,
	kgetpartition,
	ksentence,
	kcrhythm2,
    kprintphrases,
    kbwt,
    kbwtmel,
    knotenames,
    knotes2midi,
    kbwtpath,
    kbwtmatrix,
	kdb,
    kdb_insert,
    kextract,
    kshortening,
    ksproc,
    kjump,
    kmutate,
    kswap,
    ksilence,
    kproc2shapes,
    kfragment,
    krotate,
    kfragrotate,
    kcompose,
    kreverse,
    kmidi2notes,
    kstartsession,
    kstopsession,
    kprintsession,
    klistsessions,
    ksession,
    kbendf,
    kaddrep,
    krepeat,
    knest,
    ktsnmr,
	kNumModules
};	

static const char* modulTable[kNumModules] = 
{
    "propseries",
    "partition",
    "farey2binary",
	"divisors",
	"permutations",
	"fpoly",
	"permutations2",
	"intstrings",
	"concatq",
	"anaphrases",
    "printfarey",
	"crhythm",
	"lookup",
	"loadp",
	"getpart",
	"sentence",
	"compc",
    "printphrases",
    "bwt",
    "bwtmel",
    "notenames",
    "notes2midi",
    "bwtpath",
	"bwtmatrix",
	"db",
    "dbinsert",
    "extract_local_comp",
    "shortening",
    "sproc",
    "jump",
    "mutate",
    "swap",
    "silence",
    "shape",
    "fragment",
    "rotate",
    "fragrotate",
    "compose",
    "reverse",
    "midi2notes",
    "startsession",
    "stopsession",
    "printsession",
    "listsessions",
    "session",
    "bendf",
    "addrep",
	"repeat",
	"nest",
    "tsnmr"
    };



struct TextBuf 
{
	char text[MAXTEXTCHARS];
	int length;
};
			
class TextIO {
	
	private:
		
		int count;
		int w_in_line;

 public:
		DList<TextBuf>* text_obj;
		//		struct TextBuf* text_obj;
			
 		TextIO( string echoinit );
		~TextIO ();
		void TextRead( ifstream& isfptr, string filename );
		void ReadCommands();
		void PrintHelp( char* askfor );
		void PrintManual();
		void SelectHelp( int index );
		void TextWrite( ofstream& osfptr, string filename );
		void TextExchange( ifstream& isfptr, ofstream& osfptr, string filename, string type, string outputfile );

		void CatchWords( TextIO& t, TextIO& p, int line_no );
		void ShowWord( int line_no, string format="n" );
		
		int GetW_In_Line () const { return w_in_line; }		
		string GetLine( int lne_no );
		int GetCount () const { return count; }
		char GetTextBufChar (int a, int b) const { 
		  return text_obj->getAt (a)->data->text[b]; 
		}
		const char* GetTextBufText (int a) const { 
		  return text_obj->getAt (a)->data->text;
		} 
		int GetTextBufLength (int a) const { 
		  return text_obj->getAt (a)->data->length;
		}

};


class StringToFile {

 public:

  StringToFile (string path) {
    filename = path;
    output.open (filename.c_str(), ios_base::out);
    if (!output)
      cerr << "cannot write file: " << filename << endl;
  }
  ~StringToFile () { 
    if (output)
      output.close ();
  }
  void Append (string text) {
    if (output) {
      output << text << endl;
	} else {
      cerr << "cannot append to file: " << filename << endl;
    }
  }

 private:
  ofstream output;
  string filename;

};

#endif // __TextIO_h__


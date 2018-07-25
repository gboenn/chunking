///////////////////////////////////////////
// TextIO.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __TextIO_h__

#define __TextIO_h__

#ifndef __Standards_h__
#include "Standards.h"
#endif

#ifndef __DList_h__
#include "DList.h"
#endif

#if 1
enum
{
	kSettings = 0,
	kCopySF,
	kReadText,
	kMIDItoFreq,
	kFreqtoMIDI,
	kMMtoF,
	kFtoMM,
	kmstof,
	kmstoMM,
	kQtoMM,
	kSetFolder,
	kHelp,
	kFtoFFT,
	kFFTtoF,
	kDir,
	kCd,
	kManual,
	kHistory,
	kFtoL,
	kLtoF,
	kRatioToCents,
	kCentsToRatio,
	kl,
	kHarmon,
	kNormalise,
	kCrossSynth,
	kFarey,
	kFareyHarmon,
	kFareyDigest,
	kFareyDiff,
	kTestQuant,
	kNotat,
	kConvertTest,
	kTestQuant2,
	kScriptFareyDiff,
	kNotat2,
	kConvertData,
	kCheckRatios,
	kConvertMarkers,
	kGenerateTestSeries,
	kAddNoiseToIOTList,
	kShuffleData,
	kCyclicPermutations,
	kModulateTestSeries,
	kGenerateTestSeries2,
	kTestEgypt,
	kAleaNoise,
	kGenBeatSeq,
	kFreqResp,
	kr0,
	kr1,
	kr2,
	kr3,
	kr4,
	kr5,
	kr6,
	ka1,
	ka2,
	ka3,
	ka4,
	kTempo,
	kRetention,
	kTranscript,
	kPropSeries,
	kPartition,
	kRandomRhythm,
	kAnaOns,
	kgroups,
	kclaves,
	kConvertTestLog,
	kFareyEgyptian,
	kEngelExpansion,
	kFareyNet,
	kGradus,
	kHarmonicity,
	kDigestibility,
	kConvertQuantOut,
	kpan,
	kmotion,
	kwindowan,
	kperfan,
	kperfan2,
	kftri,
	kTempoAna,
	kPrepPack,
	kftor,
	ktestftor,
	kftor2,
	ktestftor2,
	ksternbrocot,
	kftor3,
	knotat4,
	kdstr,
	kanacont,
	keuler,
	krk4,
	krk4system,
	krk4duffing,
	kfareylondon,
	kfareytree,
	kloadmidi,
	kanacont2,
	kprimfac,
	kbarlen,
	kmidions,
	keudist,
	kaccumdurs,
	kstitch,
	klondtest,
	kstitch2,
	kprogram,
	ktobinary,
	kreihe,
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
	kNumModules
};	

static const char* modulTable[kNumModules] = 
{
	"Settings",
	"CopySF",
	"ReadText",
	"MIDItoFreq",
	"FreqtoMIDI",
	"MMtoF",
	"FtoMM",
	"mstof",
	"mstoMM",
	"QtoMM",
	"SetFolder",
	"?",
	"FtoFFT",
	"FFTtoF",
	"dir",
	"cd",
	"Manual",
	"h",
	"FtoL",
	"LtoF",
	"RtoC",
	"CtoR",
	"l",
	"Harmon",
        "Normalise",
        "CrossSynth",
	"Farey",
	"FareyHarmon",
	"FareyDigest",
	"FareyDiff",
	"TestQuant",
	"Notat",
	"ConvertTest",
	"TestQuant2",
	"ScriptFareyDiff",
	"Notat2",
	"ConvertData",
	"CheckRatios",
	"ConvertMarkers",
	"RSeries",
	"AddNoiseToIOTList",
	"ShuffleData",
	"CyclicPermutations",
	"ModulateTestSeries",
	"GenSeries",
	"TestEgypt",
	"AleaNoise",
	"BeatSeq",
	"FreqResp",
	"r0",
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"a1",
	"a2",
	"a3",
	"a4",
	"tempo",
	"rr0",
	"score",
	"propseries",
	"partition",
	"random_rhythm",
	"anaons",
	"groups",
	"claves",
	"ConvertTestLog",
	"fe",
	"engel",
	"fnet",
	"gradus",
	"ha",
	"digestibility",
	"convert",
	"pan",
	"motion", 
	"windowan",
	"perfan",
	"perfan2",
	"ftri",
	"tana",
	"preppack",
	"ftor",
	"testftor",
	"ftor2",
	"testftor2",
	"sternbrocot",
	"ftor3",
	"notat4",
	"dstr",
	"anacont",
	"euler",
	"rk4",
	"rk4system",
	"rk4duffing",
	"fareylondon",
	"fareytree",
	"loadmidi",
	"anacont2",
	"primfac",
	"barlen",
	"midions",
	"eudist",
	"accumdurs",
	"stitch",
	"londtest",
	"stitch2",
	"program",
	"tobinary",
	"reihe",
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
    "compose"
    };

#endif

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

#endif // __TextIO_h__


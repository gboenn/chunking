#ifndef __Interpret_h__

#define __Interpret_h__

#ifndef __Standards_h__
#include "Standards.h"
#endif

#ifndef __TextIO_h__
#include "TextIO.h"
#endif

#ifndef	__Modul_h__
#include "Modul.h"
#endif

#if 0
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
	"program"
    };
#endif

#include <string.h>

struct ArgBuf 
{
	char text[MAXZEILEN];
};

class Modul;

class Interpret {

	private:

		int i; // index to lines
		int k; // index to characters on line
		int w; // index to words
		int wk; // index to characters of word
		int wc; // counter
		int we;
		int wl;
		int ck;
		int nchars; // length of line 
		int nullcount;
		
		char zeile[MAXZEILEN];
		string args[MAXLINES];
		string wort[MAXLINES][MAXWORTE];

		string prompt;

		struct ArgBuf args_obj[MAXLINES];
		string ms;

	public:

		Interpret();
		~Interpret();
		void DoInterpret( TextIO& coms, Modul& mdl );
		void Dispatch( TextIO& coms, Modul& mdl, int from_cmd_line=0 );
		void TypeError( TextIO& coms, string ms );
		void SetArgs (string arg, int index) { strcpy (args_obj[index].text, arg.c_str()); }
		void SetModulFunct (string function_name) { ms = function_name; }

};

#endif // __Interpret_h__

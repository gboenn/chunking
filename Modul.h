///////////////////////////////////////////
// Modul.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef	__Modul_h__
#define	__Modul_h__ 
 
#ifndef __Standards_h__ 
#include "Standards.h" 
#endif 
 
#ifndef	__AlgoComp_h__ 
#include "AlgoComp.h" 
#endif 

#ifndef	__Alea_h__ 
#include "Alea.h" 
#endif 
 

#ifndef __TextIO_h__ 
#include "TextIO.h" 
#endif 
 
#ifndef __Interpret_h__ 
#include "Interpret.h" 
#endif 
 
#ifndef __SternBrocot_h__ 
#include "SternBrocot.h"
#endif

#include <vector>
#include <numeric>
#include <map>
#include <sstream>

#define PROGRESS 0 


struct partitions {
  int N;
  vector<int> parts;
  float sigma;
};

struct finali {
    float quant;
    float timing;
    float accumtim;
};

struct timingdat {
    int note;
    float timesec;
    int event;
    float delta;
};

struct motion_struct {
    int index;
    float motion;
};

struct quant_result { 
	DList<Ratio>* quant_list; 
	float sum; 
	float digest; 
    float weight;
    float digest_denom;
    float euclid;

    int num_ties;
    DList<float>* acc_res;
    float digest_subdiv;
    int all_same_durs;
    float ons_indigest;

}; 
 
struct float_digest { 
			int nom; 
			int denom; 
			float value; 
			float digest; 
			float search_weight; 
		}; 
 
struct rythm_tree { 
	float value; 
	int index; 
	int subdivision; 
}; 

struct quant_global_info {
    DList<float>* orig_onsets;
    DList<DList<float> >* groups;
    DList<DList <Ratio> >* egyptians;
    DList<float>* means;
    DList<DList<float_digest> >* candidates;
};

struct quant_solution_info {
    int solution_number;
    quant_result* result;
    float diff_total;
    float orig_ons_harmon;
    float orig_ons_digest;
    float orig_dur_harmon;
    float orig_dur_digest;
    DList<float>* scaling_digests;
    float chosen_scaling;
    float chosen_scaling_digest;
    Ratio* time_signature;
    float time_sig_harmon;
    float time_sig_digest;
    int number_of_tuplets;
    DList<int>* list_of_tuplets;
    float sum_digest_tuplets;
    float weight;
    int mark;
    float scalesum;
    float deviation;
    int equal_denom;
    
};

struct quant_solution_tuplets_info {
    int solution_number;
    float sum_digest_tuplets;
};

struct final_weights_info {
    int sol_num;
    float weight;
};

struct difference_function {
    int index;
    float val;
};

struct freqdat {
	float val;
	int freq;
};

struct scoremap {
    string notename;

};

struct metrecalc {
    float harmsum;
    float quarterval;
};

struct analysisentry {
	int musicindex;
	double kldist;
	double ecldist;
	DList<int>* dbentry;
	DList<float>* musicentry;
};

/*
int digest_list_compare (const void* arg1, const void* arg2); 
int digest_list_compare2 (const void* arg1, const void* arg2); 
int digest_list_compare_weight (const void* arg1, const void* arg2); 
int sort_quant_result (const void* arg1, const void* arg2); 
int sort_rythm_tree (const void* arg1, const void* arg2); 
int sort_durclasses (const void* arg1, const void* arg2); 
int sort_tuplet_info (const void* arg1, const void* arg2);
float calc_quant_frame_weight (DLink<quant_solution_info>* qsil);
int sort_final_weights_info (const void* arg1, const void* arg2); 
int sort_quant_result_ties (const void* arg1, const void* arg2);
int sort_projlist (const void* arg1, const void* arg2);
int sort_quant_euclidean (const void* arg1, const void* arg2);
int sort_freqdat (const void* arg1, const void* arg2);
int sort_mlist (const void* arg1, const void* arg2);
*/

class Modul 
	{ 
 
	friend class Interpret; 
	friend class TextIO; 
	 
	private: 
	 
		ifstream* sound_stream; 
		ofstream* record_stream; 
		bool doRecord; 
				 
		enum { 
			kBigEndian = 1, 
			kLittleEndian 
		}; 
		 
		string planetSoundFileName; 
		double progressVal; 
		 
		TextIO* logfile;
		quant_global_info* QGI;
		DList<quant_solution_info>* qsi;
		DList<DList<int> >* dcl; // dur classes
		DList<final_weights_info>* result_weights; 
		DList<final_weights_info>* result_weights2;
		int m_beat; // provided by TestTranscript2 ()
		int m_window;
		DList<difference_function>* df;
		
		int m_autom;
		int m_numties;
		int m_digestint;
		int m_meter_p;
		int m_meter_q;

		int pack_count;
		float x_;
		float y_;

		float lastrat;
		int qdurcount;
		float firstdur;
		float firstdurt;
		float lastinteg;
		DList<finali>* quli;
		
		DList<DList<float> >* rhythm_database;
		DList<analysisentry >* analysis_database;
		DList<int>* pulse_seq; 
		DList<float>* real_pulseq; 


		vector <vector <float> >* matrix;
		vector <vector <float> >* matrix2;
		vector <vector <float> >* matrix3;
		vector <vector <float> >* matrix4;
		vector <vector <float> >* matrix5;
		vector <vector <float> >* matrix_2s3s;
		vector <vector <float> >* bracelets;

		vector <vector <float> >* resistor;
		vector <vector <float> >* release;
		vector <vector <float> >* arch;
		vector <vector <float> >* catenary;
		vector <vector <float> >* alternating;
		vector <vector <float> >* growth;
		vector <vector <float> >* decrease;

		vector <vector <int> >* m_triangles;

		string m_group2;
		string m_group3;
		string m_group4;
		vector <string> m_group5;
		vector <string> m_group6;
		vector <string> m_group7;
		vector <string> m_group8;
		vector <string> m_group9;

        int meter_store;
        vector<vector<string> > mel_matrix;
        int pitch_line;
        float BPM;
        
	public: 

	Modul ();
	//		Modul( string filtyp, unsigned long chan, unsigned long samframs, unsigned long samsiz, unsigned long samrat ); 
		~Modul(); 
 	
		void CircleMap ();

		void AnalyseBinaryRhythmStrings (string filename);
		void FareyToBinaryRhythm (int farey_index, int dig, int flag);
		void Divisors ();
		void Permutations ();
		void Permutations2 ();
		void FareyPolyrhythm (int f, int p, int q); 
		void AnalyseIntegerRhythmStrings (string filename, string filename2);
		void AnalyseConcatQ (string filename);
		void LoadRhythmDatabase (string filename);
		void DatabaseCompare (DLink<DList<float> >* entry, DList<DList<float> >* input, int input_index, int length);
		void DisplayDatabase ();
		DLink<float>* GetPulSeqFirst () {return real_pulseq->first (); }
	
		void AnalysePhrases (string filename, int minbeat, int maxbeat, int bwt_out_flag);
		void FilterFareyPulsesWithBinary (DList<Ratio>* rlist, DList<Ratio>* patlist, string pattern);
		void CreateFareyPulses (int n, DList<Ratio>* rlist) ;
        void PrintFareySeq (int n);
		void CRhythm (int m, int n);
		void CompareCRhythms (int m, int n, int m2, int n2);
        void LookupRhythm (string s);
        void Cbaum (int p, int q);
	
	bool StringToInt (string s, int* val);
	bool StringToFloat(string s, float* val);
	void LoadPartitions (string filename, int k);
	void GetPartition (int n, int k, int cond);
	int GetPartitionSmallestSigma (int n, int k);
	void LoadAllPartitions (); 
	void StartSentence (int n, int k);
	void GetPartitionVector (int n, int& k, int cond, vector<float>* v);
	void PrintFloatVector (vector<float>* v, bool flag=false);
	int GetPartitionHighestSigma (int n);
	void LoadBracelets ();
	void LoadForms ();
	void PickBracelet (vector<float>* v, int n);
	void MatchBracelets (vector<vector<float > >* pattern_chunks, vector<vector<float > >* selected_chunks);
	void PickMusicalForm (vector<vector<float > >* pattern_chunks, vector<vector<float > >* selected_chunks);
	void PickMusicalFormViaIndex (int n, vector<float>* selected_chunks, int form, int form_index);
	void ApplyMusicalTriangle (vector<float>* phrase);
	float CompareStrings (string& s1, string& s2);
	vector<int> LookupGrouping (string& in);
	string PickRhythmChunk (int g);
	void WriteToLilyfile (ofstream& s, string pattern, bool init, bool finish, bool grouping=true);
	int LoadMelodyFromFile (string filename, vector<vector<string> >& matrix);
	void WriteToCsoundScore (ofstream& s, string pattern, float* onset, float period);
    void WriteToCsoundScore2 (ofstream& s, string pattern, float* onset, float period);
	void PrintSentenceStatement (ofstream& s, vector<float>* v, float* onset, float period, int instr);
    void PrintPhrases (string filename, string pitches, float bpm, int flag);
    void PrintPolyPhrases (string filename, string pitches, float bpm);
    vector<vector<string> > GetPitches () { return mel_matrix; }
    void SetPitchLine (int i) { pitch_line = i; }
    int GetPitchLine () { return pitch_line; }
    void BWT (string word);
    void BWTmelodies (string word, int trans, string gestalt);
    void notenames2asciinames (string notes);
        void notenames2midinotes (string filename);
        void iBWTspecific (string input, int k, int l);
        void iBWTpathway (string shorthand, string filename);
        void iBWTonBWTword (string bwtword);
	void DB_search (string searchstring);
        void DB_insert_from_file (string filename, string patname, string origin, string composer);
        void extract_from_analysephrases_output (string filename);
        string Shortening (string rhythm, int flag);
        void ShorteningProcess (string rhythm);
        string Jumping (string rhythm, int n, int k, int flag);
        string Fragment (string rhythm);
        string Rotation (string rhythm);
        string FragmentRotation (string rhythm);
        string Mutation (string rhythm, int n);
        string Swap (string rhythm, int n);
        string Reverse (string rhythm);
        string Growth (string rhythm);
        string Silence (string rhythm, int n, int k);
        string ProcessToShapes (string rhythm, int flag);
        void Compose (string rhythm);
        void midinotes2notenames (string filename);
        void BendFarey (int n);
        void AddAndRepeat (string rhythm, int n, int k);
        void Repeat (string input, int n);
	void Nest (string input);
};

class Decoder {
private:
	
	int flag;
	string code;
    string lc; //lilypond code
    string note;
    vector<vector<string> > pitches;
    int mel_line; //test to pick a new melody line
    int mel_count;
    vector<string> pitch_classes;
    //vector<int> last_midi_note; // int to vector<int>
    vector<int> midi_note; // int to vector<int>
    map<string,int> notename_midi_map;
    
public:
    Decoder () { flag = 0; code=""; note="a"; mel_line=0; mel_count=0;
        
        //last_midi_note.push_back(0);
        
        pitch_classes.push_back ("c");
        pitch_classes.push_back ("cis");
        pitch_classes.push_back ("d");
        pitch_classes.push_back ("es");
        pitch_classes.push_back ("e");
        pitch_classes.push_back ("f");
        pitch_classes.push_back ("fis");
        pitch_classes.push_back ("g");
        pitch_classes.push_back ("as");
        pitch_classes.push_back ("a");
        pitch_classes.push_back ("bes");
        pitch_classes.push_back ("b");
        vector<string> default_pitch;
        default_pitch.push_back ("a");
        pitches.push_back (default_pitch);
        
        notename_midi_map["A0"] = 21;
        notename_midi_map["A#0"] = 22;
        notename_midi_map["Bb0"] = 22;
        notename_midi_map["B0"] = 23;
        notename_midi_map["C1"] = 24;
        notename_midi_map["D1"] = 26;
        notename_midi_map["E1"] = 28;
        notename_midi_map["F1"] = 29;
        notename_midi_map["G1"] = 31;
        notename_midi_map["A1"] = 33;
        notename_midi_map["B1"] = 35;
        notename_midi_map["C#1"] = 25;
        notename_midi_map["Dd1"] = 25;
        notename_midi_map["Eb1"] = 27;
        notename_midi_map["D#1"] = 27;
        notename_midi_map["F#1"] = 30;
        notename_midi_map["Gb1"] = 30;
        notename_midi_map["Ab1"] = 32;
        notename_midi_map["G#1"] = 32;
        notename_midi_map["Bb1"] = 34;
        notename_midi_map["A#1"] = 34;
        notename_midi_map["C2"] = 36;
        notename_midi_map["D2"] = 38;
        notename_midi_map["E2"] = 40;
        notename_midi_map["F2"] = 41;
        notename_midi_map["G2"] = 43;
        notename_midi_map["A2"] = 45;
        notename_midi_map["B2"] = 47;
        notename_midi_map["C#2"] = 37;
        notename_midi_map["Db2"] = 37;
        notename_midi_map["Eb2"] = 39;
        notename_midi_map["D#2"] = 39;
        notename_midi_map["F#2"] = 42;
        notename_midi_map["Gb2"] = 42;
        notename_midi_map["Ab2"] = 44;
        notename_midi_map["G#2"] = 44;
        notename_midi_map["Bb2"] = 46;
        notename_midi_map["A#2"] = 46;
        notename_midi_map["C3"] = 48;
        notename_midi_map["D3"] = 50;
        notename_midi_map["E3"] = 52;
        notename_midi_map["F3"] = 53;
        notename_midi_map["G3"] = 55;
        notename_midi_map["A3"] = 57;
        notename_midi_map["B3"] = 59;
        notename_midi_map["C#3"] = 49;
        notename_midi_map["Db3"] = 49;
        notename_midi_map["Eb3"] = 51;
        notename_midi_map["D#3"] = 51;
        notename_midi_map["F#3"] = 54;
        notename_midi_map["Gb3"] = 54;
        notename_midi_map["Ab3"] = 56;
        notename_midi_map["G#3"] = 56;
        notename_midi_map["Bb3"] = 58;
        notename_midi_map["A#3"] = 58;
        notename_midi_map["C4"] = 60;
        notename_midi_map["D4"] = 62;
        notename_midi_map["E4"] = 64;
        notename_midi_map["F4"] = 65;
        notename_midi_map["G4"] = 67;
        notename_midi_map["A4"] = 69;
        notename_midi_map["B4"] = 71;
        notename_midi_map["C#4"] = 61;
        notename_midi_map["Db4"] = 61;
        notename_midi_map["Eb4"] = 63;
        notename_midi_map["D#4"] = 63;
        notename_midi_map["F#4"] = 66;
        notename_midi_map["Gb4"] = 66;
        notename_midi_map["Ab4"] = 68;
        notename_midi_map["G#4"] = 68;
        notename_midi_map["Bb4"] = 70;
        notename_midi_map["A#4"] = 70;
        notename_midi_map["C5"] = 72;
        notename_midi_map["D5"] = 74;
        notename_midi_map["E5"] = 76;
        notename_midi_map["F5"] = 77;
        notename_midi_map["G5"] = 79;
        notename_midi_map["A5"] = 81;
        notename_midi_map["B5"] = 83;
        notename_midi_map["C#5"] = 73;
        notename_midi_map["Db5"] = 73;
        notename_midi_map["Eb5"] = 75;
        notename_midi_map["D#5"] = 75;
        notename_midi_map["F#5"] = 78;
        notename_midi_map["Gb5"] = 78;
        notename_midi_map["Ab5"] = 80;
        notename_midi_map["G#5"] = 80;
        notename_midi_map["Bb5"] = 82;
        notename_midi_map["A#5"] = 82;
        notename_midi_map["C6"] = 84;
        notename_midi_map["D6"] = 86;
        notename_midi_map["E6"] = 88;
        notename_midi_map["F6"] = 89;
        notename_midi_map["G6"] = 91;
        notename_midi_map["A6"] = 93;
        notename_midi_map["B6"] = 95;
        notename_midi_map["C#6"] = 85;
        notename_midi_map["Db6"] = 85;
        notename_midi_map["Eb6"] = 87;
        notename_midi_map["D#6"] = 87;
        notename_midi_map["F#6"] = 90;
        notename_midi_map["Gb6"] = 90;
        notename_midi_map["Ab6"] = 92;
        notename_midi_map["G#6"] = 92;
        notename_midi_map["Bb6"] = 94;
        notename_midi_map["A#6"] = 94;
        notename_midi_map["C7"] = 96;
        notename_midi_map["D7"] = 98;
        notename_midi_map["E7"] = 100;
        notename_midi_map["F7"] = 101;
        notename_midi_map["G7"] = 103;
        notename_midi_map["A7"] = 105;
        notename_midi_map["B7"] = 107;
        notename_midi_map["C#7"] = 97;
        notename_midi_map["Db7"] = 97;
        notename_midi_map["Eb7"] = 99;
        notename_midi_map["D#7"] = 99;
        notename_midi_map["F#7"] = 102;
        notename_midi_map["Gb7"] = 102;
        notename_midi_map["Ab7"] = 104;
        notename_midi_map["G#7"] = 104;
        notename_midi_map["Bb7"] = 106;
        notename_midi_map["A#7"] = 106;
        notename_midi_map["C8"] = 108;

    }
	~Decoder () {};
    void printmap () {
        for (map<string,int>::iterator it=notename_midi_map.begin(); it!=notename_midi_map.end(); ++it)
            cout << it->first << " => " << it->second << endl;
    }
	void Set (int f) { flag = f; };
	string GetCode () { return code; };
	void SetNote (string n) { note = n; };
    void SetPitchLine (int i) { mel_line = i; }
    vector<int> GetLastMidiNote () { return midi_note; } // int to vector<int>
    //void SetLastMidiNote (int i) { last_midi_note.push_back(i); } //obsolete or int to vector<int>
    void SaveNote () { mel_count--; }
    void AdvanceNote () {
        if (flag == -2) return; // -2 is opening bracket flag - if there is one of the symbols ( ), brackets do not write to note
        if (flag == -3) {
            // -3 is end of brackets flag
            flag = 0; //reset flag
        }
        if (flag == -1) {
            flag = 0;
            return;
        }
        //clear midi_note
        midi_note.erase (midi_note.begin (), midi_note.end ());
        
        int size = pitches[mel_line].size ();
        //cout << "s:" << size << " ";
        string pstring = pitches.at(mel_line).at(mel_count);
        //cout << pstring << " ";
        if (pstring.find(":") != string::npos) {
            stringstream sstr1 (pstring);
            string n;
            
            while (getline (sstr1, n, ':')) {
                midi_note.push_back (atoi (n.c_str ()));
                //cout << midi_note.back () << " ";
            }
        } else {
            midi_note.push_back (atoi (pstring.c_str ()));
        }
        //mel_count: how many notes or chords in one line (=> 1 bar)
        //mel_line: how many lines of pitches in the input file
        //midi_note is vector<int> start loop over string pitches.at(mel_line).at(mel_count)
        //with ':' as delimiter for chord notes. for ex. 60:64:67 for c major chord starting on C4
        //for lilypond build a string that contains the octaves (c' c,) for each chord note
        //and has the format: <c' e' g'> (pointy brackets to enclose a chord)
        //midi_note.push_back( atoi( pitches.at(mel_line).at(mel_count++).c_str () ));
   
        int midi_note_size = midi_note.size ();
        //cout << "midi_note_size: " << midi_note_size << " ";
        if (midi_note_size > 1) { // if there is a chord
            int i = 0;
            note = "<";
            for (; i < midi_note_size; i++) {
                string octave = "";
                int oct = midi_note.at(i) / 12;
                //cout << oct << " ";
                if (oct > 4) {
                    oct -= 4;
                    for (int i = 0; i < oct; i++)
                        octave += "'";
                }
                else {
                    for (int i=4; i>oct ;  i--)
                        octave += ",";
                }
                //last_midi_note.push_back(midi_note.at(i));
                string pitch = pitch_classes[(midi_note.at(i) % 12)];
                note += pitch + octave + " "; // for lilypond
                //cout << "note: " << note << " ";
            }
            note += ">";
        } else {
            //cout << "midi " << midi_note.at(0) << " ";
            string octave = "";
            int oct = midi_note.at(0) / 12;
            //cout << oct << " ";
            if (oct > 4) {
                oct -= 4;
                for (int i = 0; i < oct; i++)
                    octave += "'";
            }
            else {
                for (int i=4; i>oct ;  i--)
                    octave += ",";
            }
            //for chords: last_midi_note and midi_note have to be vector<int> lists
            //last_midi_note.at(0) = midi_note.at(0); // for csound
            //for chords in lilypond: pitches and octaves have to be assembled via loop, ex.: <c' e' g'>
            string pitch = pitch_classes[(midi_note.at(0) % 12)];
            note = pitch + octave; // for lilypond
            //cout << note << " ";
        }
        
        
        if (++mel_count == size) mel_count = 0;
    }
    
    void SetPitches (vector<vector<string> > matrix) { pitches = matrix; };
    
	int decode_shorthand_length (int s) {
		// . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |
        // v 118 | w 119 | H 72
		//int code = s;
		switch (s) {
            case 87:
                return 8;
            case 72:
                return 4;
            case 119:
                return 3;
            case 118:
                return 2;
			case 46:
				return 1;
			case 73:
				return 2;
			case 58:
				return 2;
			case 47:
				return 2;
			case 88:
				return 3;
		case 33:
		  return 4;
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
				//Set(-1);
				return -1;
			case 40:
				//Set(-2);
				return -2;
			case 41:
				//Set(-3);
				return -3;
			default:
				return 0;
		}
		
		
	}

	void decode_for_csound (int s, float period_in_secs, float* onset, vector<float>& notes) {
	  //shorthand convert to csound score instrument parameters p2 (onset) and p3 (duration) on basis of period of pulsation in seconds
	  //notes vector will contain onset1, duration1, onset2, duration2, ...
	  //the previous note end is passed as current onset arg. When there is no rest at the beginning of the new pattern, then onset is the first onset of the new note
	  // . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |                           
	  // v 118 | w 119 | H 72  
	  switch (s) {
	  case 72:
	    //lc = "a2";
	    notes.push_back(*onset);
	    notes.push_back(4.f * period_in_secs);
	    *onset = *onset + 4.f * period_in_secs;
	    break;
	  case 119:
	    //lc = "r8 r a";
	    notes.push_back(*onset + 2.f * period_in_secs);
            notes.push_back(period_in_secs);
	    *onset = *onset + 3.f * period_in_secs;
	    break;
	  case 118:
	    //lc = "r8 a";
	    notes.push_back(*onset + period_in_secs);
            notes.push_back(period_in_secs);
	    *onset = *onset + 2.f * period_in_secs;
	    break;
	  case 46:
	    //	    lc = "a8";
	    notes.push_back(*onset);
            notes.push_back(period_in_secs);
	    *onset = *onset + period_in_secs;
	    break;
	  case 73:
	    //lc = "a4";
	    notes.push_back(*onset);
            notes.push_back(2.f * period_in_secs);
	    *onset = *onset + 2.f * period_in_secs;
	    break;
	  case 58:
	    //lc = "a8[ a]";
	    notes.push_back(*onset);
            notes.push_back(period_in_secs);
	    notes.push_back(*onset + period_in_secs);
            notes.push_back(period_in_secs);
	    *onset = *onset + 2.f * period_in_secs;
	    break;
	  case 47:
	    //	    lc = "r8 a";
	    notes.push_back(*onset + period_in_secs);
            notes.push_back(period_in_secs);
	    *onset = *onset + 2.f * period_in_secs;
	    break;
	  case 88:
	    //lc = "a8[ a] r";
	    notes.push_back(*onset);
            notes.push_back(period_in_secs);
            notes.push_back(*onset + period_in_secs);
            notes.push_back(period_in_secs);
	    *onset = *onset + 3.f * period_in_secs; 
	    break;
	  case 62:
	    //	    lc = "a4 a8";
	    notes.push_back(*onset);
            notes.push_back(2.f * period_in_secs);
	    notes.push_back(*onset + 2.f * period_in_secs);
            notes.push_back(period_in_secs);
	    *onset = *onset + 3.f * period_in_secs;
	    break;
	  case 60:
	    //lc = "r8 a4";
	    notes.push_back(*onset + period_in_secs);
            notes.push_back(2.f * period_in_secs);
            *onset = *onset + 3.f * period_in_secs;
	    break;
	  case 43:
	    //lc = "r8 a[ a]";
	    notes.push_back(*onset + period_in_secs);
            notes.push_back(period_in_secs);
	    notes.push_back(*onset + 2.f * period_in_secs);
            notes.push_back(period_in_secs);
            *onset = *onset + 3.f * period_in_secs;
	    break;
	  case 105:
	    //lc = "a8[ a a]";
	    notes.push_back(*onset);
            notes.push_back(period_in_secs);
	    notes.push_back(*onset + period_in_secs);
            notes.push_back(period_in_secs);
            notes.push_back(*onset + 2.f * period_in_secs);
            notes.push_back(period_in_secs);
            *onset = *onset + 3.f * period_in_secs;
	    break;
	  case 45:
	    //lc = "a4.";
	    notes.push_back(*onset);
            notes.push_back(3.f * period_in_secs);
            *onset = *onset + 3.f * period_in_secs;
	    break;
	  case 126:
	    //lc = "";
	    //Set(-1);
	    break;
	  case 40:
	    //lc = "";
	    //Set(-2);
	    break;
	  case 41:
	    //lc = "";
	    //Set(-3);
	    break;

	  default:
	    return;
	  }
	  return;
	}

    void decode_for_csound2 (int s, float period_in_secs, float* onset, vector<float>& notes) {
        //shorthand convert to csound score instrument parameters p2 (onset) and p3 (duration) on basis of period of pulsation in seconds
        //notes vector will contain onset1, duration1, amplitude1, onset2, duration2, amplitude2, ...
        //the previous note end is passed as current onset arg. When there is no rest at the beginning of the new pattern, then onset is the first onset of the new note
        // . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |
        // v 118 | w 119 | H 72
        float strong = 1.f;
        float weak = .6f;
        float weaker = .3f;
        switch (s) {
            case 72:
                //lc = "a2";
                notes.push_back(*onset);
                notes.push_back(4.f * period_in_secs);
                notes.push_back(strong);
                *onset = *onset + 4.f * period_in_secs;
                break;
            case 119:
                //lc = "r8 r a";
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 118:
                //lc = "r8 a";
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 46:
                //	    lc = "a8";
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                *onset = *onset + period_in_secs;
                break;
            case 73:
                //lc = "a4";
                notes.push_back(*onset);
                notes.push_back(2.f * period_in_secs);
                notes.push_back(strong);
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 58:
                //lc = "a8[ a]";
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 47:
                //	    lc = "r8 a";
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 88:
                //lc = "a8[ a] r";
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 3.f * period_in_secs;
                break;
	case 33:
          //lc = note + "8 " + note + "4. ";
          notes.push_back(*onset);
	  notes.push_back(period_in_secs);
	  notes.push_back(strong);
	  notes.push_back(*onset + period_in_secs*3.f);
	  notes.push_back(period_in_secs*3.f);
	  notes.push_back(weak);
	  *onset = *onset + 4.f * period_in_secs;
	  break;
            case 62:
                //	    lc = "a4 a8";
                notes.push_back(*onset);
                notes.push_back(2.f * period_in_secs);
                notes.push_back(strong);
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 60:
                //lc = "r8 a4";
                notes.push_back(*onset + period_in_secs);
                notes.push_back(2.f * period_in_secs);
                notes.push_back(weak);
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 43:
                //lc = "r8 a[ a]";
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weaker);
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 105:
                //lc = "a8[ a a]";
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weaker);
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 45:
                //lc = "a4.";
                notes.push_back(*onset);
                notes.push_back(3.f * period_in_secs);
                notes.push_back(strong);
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 126:
                //lc = "";
                //Set(-1);
                break;
            case 40:
                //lc = "";
                //Set(-2);
                break;
            case 41:
                //lc = "";
                //Set(-3);
                break;
                
            default:
                return;
        }
        return;
    }

    void decode_for_csound3 (int s, float period_in_secs, float* onset, vector<float>& notes)
    {
        // this is the converter used for csound score generation
        //shorthand convert to csound score instrument parameters p2 (onset) and p3 (duration) on basis of period of pulsation in seconds
        //notes vector will contain onset1, duration1, amplitude1, midipitch1, onset2, duration2, amplitude2, midipitch2, ...
        //the previous note end is passed as current onset arg. When there is no rest at the beginning of the new pattern, then onset is the first onset of the new note
        // . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |
        // v 118 | w 119 | H 72
        float strong = 1.f;
        float weak = .6f;
        float weaker = .3f;
        switch (s) {
            case 87:
                //whole note
                AdvanceNote ();
                //for chords one needs to loop over the  vector of vector<int>midi_note
                // same onset1, duration1, amplitude1, for all pitches of the chord
                notes.push_back(*onset);
                notes.push_back(8.f * period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 8.f * period_in_secs;
                break;
            case 72:
                //lc = "a2";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(4.f * period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 4.f * period_in_secs;
                break;
            case 119:
                //lc = "r8 r a";
                AdvanceNote ();
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 118:
                //lc = "r8 a";
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 46:
                //	    lc = "a8";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + period_in_secs;
                break;
            case 73:
                //lc = "a4";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(2.f * period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 58:
                //lc = "a8[ a]";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 47:
                //	    lc = "r8 a";
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 2.f * period_in_secs;
                break;
            case 88:
                //lc = "a8[ a] r";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 33:
                //lc = note + "8 " + note + "4. ";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs*3.f);
                notes.push_back(period_in_secs*3.f);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 4.f * period_in_secs;
                break;
            case 62:
                //	    lc = "a4 a8";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(2.f * period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 60:
                //lc = "r8 a4";
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(2.f * period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 43:
                //lc = "r8 a[ a]";
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weaker);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 105:
                //lc = "a8[ a a]";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weak);
                notes.push_back(GetLastMidiNote ().at(0));
                AdvanceNote ();
                notes.push_back(*onset + 2.f * period_in_secs);
                notes.push_back(period_in_secs);
                notes.push_back(weaker);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 45:
                //lc = "a4.";
                AdvanceNote ();
                notes.push_back(*onset);
                notes.push_back(3.f * period_in_secs);
                notes.push_back(strong);
                notes.push_back(GetLastMidiNote ().at(0));
                *onset = *onset + 3.f * period_in_secs;
                break;
            case 126:
                //lc = "";
                //Set(-1);
                break;
            case 40:
                //lc = "";
                //Set(-2);
                break;
            case 41:
                //lc = "";
                //Set(-3);
                break;
                
            default:
                return;
        }
        return;
    }
    
    string decode_for_lilypond (int s) {
        // . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |
        // v 118 | w 119 | H 72
        //int code = s;
        //string code = "";
        
        //AdvanceNote() advances the melody (pitches, chords) to the next item
        // chords are done with string <c' e' g'>
        switch (s) {
            case 87:
                AdvanceNote ();
                lc = note + "1";
                break;
            case 72:
                AdvanceNote ();
                lc = note + "2";
                break;
            case 119:
                AdvanceNote ();
                lc = "r8 r " + note;
                break;
            case 118:
                AdvanceNote ();
                lc = "r8 " + note;
                break;
            case 46:
                AdvanceNote ();
                lc = note + "8";
                break;
            case 73:
                AdvanceNote ();
                lc = note + "4";
                break;
            case 58:
                AdvanceNote ();
                lc = note + "8[ ";
                AdvanceNote ();
                lc += note + "]";
                break;
            case 47:
                AdvanceNote ();
                lc = "r8 " + note;
                break;
            case 33:
                AdvanceNote ();
                lc = note + "8 ";
                AdvanceNote ();
                lc += note + "4. ";
                break;
            case 88:
                AdvanceNote ();
                lc = note + "8[ ";
                AdvanceNote ();
                lc += note + "] r";
                break;
            case 62:
                AdvanceNote ();
                lc = note + "4 ";
                AdvanceNote ();
                lc += note + "8";
                break;
            case 60:
                //AdvanceNote ();
                lc = "r8 ";
                AdvanceNote ();
                lc += note + "4";
                break;
            case 43:
                AdvanceNote ();
                lc = "r8 " + note;
                AdvanceNote ();
                lc += "[ " + note + "]";
                break;
            case 105:
                AdvanceNote ();
                lc = note + "8[ ";
                AdvanceNote ();
                lc += note;
                AdvanceNote ();
                lc += " " +  note + "]";
                break;
            case 45:
                AdvanceNote ();
                lc = note + "4.";
                break;
            case 126:
                lc = " ~ ";
                Set(-1);
                //SaveNote ();
                break;
            case 40:
                lc = "";
                SetNote("r");
                Set(-2);
                break;
            case 41:
                lc = "";
                //SetNote("a");
                Set(-3);
                break;
            default:
                lc = "";
                return lc;
        }	
        return lc;
    }

    string decode_shorthand_symbol (int s) {
      // used in Modul::LookupRhythm() and Modul::AnalysePhrases()
		// . (46)  | I (73)  | : (58)  | / (47)  | X (88)  | > (62)  | < (60)  | + (43)  | i (105)  | - (45)   (32)  | ~ (126)  | ( (40)  | ) (41)  |
        // v 118 | w 119 | H 72
		//int code = s;
		//string code = "";
		switch (s) {
            case 72:
                code = "1000";
                edit_ties_silence ();
                break;
            case 119:
                code = "001";
                edit_ties_silence ();
                break;
            case 118:
                code = "01";
                edit_ties_silence ();
                break;
			case 46:
				code = "1";
				edit_ties_silence ();
				break;
			case 73:
				code = "10";
				edit_ties_silence ();
				break;
			case 58:
				code = "11";
				edit_ties_silence ();
				break;
			case 47:
				code = "01";
				edit_ties_silence ();
				break;
			case 88:
				code = "110";
				edit_ties_silence ();
				break;
		case 33:
		  code = "1100";
		  edit_ties_silence ();
		  break;
			case 62:
				code = "101";
				edit_ties_silence ();
				break;
			case 60:
				code = "010";
				edit_ties_silence ();
				break;
			case 43:
				code = "011";
				edit_ties_silence ();
				break;
			case 105:
				code = "111";
				edit_ties_silence ();
				break;
			case 45:
				code = "100";
				edit_ties_silence ();
				break;
			case 126:
				code = "";
				Set(-1);
				break;
			case 40:
				code = "";
				Set(-2);
				break;
			case 41:
				code = "";
				Set(-3);
				break;
			default:
                code = "";
				return code;
		}	
		return code;
	}

	void edit_ties_silence () {
		switch (flag) {
			case -1: // tie to next symbol silences first onset
				code.replace (0, 1, 1, '0' );
				flag = 0;
				break;
			case -2: // round brackets silences every onset in symbol (chunk)
				for (string::iterator it=code.begin(); it!=code.end(); ++it)
				{
					*it = '0';
				}
				break;
			case -3: // right bracket ends silence
				flag = 0;
				break;
			default:
				break;
		}
	}
    
    int asciipitch_to_midi (int s) {
        switch (s) {
             // X Y Z // lowest piano keys
            case 88:
                return 21;
            case 89:
                return 22;
            case 90:
                return 23;
                // Q R S T U V W
                // return MIDI note number for C1...B1
            case 81:
                return 24;
            case 82:
                return 26;
            case 83:
                return 28;
            case 84:
                return 29;
            case 85:
                return 31;
            case 86:
                return 33;
            case 87:
                return 35;
                // { } [ ] |
                // C#1 D#1 ...
            case 123:
                return 25;
            case 125:
                return 27;
            case 91:
                return 30;
            case 93:
                return 32;
            case 124:
                return 34;
                // I K L M N O P
                // return MIDI note number for C2...B2
            case 73:
                return 36;
            case 75:
                return 38;
            case 76:
                return 40;
            case 77:
                return 41;
            case 78:
                return 43;
            case 79:
                return 45;
            case 80:
                return 47;
                // , . ? : ;
                // C#2 D#2 ...
            case 44:
                return 37;
            case 46:
                return 39;
            case 63:
                return 42;
            case 58:
                return 44;
            case 59:
                return 46;
                // C D E F G A B
                // return MIDI note number for C3...B3
            case 67:
                return 48;
            case 68:
                return 50;
            case 69:
                return 52;
            case 70:
                return 53;
            case 71:
                return 55;
            case 65:
                return 57;
            case 66:
                return 59;
                // 1 2 3 4 5
                // C#3 D#3 ...
            case 49:
                return 49;
            case 50:
                return 51;
            case 51:
                return 54;
            case 52:
                return 56;
            case 53:
                return 58;
                // c d e f g a b
                // return MIDI note number for C4...B4
            case 99:
                return 60;
            case 100:
                return 62;
            case 101:
                return 64;
            case 102:
                return 65;
            case 103:
                return 67;
            case 97:
                return 69;
            case 98:
                return 71;
                // 6 7 8 9 0
                // C#4 D#4 ...
            case 54:
                return 61;
            case 55:
                return 63;
            case 56:
                return 66;
            case 57:
                return 68;
            case 48:
                return 70;
                
                // i k l m n o p
                // return MIDI note number for C5...B5
            case 105:
                return 72;
            case 107:
                return 74;
            case 108:
                return 76;
            case 109:
                return 77;
            case 110:
                return 79;
            case 111:
                return 81;
            case 112:
                return 83;
                // ! @ # $ %
                // C#5 D#5 ...
            case 33:
                return 73;
            case 64:
                return 75;
            case 35:
                return 78;
            case 36:
                return 80;
            case 37:
                return 82;
                
                // q r s t u v w
                // return MIDI note number for C6...B6
            case 113:
                return 84;
            case 114:
                return 86;
            case 115:
                return 88;
            case 116:
                return 89;
            case 117:
                return 91;
            case 118:
                return 93;
            case 119:
                return 95;
                // ^ & * ( )
                // C#6 D#6 ...
            case 94:
                return 85;
            case 38:
                return 87;
            case 42:
                return 90;
            case 40:
                return 92;
            case 41:
                return 94;
            
                // x y z h j H J
                // return MIDI note number for C7...B7
            case 120:
                return 96;
            case 121:
                return 98;
            case 122:
                return 100;
            case 104:
                return 101;
            case 106:
                return 103;
            case 72:
                return 105;
            case 74:
                return 107;
                // - + ~ ` "
                // C#7 D#7 ...
            case 45:
                return 97;
            case 43:
                return 99;
            case 126:
                return 102;
            case 96:
                return 104;
            case 34:
                return 106;
                //C8 last key on piano
            case 61:
                return 108;
                
            default:
                return 60;
        }
    }

    int midi_to_asciipitch (int s) {
        switch (s) {
                // X Y Z // lowest piano keys
            case 21:
                return 88;
            case 22:
                return 89;
            case 23:
                return 90;
                // Q R S T U V W
                // return MIDI note number for C1...B1
            case 24:
                return 81;
            case 26:
                return 82;
            case 28:
                return 83;
            case 29:
                return 84;
            case 31:
                return 85;
            case 33:
                return 86;
            case 35:
                return 87;
                // { } [ ] |
                // C#1 D#1 ...
            case 25:
                return 123;
            case 27:
                return 125;
            case 30:
                return 91;
            case 32:
                return 93;
            case 34:
                return 124;
                // I K L M N O P
                // return MIDI note number for C2...B2
            case 36:
                return 73;
            case 38:
                return 75;
            case 40:
                return 76;
            case 41:
                return 77;
            case 43:
                return 78;
            case 45:
                return 79;
            case 47:
                return 80;
                // , . ? : ;
                // C#2 D#2 ...
            case 37:
                return 44;
            case 39:
                return 46;
            case 42:
                return 63;
            case 44:
                return 58;
            case 46:
                return 59;
                
                // C D E F G A B
                // return MIDI note number for C3...B3
            case 48:
                return 67;
            case 50:
                return 68;
            case 52:
                return 69;
            case 53:
                return 70;
            case 55:
                return 71;
            case 57:
                return 65;
            case 59:
                return 66;
                // 1 2 3 4 5
                // C#3 D#3 ...
            case 49:
                return 49;
            case 51:
                return 50;
            case 54:
                return 51;
            case 56:
                return 52;
            case 58:
                return 53;
                // c d e f g a b
                // return MIDI note number for C4...B4
            case 60:
                return 99;
            case 62:
                return 100;
            case 64:
                return 101;
            case 65:
                return 102;
            case 67:
                return 103;
            case 69:
                return 97;
            case 71:
                return 98;
                // 6 7 8 9 0
                // C#4 D#4 ...
            case 61:
                return 54;
            case 63:
                return 55;
            case 66:
                return 56;
            case 68:
                return 57;
            case 70:
                return 48;
                
                
                // i k l m n o p
                // return MIDI note number for C5...B5
            case 72:
                return 105;
            case 74:
                return 107;
            case 76:
                return 108;
            case 77:
                return 109;
            case 79:
                return 110;
            case 81:
                return 111;
            case 83:
                return 112;
                // ! @ # $ %
                // C#5 D#5 ...
            case 73:
                return 33;
            case 75:
                return 64;
            case 78:
                return 35;
            case 80:
                return 36;
            case 82:
                return 37;
                
                // q r s t u v w
                // return MIDI note number for C6...B6
            case 84:
                return 113;
            case 86:
                return 114;
            case 88:
                return 115;
            case 89:
                return 116;
            case 91:
                return 117;
            case 93:
                return 118;
            case 95:
                return 119;
                // ^ & * ( )
                // C#6 D#6 ...
            case 85:
                return 94;
            case 87:
                return 38;
            case 90:
                return 42;
            case 92:
                return 40;
            case 94:
                return 41;
                
                // x y z h j H J
                // return MIDI note number for C7...B7
            case 96:
                return 120;
            case 98:
                return 121;
            case 100:
                return 122;
            case 101:
                return 104;
            case 103:
                return 106;
            case 105:
                return 72;
            case 107:
                return 74;
                // - + ~ ` "
                // C#7 D#7 ...
            case 97:
                return 45;
            case 99:
                return 43;
            case 102:
                return 126;
            case 104:
                return 96;
            case 106:
                return 34;
                //C8 last key on piano
            case 108:
                return 61;
                
                
            default:
                return 99;
        }
    }

    string midi_to_notename (int s) {
        switch (s) {
                // X Y Z // lowest piano keys
            case 21:
                return "A0";
            case 22:
                return "Bb0";
            case 23:
                return "B0";
                // Q R S T U V W
                // return MIDI note number for C1...B1
            case 24:
                return "C1";
            case 26:
                return "D1";
            case 28:
                return "E1";
            case 29:
                return "F1";
            case 31:
                return "G1";
            case 33:
                return "A1";
            case 35:
                return "B1";
                // { } [ ] |
                // C#1 D#1 ...
            case 25:
                return "C#1";
            case 27:
                return "Eb1";
            case 30:
                return "F#1";
            case 32:
                return "Ab1";
            case 34:
                return "Bb1";
                // I K L M N O P
                // return MIDI note number for C2...B2
            case 36:
                return "C2";
            case 38:
                return "D2";
            case 40:
                return "E2";
            case 41:
                return "F2";
            case 43:
                return "G2";
            case 45:
                return "A2";
            case 47:
                return "B2";
                // , . ? : ;
                // C#2 D#2 ...
            case 37:
                return "C#2";
            case 39:
                return "Eb2";
            case 42:
                return "F#2";
            case 44:
                return "Ab2";
            case 46:
                return "Bb2";
                
                // C D E F G A B
                // return MIDI note number for C3...B3
            case 48:
                return "C3";
            case 50:
                return "D3";
            case 52:
                return "E3";
            case 53:
                return "F3";
            case 55:
                return "G3";
            case 57:
                return "A3";
            case 59:
                return "B3";
                // 1 2 3 4 5
                // C#3 D#3 ...
            case 49:
                return "C#3";
            case 51:
                return "Eb3";
            case 54:
                return "F#3";
            case 56:
                return "Ab3";
            case 58:
                return "Bb3";
                // c d e f g a b
                // return MIDI note number for C4...B4
            case 60:
                return "C4";
            case 62:
                return "D4";
            case 64:
                return "E4";
            case 65:
                return "F4";
            case 67:
                return "G4";
            case 69:
                return "A4";
            case 71:
                return "B4";
                // 6 7 8 9 0
                // C#4 D#4 ...
            case 61:
                return "C#4";
            case 63:
                return "Eb4";
            case 66:
                return "F#4";
            case 68:
                return "Ab4";
            case 70:
                return "Bb4";
                
                
                // i k l m n o p
                // return MIDI note number for C5...B5
            case 72:
                return "C5";
            case 74:
                return "D5";
            case 76:
                return "E5";
            case 77:
                return "F5";
            case 79:
                return "G5";
            case 81:
                return "A5";
            case 83:
                return "B5";
                // ! @ # $ %
                // C#5 D#5 ...
            case 73:
                return "C#5";
            case 75:
                return "Eb5";
            case 78:
                return "F#5";
            case 80:
                return "Ab5";
            case 82:
                return "Bb5";
                
                // q r s t u v w
                // return MIDI note number for C6...B6
            case 84:
                return "C6";
            case 86:
                return "D6";
            case 88:
                return "E6";
            case 89:
                return "F6";
            case 91:
                return "G6";
            case 93:
                return "A6";
            case 95:
                return "B6";
                // ^ & * ( )
                // C#6 D#6 ...
            case 85:
                return "C#6";
            case 87:
                return "Eb6";
            case 90:
                return "F#6";
            case 92:
                return "Ab6";
            case 94:
                return "Bb6";
                
                // x y z h j H J
                // return MIDI note number for C7...B7
            case 96:
                return "C7";
            case 98:
                return "D7";
            case 100:
                return "E7";
            case 101:
                return "F7";
            case 103:
                return "G7";
            case 105:
                return "A7";
            case 107:
                return "B7";
                // - + ~ ` "
                // C#7 D#7 ...
            case 97:
                return "C#7";
            case 99:
                return "Eb7";
            case 102:
                return "F#7";
            case 104:
                return "Ab7";
            case 106:
                return "Bb7";
                //C8 last key on piano
            case 108:
                return "C8";
                
                
            default:
                return "C4";
        }
    }
    
    void notenames2asciinames (string notes) {
        map<string,int>::iterator map_it;
        stringstream lineStream (notes);
        string cell;
        vector<int> midinotes;
        while (getline(lineStream, cell, ' ')) {
            map_it = notename_midi_map.find(cell);
            if (map_it != notename_midi_map.end()) {
                midinotes.push_back (map_it->second);
                cout << char(midi_to_asciipitch (map_it->second));
            }
        }
        cout << endl;
        for (vector<int>::iterator it=midinotes.begin() ; it!=midinotes.end(); ++it) {
            cout << *it;
            if (it+1 != midinotes.end())
                cout << ", ";
        }
        cout << endl;
    }
    
    string notenames2midinotes (string notes) {
        map<string,int>::iterator map_it;
        stringstream lineStream (notes);
        string cell;
        vector<int> midinotes;
        while (getline(lineStream, cell, ' ')) {
            map_it = notename_midi_map.find(cell);
            if (map_it != notename_midi_map.end())
                midinotes.push_back (map_it->second);
        }
        
        string note_string;
        for (vector<int>::iterator it=midinotes.begin() ; it!=midinotes.end(); ++it) {
            note_string += to_string(*it);
            if (it+1 != midinotes.end())
                note_string += ", ";
        }
        
        return note_string;
    }
    
    string midinotes2notenames (string midi) {
        stringstream lineStream (midi);
        string cell;
        vector<string> notes;
        vector<int> m;
        while (getline(lineStream, cell, ',')) {
            int midivalue = atoi (cell.c_str ());
            m.push_back (midivalue);
            notes.push_back (midi_to_notename (midivalue));
        }
        string note_string;
        for (vector<string>::iterator it=notes.begin() ; it!=notes.end(); ++it) {
            note_string += *it;
            if (it+1 != notes.end())
                note_string += ", ";
        }
        note_string += "\n$ ";
        if (m.size () > 1) {
            int first = m.front ();
            for (vector<int>::iterator it=m.begin()+1 ; it!=m.end(); ++it) {
                note_string += to_string(abs (first - *it)) + ", ";
                first = *it;
            }
        }
        return note_string;
    }

    string midichords2notenames (string midi) {
        stringstream lineStream (midi);
        string cell;
        vector<string> notes;
        vector<int> m;
        while (getline(lineStream, cell, ':')) {
            int midivalue = atoi (cell.c_str ());
            m.push_back (midivalue);
            notes.push_back (midi_to_notename (midivalue));
        }
        string note_string;
        for (vector<string>::iterator it=notes.begin() ; it!=notes.end(); ++it) {
            note_string += *it;
            if (it+1 != notes.end())
                note_string += ", ";
        }
        note_string += "\n$ ";
        if (m.size () > 1) {
            int first = m.front ();
            for (vector<int>::iterator it=m.begin()+1 ; it!=m.end(); ++it) {
                note_string += to_string(abs (first - *it)) + ", ";
                first = *it;
            }
        }
        return note_string;
    }

};
#endif // __Modul_h__ 
 

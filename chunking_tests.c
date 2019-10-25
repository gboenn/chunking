#include <Modul.h>
#include <TextIO.h>

void chunking_tests () {
    Modul mdl;
//	if (ms == modulTable[kPropSeries])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    proportion_series (89, 8, 1.618);
    cout << "Usage: chunking -m propseries <chunk to divide iteratively: float> <number of iterations: int> <divisor: float>" << endl;
    
//	if (ms == modulTable[kPartition])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    partition (30, 0, 1, 31, 30, 2, 0, 3, 0);

    cout << "Usage: chunking -m partition <n> <flag parts-must-be-prime> <flag parts-not-’1’>" << endl;
    cout << "<max prime in parts> <max int in parts>" << endl;
    cout << "<min int in parts>" << endl;
    cout << "<int to add to all parts>" << endl;
    cout << "<number of distinct parts, 0 := print all partitions>" << endl;
    cout << "<flag for p. with all parts being equal>" << endl;

//	if (ms == modulTable[kanaphrases])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    StringToFile f("rstrings.txt");
    f.Append("IXIIX");
    f.Append("--::I");
    f.Append(">HII");
    
    mdl.AnalysePhrases("rstrings.txt", 1, 100, 1);

    cout << "usage: chunking -m anaphrases <shorthand.txt>" << endl;
    cout << "or: chunking -m anaphrases <shorthand.txt> <min beats> <max beats>" << endl;

//    if (ms == modulTable[kprintphrases])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    f.Append("IXIIX");
    f.Append("--::I");
    f.Append(">HII");
    StringToFile f2("midipitches.txt");
    f2.Append("60,67,69,65,67,64,62,65,64,60");
    mdl.PrintPhrases ("rstrings.txt", "midipitches.txt", 150, 1);

    cout << "Usage: chunking -m printphrases <file1: shorthand notation> <file2: midi pitches> <int: bpm (optional)> <int: flag (optional)>" << endl;

//	if (ms == modulTable[kintstrings])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    StringToFile f3("irstrings1.txt");
    f3.Append("2,2,3,1,1,2");
    f3.Append("2,1,1,2,3,2");
    StringToFile f4("irstrings2.txt");
    f4.Append("2,2,2,1,1,3");
    f4.Append("2,1,1,2,1,2,2");
    mdl.AnalyseIntegerRhythmStrings ("irstrings1.txt", "irstrings2.txt");

    cout << "Usage: chunking -m intstrings <file1> <file2>" << endl;
    cout << "Input: Two ascii text files with lines of comma-separated rhythms in integer distance notation." << endl;
    cout << "Output: various distance measurements between all pairs of rhythms be- tween file1 and file2" << endl;

//	if (ms == modulTable[kfarey2binary])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.FareyToBinaryRhythm (7, 4, 0);
    cout << "Usage: chunking -m farey2binary <Farey Sequence n> <Digestibility threshold f> <int flag activates smooth filter 2 3>" << endl;

#if 0
//	if (ms == modulTable[kdivisors])
        // lists all divisors of n in {1,2,3,...,499}
		mdl.Divisors ();

//	if (ms == modulTable[kpermutations])
        // Outputs the Christoffel words and BWTs of ratios built by the first twenty-one 7-smooth numbers.
		mdl.Permutations ();

//	if (ms == modulTable[kpermutations2])
		mdl.Permutations2 ();
#endif
    
//	if (ms == modulTable[kfpoly])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.FareyPolyrhythm (20, 5, 4);
    cout << "Usage: chunking -m fpoly <Farey Seq. N> <first subdivision> <second subdivision>" << endl;

//    if (ms == modulTable[kprintfarey])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.PrintFareySeq (4);

    cout << "Usage: chunking -m printfarey <Farey Sequence n>" << endl;
    cout << "Prints all members of Farey Sequence n, " << endl;
    cout << "with each ratio also interpreted as slope of Christoffel word," << endl;
    cout << "including bit pattern operations, BWT, and shorthand notations." << endl;


//	if (ms == modulTable[kcrhythm])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.CRhythm (3, 4);

    cout << "Usage: chunking -m crhythm <m: integer> <n: integer>" << endl;
    cout << "Outputs a Christoffel word C(m,n), its ancestors in the Stern-Brocot tree, and various other transformations." << endl;



//	if (ms == modulTable[kcrhythm2])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.CompareCRhythms (3, 4, 5, 6);

    cout << "Usage: chunking -m compc <m1: int> <n1: int> <m2: int> <n2: int>" << endl;
    cout << "Compares two Crhistoffel rhythms with each other to find intersections of their inverse Burrows-Wheeler matrix, i.e. comparing all of their possible cyclic substrings." << endl;


//	if (ms == modulTable[klookup])
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.LookupRhythm ("IX");

    cout << "Usage: chunking -m lookup <shorthand pattern>" << endl;
    cout << "Searches all Christoffel words C(m,n), from C(1,1) to C(20,20), for a matching rhythmic pattern" << endl;

#if 0
//	if (ms == modulTable[kloadpartition]) {
	  mdl.LoadPartitions (s1, i1);
#endif
    
//	if (ms == modulTable[kgetpartition]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.GetPartition (40, 3, 1);

    cout << "Usage: chunking -m getpart <n: integer> <k: integer> <1>" << endl;
    cout << "returns the partition of n into k unique parts with the lowest standard deviation," << endl;
    cout << "with n <= 120 and k <= 5. The output format is: n part_1 part_2 ... part_k mean k" << endl;


//	if (ms == modulTable[ksentence]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    cout << "Usage: chunking -m sentence n k" << endl;
    cout << "with n = number of pulses <= 120," << endl;
    cout << "and k = number of distinct parts <= 5" << endl;
    mdl.StartSentence (60, 3);
    mdl.PrintPhrases("sentence_60_3.txt", "midipitches.txt", 150, 1);
    
    
//    if (ms == modulTable[kbwt]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.BWT ("$1564532431");
    cout << "Usage: chunking -m bwt <string>" << endl;

    
//    if (ms == modulTable[kbwtmel]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.BWTmelodies ("c6ef", 0, "g");
    cout << "Usage: chunking -m bwtmel <string of ascii notes> <integer denoting semitones for transposition> <optional: character denoting a type of transformation (g (original),u (inversion),k (retrograde),q (retrograde of inversion)>" << endl;
    cout << "Example: chunking -m bwtmel 'c6ef' 0 g" << endl;

    
//    if (ms == modulTable[knotenames]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.notenames2asciinames ("C4 C#4 D4 D#4");

    cout << "Usage: chunking -m notenames <string>" << endl;
    cout << "Returns: ascii code for pitches as one character per pitch, useful for Burrows-Wheeler." << endl;
    cout << "Returns also a list of MIDI note numbers." << endl;
    cout << "Example: chunking -m notenames 'C4 C#4 D4 D#4'" << endl;
    cout << "c6d7" << endl;
    cout << "60, 61, 62, 63" << endl;

    
//    if (ms == modulTable[knotes2midi]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    StringToFile notes("notelines.txt");
    notes.Append ("C4 C4 G4 G4 A4 A4 G4");
    notes.Append ("F4 F4 E4 E4 D4 D4 C4");
    mdl.notenames2midinotes ("notelines.txt");
    cout << "Usage: chunking -m notes2midi <file name>" << endl;
    cout << "Input: Name of a text file containing lines of note names, for example:" << endl;
    cout << "C4 C4 G4 G4 A4 A4 G4" << endl;
    cout << "F4 F4 E4 E4 D4 D4 C4" << endl;
    cout << "Output: Lines of comma-separated Midi note numbers, for example:" << endl;
    cout << "60, 60, 67, 67, 69, 69, 67" << endl;
    cout << "65, 65, 64, 64, 62, 62, 60" << endl;
    cout << "After being saved as a file, the output can be used together with printphrases to merge the pitches with rhythmic phrases." << endl;

//    if (ms == modulTable[kmidi2notes]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    StringToFile notes2("notelines2.txt");
    notes2.Append ("60, 60, 67, 67, 69, 69, 67");
    notes2.Append ("65, 65, 64, 64, 62, 62, 60");
    mdl.midinotes2notenames ("notelines2.txt");
    cout << "Usage: chunking -m midi2notes <file name>" << endl;
    cout << "Input: Name of a text file containing lines of comma-separated Midi note numbers, for example:" << endl;
    cout << "60, 60, 67, 67, 69, 69, 67" << endl;
    cout << "65, 65, 64, 64, 62, 62, 60" << endl;
    cout << "Output: Lines of note names, for example:" << endl;
    cout << "C4 C4 G4 G4 A4 A4 G4" << endl;
    cout << "F4 F4 E4 E4 D4 D4 C4" << endl;



//    if (ms == modulTable[kbwtpath]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    StringToFile shnd("bwtrows.txt");
    shnd.Append ("14, 10, 7, 5, 3, 1");
    
    mdl.iBWTpathway ("IXIIXIIIXX", "bwtrows.txt");

    cout << "Usage: chunking -m bwtpath <shorthand string> <file name>" << endl;
    cout << "Input: 1. A string of rhythm shorthand, for example:" << endl;
    cout << "'IXIIXIIIXX'" << endl;
    cout << "Internally, the algorithm converts the shorthand into a word over the alphabet {a,b}, " << endl;
    cout << "where 'a' represents a note onset, and 'b' represents inter-onset pulses" << endl;
    cout << "2. A file containing a random list of row numbers of the inverse Burrows Wheeler (iBWT) matrix." << endl;
    cout << "The iBWT matrix has as many rows as the word has characters." << endl;
    cout << "An example file of row numbers may contain: 14, 10, 7, 5, 3, 1." << endl;

   
//    if (ms == modulTable[kbwtmatrix]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.iBWTspecific ("IXIIX", 5, 0);

    cout << "Usage: chunking -m bwtmatrix <shorthand string>" << endl;
    cout << "Usage: chunking -m bwtmatrix <shorthand string> <integer: length>" << endl;

    
//    if (ms == modulTable[kdb]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.DB_search ("IXII%");
    cout << "Usage: chunking -m db <search string in shorthand notation>" << endl;
    cout << "The search string may contain '%' for extended search." << endl;

    #if 0
    //    if (ms == modulTable[kdb_insert]) {

    mdl.DB_insert_from_file (s1,s2,s3,s4);

    cout << "Usage: chunking -m dbinsert <filename> <name> <origin> <composer>" << endl;
    cout << "File containing shorthand notation. One line creates new entry in the table rhythm of rhy.db." << endl;
    #endif

    //    if (ms == modulTable[kshortening]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    string result = mdl.Shortening ("IXI-I:", 1);
    cout << result << endl;
    cout << "Usage: chunking -m shortening <shorthand string> <from_top? 0 (no) or 1 (yes)>" << endl;


    //    if (ms == modulTable[ksproc]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.ShorteningProcess (":IH:I>I");
    cout << "Usage: chunking -m sproc <shorthand string>" << endl;


    //    if (ms == modulTable[kjump]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    string input = ":IH::X>I";
    cout << "input: " << input << endl;
    result = mdl.Jumping (input, 2, 2, 1);
    cout << result << endl;
    cout << "Usage: chunking -m jump <shorthand string> <n_symbols int> <k_times int> <from_start? 0 (no) or 1 (yes)>" << endl;

    //    if (ms == modulTable[kmutate]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.Mutation (input, 2);
    cout << result << endl;
    result = mdl.Mutation (result, 2);
    cout << result << endl;
    result = mdl.Mutation (result, 2);
    cout << result << endl;
    cout << "Usage: chunking -m mutate <shorthand string> <k_times int>" << endl;

    //    if (ms == modulTable[kswap]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.Swap (input, 2);
    cout << result << endl;
    result = mdl.Swap (result, 2);
    cout << result << endl;
    result = mdl.Swap (result, 2);
    cout << result << endl;
    cout << "Usage: chunking -m swap <shorthand string> <k_times int>" << endl;


    //    if (ms == modulTable[ksilence]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.Silence (input, 0, 2);
    cout << result << endl;
    cout << "Usage: chunking -m silence <shorthand string> <from_pos int> <to_pos int>" << endl;
    


    //    if (ms == modulTable[kproc2shapes]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.ProcessToShapes (input, 0);
    cout << result << endl;
    result = mdl.ProcessToShapes (input, 1);
    cout << result << endl;
    result = mdl.ProcessToShapes (input, 2);
    cout << result << endl;
    result = mdl.ProcessToShapes (input, 3);
    cout << result << endl;
    cout << "Usage: chunking -m shape <shorthand string> <flag int [0-3]>" << endl;
    

    //    if (ms == modulTable[kfragment]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.Fragment (input);
    cout << result << endl;
    result = mdl.Fragment (input);
    cout << result << endl;
    result = mdl.Fragment (input);
    cout << result << endl;
    cout << "Usage: chunking -m fragment <shorthand string>" << endl;


    //    if (ms == modulTable[krotate]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.Rotation (input);
    cout << result << endl;
    cout << "Usage: chunking -m rotate <shorthand string>" << endl;

    //    if (ms == modulTable[kfragrotate]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.FragmentRotation (input);
    cout << result << endl;
    cout << "Usage: chunking -m fragrotate <shorthand string>" << endl;

    //    if (ms == modulTable[kcompose]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    mdl.Compose (input);
    cout << "Usage: chunking -m compose <shorthand string>" << endl;

    //    if (ms == modulTable[kreverse]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    result = mdl.Reverse (input);
    cout << result << endl;
    cout << "Usage: chunking -m reverse <shorthand string>" << endl;

    //    if (ms == modulTable[kaddrep]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    mdl.AddAndRepeat (input, 2, 3);
    cout << "Usage: chunking -m addrep <shorthand string> <n int> <k int>" << endl;

    //    if (ms == modulTable[krepeat]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    mdl.Repeat (input, 2);
    cout << "Usage: chunking -m repeat <shorthand string> <n int>" << endl;

    //    if (ms == modulTable[knest]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    input = "I:>:-::I";
    cout << "input: " << input << endl;
    mdl.Nest (input);
    mdl.Nest (input);
    cout << "Demonstration of recursive call: return Mutation(Mutation(Mutation(input,1), 1), 1);" << endl;
    //    if (ms == modulTable[kbendf]) {
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    mdl.BendFarey (5);
    cout << "Usage: chunking -m bendf <farey_number int>" << endl;
    cout << "///////////////////////////// TEST ////////////////////////////////////////////" << endl;
    StringToFile np("snmr_new_parser.txt");
    np.Append("[4H~IH~IH~IH~I]");
    np.Append("IIII");
    np.Append("[4W~IW~IW~IW~I]");
    np.Append("----");
    np.Append("[5HHHHH]");
    np.Append("[5H~IH~IH~IH~IH~I]");
    np.Append("[5WWWWW]");
    np.Append("IIIII");
    StringToFile npp("snmr_new_parser_pitches.txt");
    npp.Append("60, 60:67, 60:67:71, 74");
    npp.Append("76, 67:69, 69, 76");
    npp.Append("77, 65, 65:67, 64");
    npp.Append("62");
    mdl.Translate_Shorthand ("snmr_new_parser.txt", "snmr_new_parser_pitches.txt");
}

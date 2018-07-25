///////////////////////////////////////////
// Christoffel.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __christoffel_h__
#define __christoffel_h__

#include "DList.h"

class Christoffel
{
// input: words across alphabet of {a,b}
public:
    Christoffel () { word = ""; bwt_word = ""; init (); }
    Christoffel (string input) {word = input; init (); calculate_words (); minb = 0; maxb = word.length(); }
    ~Christoffel () {cleanup ();}
    
    void init () {
        bin_word1 = new DList<int>;
        bin_word2 = new DList<int>;
        bin_word3 = new DList<int>;
        bin_word4 = new DList<int>;
    
    }
    
    void cleanup () {
        
        bin_word1->destroy ();
        bin_word2->destroy ();
        bin_word3->destroy ();
        bin_word4->destroy ();
        delete bin_word1;
        delete bin_word2;
        delete bin_word3;
        delete bin_word4;
        
    }
    
    void erase () {
        
        bin_word1->destroy ();
        bin_word2->destroy ();
        bin_word3->destroy ();
        bin_word4->destroy ();
    }
    
    string CheckWord (string input);
    void SetWord (string input) {
        string temp = CheckWord (input);
        word = temp;
        minb = 0; maxb = word.length();
        calculate_words ();
    }
    
    void SetAnyWord (string input) {
        string temp = CheckWord (input);
        word = temp;
        minb = 0; maxb = word.length();
        calculate_words ();
    }
    
    void SetAsciiPitchWord (string input) {
        //string temp = CheckWord (input);
        word = input;
        minb = 0; maxb = word.length();
        calculate_words ();
    }

    string GetWord () const { return word; }
    DLink<int>* GetBin1 () const { return bin_word1->first (); }
    DLink<int>* GetBin2 () const { return bin_word2->first (); }
    DLink<int>* GetBin3 () const { return bin_word3->first (); }
    DLink<int>* GetBin4 () const { return bin_word4->first (); }
    
    void calculate_words ();
    void print_words ();
    
    int length_word () { return word.length (); }
    string rotate (int i); // roates the word to the right by i places
    string burrows_wheeler_trans (); // returns the BWT string
    string burrows_wheeler_trans2 (); // returns the BWT string
    string burrows_wheeler_inverse (int k); // returns the concatenated strings of the inverse BWT procedure at step i
    string burrows_wheeler_inverse2 (int k);
    void display_all ();
    string word_to_rhythm_chunks (string w);
    string word_to_rhythm_chunks3 (string w);
    void word_to_partition (string w);

    string display_all2 (int j);
    vector<string> GetShorthand () { return shorthand; }
    
    int count_beats_in_word (string w);
    void SetMinMaxBeatCount (int min, int max) { minb = min; maxb=max;}
    void SetBWTword (string word) { bwt_word = word; }
    string burrows_wheeler_inverse_substring (int k, int l);
    
private:
    string word;
    string bwt_word;
    DList<int>* bin_word1;
    DList<int>* bin_word2;
    DList<int>* bin_word3;
    DList<int>* bin_word4;
    vector<string> shorthand;
    int minb; int maxb;
    
};

#endif // __christoffel_h__

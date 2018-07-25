///////////////////////////////////////////
// Christoffel.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "Christoffel.h"


string Christoffel::CheckWord (string input) {
    string temp = "";
    bool binary = false;
    string::iterator it=input.begin();
    for (; it!=input.end(); ++it)
    {
        if (char(*it) == '1' || char(*it) == '0') {
            binary = true;
        }
    }
    
    if (binary) {
        it=input.begin();
        for (; it!=input.end(); ++it) {
            if (char(*it) == '1') {
                temp = temp + "a";
            }
            if (char(*it) == '0') {
                temp = temp + "b";
            }
            
        }
    }
    
    if (binary) {
        return temp;
    } else {
        return input;
    }
}


void Christoffel::calculate_words () {
    
    this->erase ();
    string::iterator it=word.begin();
    
    bool first = true;
    char last = 'z';
    for (; it!=word.end(); ++it)
    {
        if (char(*it) != ' ') { //ignore empty spaces
            //cout << *it;
            if (char(*it) == 'a') {
                bin_word1->append (new int(1));
                bin_word2->append (new int(0));
            }
            if (char(*it) == 'b') {
                bin_word1->append (new int(0));
                bin_word2->append (new int(1));
            }
            
            if (first) {
                bin_word3->append (new int(1));
                bin_word4->append (new int(0));
                if (char(*it) == 'a')
                    last = 'a';
                else
                    last = 'b';
                first = false;
            }
            
            else
            
            {
                
                if (char(*it) == 'a' && last == 'a') {
                    bin_word3->append (new int(0));
                    bin_word4->append (new int(1));
                }
                else if (char(*it) == 'a' && last == 'b') {
                    bin_word3->append (new int(1));
                    bin_word4->append (new int(0));
                    last = 'a';
                }
                else if (char(*it) == 'b' && last == 'b') {
                    bin_word3->append (new int(0));
                    bin_word4->append (new int(1));
                }
                else if (char(*it) == 'b' && last == 'a') {
                    bin_word3->append (new int(1));
                    bin_word4->append (new int(0));
                    last = 'b';
                }
                
                
                
            }
            
            
        }
    }
}


void Christoffel::print_words () {
    
    cout << word << endl;
    cout << "---------------------------" << endl;
    DLink<int>* l = GetBin1 ();
    for (; l != NULL; l = l->next) {
        
        cout << (*l->data) << ",";
    }
    cout << endl;
    cout << "---------------------------" << endl;
    l = GetBin2 ();
    for (; l != NULL; l = l->next) {
        
        cout << (*l->data) << ",";
    }
    cout << endl;
    cout << "---------------------------" << endl;
    l = GetBin3 ();
    for (; l != NULL; l = l->next) {
        
        cout << (*l->data) << ",";
    }
    cout << endl;
    cout << "---------------------------" << endl;
    l = GetBin4 ();
    for (; l != NULL; l = l->next) {
        
        cout << (*l->data) << ",";
    }
    cout << endl;
    cout << "---------------------------" << endl;
}

string Christoffel::rotate (int i) {
    
    string temp = word;
    while (i > 0) {
        char last = temp.at(temp.length () - 1);
        //temp.pop_back ();
        temp.erase(temp.length()-1);
        temp = last + temp;
        --i;
    }
    return temp;
    
}

string Christoffel::burrows_wheeler_trans () {
    
    vector<string> rwords;
    int len = length_word ();
    int lenm1 = len - 1;
    if (bwt_word == "") {
        int i = 0;
        for (; i < len; i++) {
            rwords.push_back(this->rotate(i));
        }
        sort(rwords.begin(), rwords.end(), greater<string>());
    }
    
    for (vector<string>::reverse_iterator it=rwords.rbegin(); it!=rwords.rend(); ++it) {
        bwt_word = bwt_word + ((*it).at (lenm1));
    }
    
    //cout << "BWT-word: " << bwt_word << endl;
        
    return bwt_word;
    
}

string Christoffel::burrows_wheeler_trans2 () {
    
    vector<string> rwords;
    int len = length_word ();
    int lenm1 = len - 1;
    if (bwt_word == "") {
        int i = 0;
        for (; i < len; i++) {
            rwords.push_back(this->rotate(i));
        }
        sort(rwords.begin(), rwords.end(), greater<string>());
    }
    
    //cout << "BWT: ";
    for (vector<string>::reverse_iterator it=rwords.rbegin(); it!=rwords.rend(); ++it) {
        //cout << *it << ", ";
        bwt_word = bwt_word + ((*it).at (lenm1));
    }
    //cout << endl;
    //cout << "BWT-word: " << bwt_word << endl;
    
    return bwt_word;
    
}

string Christoffel::burrows_wheeler_inverse (int k) {
    
    if (bwt_word == "") {
        burrows_wheeler_trans ();
    }
    
    vector<string> iwords;
    int len = length_word ();
    int i = 0;
    
    for (; i < len; i++)
        iwords.push_back("");
    
    //shorthand.clear();

    while (k > 0) {
        for (i=0; i < len; i++) {
            string w = iwords.at(i);
            char c = bwt_word[i];
            iwords.at(i) =  c + w;
        }
        sort(iwords.rbegin(), iwords.rend(), greater<string>());
        --k;
    }
 
    vector<string> iwords2;
    for (i = 0; i < len; i++) {
        int beats = count_beats_in_word (iwords.at(i));
        if (beats >= minb && beats < maxb) {
            //cout << "include " << iwords.at(i) << endl;
            iwords2.push_back (iwords.at(i));
        }
    }
    
    len = iwords2.size();

    for (i = 0; i < len; i++) {
      shorthand.push_back (word_to_rhythm_chunks3 (iwords2.at(i)));
    }

//    for (i = 0; i < len; i++)
//        word_to_partition (iwords2.at(i));

    string bwt_i_word;
    for (i = 0; i < len; i++)
        bwt_i_word = bwt_i_word + iwords2.at(i) + ",";
    
    return bwt_i_word;
}

string Christoffel::burrows_wheeler_inverse2 (int k) {
    
    if (bwt_word == "") {
        burrows_wheeler_trans ();
    }
    
    vector<string> iwords;
    int len = length_word ();
    int i = 0;
    
    for (; i < len; i++)
        iwords.push_back("");
    
    while (k > 0) {
        for (i=0; i < len; i++) {
            string w = iwords.at(i);
            char c = bwt_word[i];
            iwords.at(i) =  c + w;
        }
        sort(iwords.rbegin(), iwords.rend(), greater<string>());
        --k;
    }
    
    //for (i = 0; i < len; i++)
    //    word_to_rhythm_chunks3 (iwords.at(i));
    
    string bwt_i_word;
    for (i = 0; i < len; i++)
        bwt_i_word = bwt_i_word + iwords.at(i) + ", ";
    
    return bwt_i_word;
}

string Christoffel::burrows_wheeler_inverse_substring (int k, int l) {
// returns the l-th substring in column k of the iBWT
    
    if (bwt_word == "") {
        burrows_wheeler_trans ();
    }
    
    vector<string> iwords;
    int len = length_word ();
    if (l > len-1) l = len - 1;
    if (l < 0) l = 0;
    
    if (k > len) k = len;
    if (k < 1) k = 1;
    
    int i = 0;
    for (; i < len; i++)
        iwords.push_back("");
    
    while (k > 0) {
        for (i=0; i < len; i++) {
            string w = iwords.at(i);
            char c = bwt_word[i];
            iwords.at(i) =  c + w;
        }
        sort(iwords.rbegin(), iwords.rend(), greater<string>());
        --k;
    }
    return iwords.at(l);
}

void Christoffel::display_all () {
    this->print_words ();
    this->burrows_wheeler_trans ();
    int len = length_word ();
    int j = 1;
    for (; j <= len; j++) {
        string temp = this->burrows_wheeler_inverse (j);
        //word_to_rhythm_chunks (temp);
        cout << "Block #" << j << endl << temp << endl;
    }
    cout << endl;
}

string Christoffel::display_all2 (int j) {
  //this->print_words ();
  //this->burrows_wheeler_trans ();
  int len = length_word ();
  string temp;
  if (j <= len) {
    temp = this->burrows_wheeler_inverse2 (j);
  }

  //  cout << "Block #" << j << endl << temp << endl;
  
  return temp;
}

/*
method to compare two Christoffel words via iBWT
have display_all2 (int j) return the temp string for block j, for each word
then, generate comparison between the two strings

stringstream ss( "1,1,1,1, or something else ,1,1,1,0" );
vector<string> result;

while( ss.good() )
{
    string substr;
    getline( ss, substr, ',' );
    result.push_back( substr );
}

splitting the strings into tokens then compare via loop

if (str1.compare(str2) == 0)
   std::cout << str1 << " is " << str2 << '\n';

count the positives

 */

void Christoffel::word_to_partition (string w) {
    
    string part = "";
    int len = w.length ();
    int acount = 0;
    int bcount = 0;
    int last_was_a = 0;
    int last_was_b = 0;
    int i = 0;
    for (; i < len; i++) {
        if (w[i] == 'a') {
            acount++;
            last_was_a = 1;
            if (last_was_b) {
                char buffer [8];
                sprintf (buffer, "%d", bcount);
                part  = part + string(buffer);
                bcount = 0;
                last_was_b = 0;
            }
        }
        else if (w[i] == 'b') {
            bcount++;
            last_was_b = 1;
            if (last_was_a) {
                char buffer [8];
                sprintf (buffer, "%d", acount);
                part  = part + string(buffer);
                acount = 0;
                last_was_a = 0;
            }
        }
    }
    
    if (last_was_b) {
        char buffer [8];
        sprintf (buffer, "%d", bcount);
        part  = part + string(buffer);
    }
    if (last_was_a) {
        char buffer [8];
        sprintf (buffer, "%d", acount);
        part  = part + string(buffer);
    }
    cout << part << endl;
    
}

string Christoffel::word_to_rhythm_chunks (string w) {
    
    string chunks = "";
    int len = w.length ();
    int len3 = len;
    
    int remainder2 = len % 2;
    int remainder3 = len % 3;
    
    if (remainder2) {
        len = len - 2;
    } else if (!remainder2) {
        len = len - 1;
    }
    else if (remainder3 == 1) {
        len3 = len3 - 2;
    }
    else if (remainder3 == 2) {
        len3 = len3 - 2;
    }
    else if (remainder3 == 0) {
        len3 = len3 - 2;
    }
    
    int i = 0;
    for (; i < len; i += 2) {
        
        char m = w[i];
        char n = w[i+1];
        
        if (m == 'a' && n == 'a')
            chunks = chunks + ": ";
        
        if (m == 'a' && n == 'b')
            chunks = chunks + "I ";
        
        if (m == 'b' && n == 'a')
            chunks = chunks + "v ";
            
        if (m == 'b' && n == 'b')
            chunks = chunks + "( I ) ";
    }
    if (remainder2) {
        char m = w[w.length()-1];
        if (m == 'a')
            chunks = chunks + ". ";
        else
            chunks = chunks + "(.) ";
    }
            
    cout << chunks << endl;
    return chunks;
}

string Christoffel::word_to_rhythm_chunks3 (string w) {
    
    string chunks = "";
    int len = w.length ();
    int len3 = len;
    
    int remainder2 = len % 2;
    int remainder3 = len % 3;
    
    if (remainder2) {
        len = len - 2;
    } else if (!remainder2) {
        len = len - 1;
    }
    else if (remainder3 == 1) {
        len3 = len3 - 2;
    }
    else if (remainder3 == 2) {
        len3 = len3 - 2;
    }
    else if (remainder3 == 0) {
        len3 = len3 - 2;
    }
    
    int i = 0;
    for (; i < len; i += 3) {
        
        char m = w[i];
        char n = w[i+1];
        char o = w[i+2];
        
        if (m == 'a' && n == 'a' && o == 'a')
            chunks = chunks + "i ";
        
        if (m == 'a' && n == 'a' && o == 'b')
            chunks = chunks + "X ";
        
        if (m == 'a' && n == 'b' && o == 'b')
            chunks = chunks + "- ";
        
        if (m == 'b' && n == 'a' && o == 'a')
            chunks = chunks + "+ ";
        
        if (m == 'b' && n == 'a' && o == 'b')
            chunks = chunks + "< ";
        
        if (m == 'b' && n == 'b' && o == 'a')
            chunks = chunks + "w ";
        
        if (m == 'a' && n == 'b' && o == 'a')
            chunks = chunks + "> ";
        
        if (m == 'b' && n == 'b' && o == 'b')
            chunks = chunks + "(-) ";
    }
    if (remainder3 == 2) {
        char m = w[w.length()-2];
        char n = w[w.length()-1];
        
        if (m == 'a' && n == 'a')
            chunks = chunks + ": ";
        
        if (m == 'a' && n == 'b')
            chunks = chunks + "I ";
        
        if (m == 'b' && n == 'a')
            chunks = chunks + "v ";
        
        if (m == 'b' && n == 'b')
            chunks = chunks + "(I) ";
    }
    if (remainder3 == 1) {
        char m = w[w.length()-1];
        if (m == 'a')
            chunks = chunks + ". ";
        else
            chunks = chunks + "(.) ";
    }
    
    //cout << chunks << endl;
    return chunks;
}


int Christoffel::count_beats_in_word (string w) {
    
    int nbeats = 0;
    int len = w.length ();
    int len3 = len;
    
    int remainder2 = len % 2;
    int remainder3 = len % 3;
    
    if (remainder2) {
        len = len - 2;
    } else if (!remainder2) {
        len = len - 1;
    }
    else if (remainder3 == 1) {
        len3 = len3 - 2;
    }
    else if (remainder3 == 2) {
        len3 = len3 - 2;
    }
    else if (remainder3 == 0) {
        len3 = len3 - 2;
    }
    
    int i = 0;
    for (; i < len; i += 3) {
        
        char m = w[i];
        char n = w[i+1];
        char o = w[i+2];
        
        if (m == 'a' && n == 'a' && o == 'a')
            nbeats += 3;
        if (m == 'a' && n == 'a' && o == 'b')
            nbeats += 2;
        if (m == 'a' && n == 'b' && o == 'b')
            nbeats += 1;
        if (m == 'b' && n == 'a' && o == 'a')
            nbeats += 2;
        if (m == 'b' && n == 'a' && o == 'b')
            nbeats += 1;
        if (m == 'b' && n == 'b' && o == 'a')
            nbeats += 1;
        if (m == 'a' && n == 'b' && o == 'a')
            nbeats += 2;
        if (m == 'b' && n == 'b' && o == 'b')
            ;
    }
    if (remainder3 == 2) {
        char m = w[w.length()-2];
        char n = w[w.length()-1];
        
        if (m == 'a' && n == 'a')
            nbeats += 2;
        
        if (m == 'a' && n == 'b')
            nbeats += 1;
        
        if (m == 'b' && n == 'a')
            nbeats += 1;
        
        if (m == 'b' && n == 'b')
            ;
    }
    if (remainder3 == 1) {
        char m = w[w.length()-1];
        if (m == 'a')
            nbeats += 1;
        else
            ;
    }
    
    //cout << nbeats << endl;
    return nbeats;
}



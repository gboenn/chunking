// Mutations.cpp

#ifndef __Mutations_h__
#include "Mutations.h"
#endif

#include <random>
#include <sstream>

string Mutations::Jumping (string rhythm, int n, int k, int flag) {
    if (n == 0) {
        cout << "$ n must be positive." << endl;
        return rhythm;
    }
    size_t rlen = rhythm.length ();
    string output;
    if (n < 0) n *= -1;
    if (n > int(rlen)) {
        n = rlen;
        int i = 0;
        for (; i < k; i++) {
            output += '\n';
            output += rhythm;
        }
    }
    else {
        if (flag == 0) {
            int i = 0;
            output = rhythm;
            for (; i < k; i++) {
                output += '\n';
                output += rhythm.substr(rlen-n, n);
            }
        } else {
            int i = 0;
            for (; i < k; i++) {
                output += rhythm.substr(0, n);
                output += '\n';
            }
            output += rhythm;
        }
    }
    if (flag == 0) {
        cout << "$ jumping needle for " << k << " times the last " << n << " symbols." << endl;
    } else {
        cout << "$ jumping needle for " << k << " times the first " << n << " symbols." << endl;
    }
    //cout << output << endl;
    return output;
}

string Mutations::Fragment (string rhythm) {
    size_t rlen = rhythm.length ();
    if (rlen == 1)
        return rhythm;
    vector <int> mutpos;
    srand (time(NULL));
    
    int lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, lenm1);
    int r = dist(md);
    mutpos.push_back(r);
    
    while (1) {
        int r2 = dist(md);
        if (r != r2) {
            mutpos.push_back(r2);
            break;
        }
    }
    
    sort (mutpos.begin (), mutpos.end ());
    //cout << "Fragment: " << mutpos.at(0) << " " << mutpos.at(1) << endl;
    string result = rhythm.substr (mutpos.at(0), mutpos.at(1));
    //cout << "Fragment result: " << result << endl;
    return result;
}

string Mutations::FragmentRotation (string rhythm) {
    string temp = Fragment (rhythm);
    temp = Rotation (temp);
    //cout << temp << endl;
    return temp;
}

string Mutations::Rotation (string rhythm) {
    size_t rlen = rhythm.length ();
    if (rlen == 1)
        return rhythm;
    int lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, lenm1);
    int r = dist(md);
    
    string temp = rhythm;
    while (--r >= 0) {
        char last = temp.at(temp.length () - 1);
        temp.erase(temp.length()-1);
        temp = last + temp;
    }
    if (temp == rhythm) {
        char last = temp.at(temp.length () - 1);
        temp.erase(temp.length()-1);
        temp = last + temp;
    }
    //cout << temp << endl;
    return temp;
    
}

string Mutations::Mutation (string rhythm, int n) {
    // random mutations, n = number of mutations
    
    size_t rlen = rhythm.length ();
    vector <int> mutpos;
    //srand (time(NULL));
    int m = n;
    int lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, lenm1);
    while (--m >= 0) {
        int r = dist(md);
        mutpos.push_back(r);
    }
    
    int i = 0;
    cout << "$ mutations at positions: ";
    for (; i < n; i++) {
        cout << mutpos.at(i) << ", ";
    }
    cout << endl;
    string dual = "I:v";
    int dual_length = dual.length ();
    string ternary = "-iX><w";
    int ternary_length = ternary.length ();
    string quaternary = "H!";
    const int quat_repl_length = 8;
    string quat_repl[quat_repl_length] = {"!", "H", "::", "II", "-.", ":I", "I:", ".I."};
    i = 0;
    for (string::iterator it=rhythm.begin(); it!=rhythm.end(); ++it, i++) {
        int k = 0;
        int flag = 0;
        for (; k < n; k++) {
            if (i == mutpos.at(k)) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            for (string::iterator it2=dual.begin(); it2!=dual.end(); ++it2) {
                if (int(*it2) == int(*it)) {
                    char c = *it;
                    while (1) {
                        c = dual[rand() % dual_length];
                        if (int(c) != int(*it))
                            break;
                    }
                    rhythm[i] = c;
                    break;
                }
            }
            for (string::iterator it2=quaternary.begin(); it2!=quaternary.end(); ++it2) {
                if (int(*it2) == int(*it)) {
                    string temp = quat_repl[rand() % quat_repl_length];
                    rhythm.replace (i,  1,  temp, 0, string::npos);
                    break;
                }
            }
            for (string::iterator it2=ternary.begin(); it2!=ternary.end(); ++it2) {
                if (int(*it2) == int(*it)) {
                    char c = *it;
                    while (1) {
                        c = ternary[rand() % ternary_length];
                        if (int(c) != int(*it))
                            break;
                    }
                    rhythm[i] = c;
                    break;
                }
            }
        }
    }
    
//    cout << "Mutation result: " << rhythm << endl;
    return rhythm;
}

string Mutations::Swap (string rhythm, int n) {
    //random swap(s), n = number of swaps
    size_t rlen = rhythm.length ();
    vector <int> mutpos;
    srand (time(NULL));
    int m = n;
    int lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, lenm1);
    while (--m >= 0) {
        int r = dist(md);
        mutpos.push_back(r);
    }
    int i = 0;
    cout << "$ swapping at positions: ";
    for (; i < n; i++) {
        cout << mutpos.at(i) << ", ";
    }
    cout << endl;
    for (i=0; i < n; i++) {
        char c = rhythm[mutpos.at(i)];
        int swapindex = mutpos.at(i)+1;
        if (swapindex > lenm1) swapindex = 0;
        rhythm[mutpos.at(i)] = rhythm[swapindex];
        rhythm[swapindex] = c;
        //cout << "swap at pos: " << i << endl;
    }
    
    //cout << rhythm << endl;
    return rhythm;
}

string Mutations::Silence (string rhythm, int n, int k) {
    // renders a silence with symbols between pos n and k
    
    // check whether there is already silence in the string
    // if yes, then remove the brackets
    int i = 0;
    for (string::iterator it=rhythm.begin(); it!=rhythm.end(); ++it, i++) {
        if (int(*it) == 40 || int(*it) == 41) // == '(' or ')'
            rhythm.erase(rhythm.begin()+i);
    }
    // check boundaries and assert (n<k)
    // k can be >= list length in which case the right bracket is simply appended
    size_t rlen = rhythm.length ();
    if (k == n) {
        cout << "$ " << rhythm << " has " << rlen << " characters. <from_pos> and <to_pos> should be different." << endl;
        return rhythm;
    }
    if (k < n) {
        cout << "$ " << rhythm << " has " << rlen << " characters. <from_pos> should be smaller than <to_pos>." << endl;
        return rhythm;
    }
    if (n < 0) n = 0;
    if (n > rlen - 1) n = rlen - 1;
    i = 0;
    for (string::iterator it=rhythm.begin(); it!=rhythm.end(); ++it, i++) {
        if (i == n)
            rhythm.insert(it, '(');
        if (i == k+1) // insert is always before index, and since we already inserted a char (n<k)...
            rhythm.insert(it, ')');
    }
    if (k >= rlen)
        rhythm.push_back(')'); // the above loop cannot go past the list
    
    //cout << rhythm << endl;
    return rhythm;
}

string Mutations::ProcessToShapes (string rhythm, int flag) {
    string result = "";
    //string temp = rhythm;
    vector<string> rev;
    int i, len;
    switch (flag) {
        case 0: // hourglass
            while (!rhythm.empty ()) {
                result += rhythm;
                rev.push_back(rhythm);
                result += '\n';
                rhythm.pop_back ();
            }
            
            len = rev.size ();
            i = len - 2;
            for (; i > -1; i--) {
                result += rev.at(i);
                result += '\n';
            }
            break;
        case 1: // tail
            while (!rhythm.empty ()) {
                result += rhythm;
                result += '\n';
                rhythm.pop_back ();
            }
            break;
        case 2: // river
            while (!rhythm.empty ()) {
                rev.push_back(rhythm);
                rhythm.pop_back ();
            }
            len = rev.size ();
            i = len - 1;
            for (; i > -1; i--) {
                result += rev.at(i);
                result += '\n';
            }
            break;
        case 3: // barrell
            while (!rhythm.empty ()) {
                rev.push_back(rhythm);
                rhythm.pop_back ();
            }
            len = rev.size ();
            i = len - 1;
            for (; i > -1; i--) {
                result += rev.at(i);
                result += '\n';
            }
            for (i = 1; i < len; i++) {
                result += rev.at(i);
                result += '\n';
            }
            break;
            
        default:
            break;
            
    }
    //cout << result;
    return result;
}

string Mutations::Reverse (string rhythm) {
        vector<float> p;
        size_t found = rhythm.find (",");
        if (found != string::npos) {
            stringstream aline (rhythm);
            string cell;
            while (getline (aline, cell, ',')) {
                p.push_back (atof (cell.c_str()));
            }
            stringstream prev;
            int len = p.size ();
            while (--len > -1)
                prev << p[len] << ",";
            return prev.str ();
        } else {
            reverse(rhythm.begin (), rhythm.end ());
            return rhythm;
        }
}

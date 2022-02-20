// Mutations.cpp

#ifndef __Mutations_h__
#include "Mutations.h"
#endif

#ifndef __RhythmParser_h__
#include "RhythmParser.h"
#endif


#include <random>
#include <sstream>

string Mutations::Jumping (string rhythm, unsigned long n, int k, int flag) {
    if (n == 0) {
        cout << "$ n must be positive." << endl;
        return rhythm;
    }
    size_t rlen = rhythm.length ();
    string output;
//    if (n < 0) n *= -1;
    if (n > rlen) {
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
    string result = "";
    vector<unsigned long> vopenb;
    vector<unsigned long> vclosb;
    vector<unsigned long> vopens;
    vector<unsigned long> vcloss;
    vector<vector<unsigned long>> vunits;
    std::size_t num_symb = vrh.size ();
    string e = vrh.back();
    if (e == "newline")
        num_symb--;
    
    // unbalanced brackets, [ or (, cause parse errors earlier
    // finding out where the outer bracket pairs are []
    for (std::size_t i = 0; i < num_symb; i++) {
        if (vrh[i] == "[") vopenb.push_back(i);
    }
    // with knowledge of the opening brackets, find the closing brackets
    for (auto it = vopenb.begin() ; it != vopenb.end(); ++it) {
        vclosb.push_back (CloseBracketInd (*it));
    }
    
    // finding the pos of the silence brackets ()
    for (std::size_t i = 0; i < num_symb; i++) {
        if (vrh[i] == "(") vopens.push_back(i);
    }
    for (auto it = vopens.begin(); it != vopens.end(); ++it) {
        vcloss.push_back (CloseSilenceBracketInd (*it));
    }
    
//    cout << "non-nested square brackets:" << endl;
    unsigned long last_closed = 0;
    for (auto it = vopenb.begin(), it2 = vclosb.begin(); it != vopenb.end(); ++it, ++it2) {
        unsigned long openb = *it;
        if (openb == 0 || openb > last_closed) {
            vector<unsigned long> v;
            v.push_back(*it);
            v.push_back(*it2);
            vunits.push_back(v);
        }
        last_closed = *it2;
    }
//    for (auto it = vunits.begin(); it != vunits.end(); ++it) {
//        cout << (*it)[0] << ", " << (*it)[1] << endl;
//    }
    
//    cout << "with silence brackets outside square brackets:" << endl;
    for (auto it = vopens.begin(), it2 = vcloss.begin(); it != vopens.end(); ++it, ++it2) {
        int flag = 0;
        for (auto vt = vunits.begin(); vt != vunits.end(); ++vt) {
            if (*it > (*vt)[0] && *it < (*vt)[1]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            vector<unsigned long> v;
            v.push_back(*it);
            v.push_back(*it2);
            vunits.push_back(v);
        }
    }
    
    if (vunits.size() == 0) {
        // if rhythm has no brackets at all, then breaking it up into
        // single chars
//        cout << "should be 1: " << num_symb << endl;
        rhythm = vrh[0];
        vrh.clear();
        for (auto rt = rhythm.begin(); rt != rhythm.end(); ++rt) {
            string s;
            s += (*rt);
            vrh.push_back(s);
        }
        num_symb = vrh.size ();
//        for (int i = 0; i < num_symb; i++) {
//            cout << vrh[i] << endl;
//        }
    }

//    for (auto it = vunits.begin(); it != vunits.end(); ++it) {
//        cout << (*it)[0] << ", " << (*it)[1] << endl;
//    }
//
    
//    cout << "with free items:" << endl;
    // finding the pos of all patterns outside all brackets
    for (std::size_t i = 0; i < num_symb; i++) {
        int flag = 0;
        if (vrh[i] == "~") {
            // ignoring the ~ ties
//            continue;
        }
        for (auto vt = vunits.begin(); vt != vunits.end(); ++vt) {
            if ((*vt).size() == 2){
                if (i >= (*vt)[0] && i <= (*vt)[1]) {
                    flag = 1;
                    break;
                }
            } else {
                if (i == (*vt)[0]) {
                    flag = 1;
                    break;
                }
            }
        }
        if (!flag) {
            vector<unsigned long> v;
            v.push_back(i);
            vunits.push_back(v);
        }
    }
    sort (vunits.begin(), vunits.end());
//    for (auto it = vunits.begin(); it != vunits.end(); ++it) {
//        if ((*it).size() == 2){
//            cout << (*it)[0] << ", " << (*it)[1] << endl;
//        } else {
//            cout << (*it)[0] << endl;
//        }
//    }

    // generate two random positions
    size_t rlen = vunits.size ();
    vector <int> mutpos;
    srand (static_cast<unsigned int>(time(NULL)));

//    int lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, rlen);
    int r = int(dist(md));
    mutpos.push_back(r);

    int r2 = int(dist(md));
    mutpos.push_back(r2);

    sort (mutpos.begin (), mutpos.end ());
//    cout << mutpos[0] << ", " << mutpos[1] << endl;
    
    int count = 0;
    for (auto it = vunits.begin(); it != vunits.end(); ++it) {
        if (count >= mutpos[0] && count <= mutpos[1]) {
            if (it->size() == 1) {
                string t = vrh[(*it)[0]];
// potential for some random fragmentation here:
                for (auto tt = t.begin(); tt != t.end(); ++tt) {
                    result += *tt;
                }
            } else {
                for (unsigned long i = (*it)[0]; i <= (*it)[1]; i++) {
                    result += vrh[i];
                }
            }
        }
        count++;
    }
    
    if (result.front () == '~')
        result.erase (result.begin());
    if (result.back () == '~')
        result.erase (result.end()-1);
    if (result == "")
        result = vrh[0];
//        cout << "Error. empty. " << vrh[0] << endl;
    return result;
}

string Mutations::Rotation (string rhythm) {
    string result = "";
    vector<unsigned long> vopenb;
    vector<unsigned long> vclosb;
    vector<unsigned long> vopens;
    vector<unsigned long> vcloss;
    vector<vector<unsigned long>> vunits;
    std::size_t num_symb = vrh.size ();
    string e = vrh.back();
    if (e == "newline")
        num_symb--;
        
    // unbalanced brackets, [ or (, cause parse errors earlier
    // finding out where the outer bracket pairs are []
    for (unsigned long i = 0; i < num_symb; i++) {
        if (vrh[i] == "[") vopenb.push_back(i);
    }
    // with knowledge of the opening brackets, find the closing brackets
    for (auto it = vopenb.begin() ; it != vopenb.end(); ++it) {
        vclosb.push_back (CloseBracketInd (*it));
    }
    
    // finding the pos of the silence brackets ()
    for (unsigned long i = 0; i < num_symb; i++) {
        if (vrh[i] == "(") vopens.push_back(i);
    }
    for (auto it = vopens.begin(); it != vopens.end(); ++it) {
        vcloss.push_back (CloseSilenceBracketInd (*it));
    }
    
//    cout << "non-nested square brackets:" << endl;
    unsigned long last_closed = 0;
    for (auto it = vopenb.begin(), it2 = vclosb.begin(); it != vopenb.end(); ++it, ++it2) {
        unsigned long openb = *it;
        if (openb == 0 || openb > last_closed) {
            vector<unsigned long> v;
            v.push_back(*it);
            v.push_back(*it2);
            vunits.push_back(v);
        }
        last_closed = *it2;
    }
    
//    cout << "with silence brackets outside square brackets:" << endl;
    for (auto it = vopens.begin(), it2 = vcloss.begin(); it != vopens.end(); ++it, ++it2) {
        int flag = 0;
        for (auto vt = vunits.begin(); vt != vunits.end(); ++vt) {
            if (*it > (*vt)[0] && *it < (*vt)[1]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            vector<unsigned long> v;
            v.push_back(*it);
            v.push_back(*it2);
            vunits.push_back(v);
        }
    }
    
    if (vunits.size() == 0) {
        // if rhythm has no brackets at all, then breaking it up into
        // single chars
        rhythm = "";
        for (auto vt = vrh.begin(); vt != vrh.end(); ++vt) {
            if ((*vt) != "newline")
                rhythm += (*vt);
        }
//        rhythm = vrh[0];
        vrh.clear();
        for (auto rt = rhythm.begin(); rt != rhythm.end(); ++rt) {
            string s;
            s += (*rt);
            vrh.push_back(s);
        }
        num_symb = vrh.size ();
    }
    // finding the pos of all patterns outside all brackets
    for (unsigned long i = 0; i < num_symb; i++) {
        int flag = 0;
//        cout << vrh[i] << endl;
        if (vrh[i] == "~") {
            // ignoring the ~ ties
//            continue;
            vector<unsigned long> v;
            v.push_back(i);
            vunits.push_back(v);
//            cout << "tie: " << i << endl;
        }
        for (auto vt = vunits.begin(); vt != vunits.end(); ++vt) {
            if ((*vt).size() == 2){
                if (i >= (*vt)[0] && i <= (*vt)[1]) {
                    flag = 1;
                    break;
                }
            } else {
                if (i == (*vt)[0]) {
                    flag = 1;
                    break;
                }
            }
        }
        if (!flag) {
            vector<unsigned long> v;
            v.push_back(i);
            vunits.push_back(v);
        }
    }
    sort (vunits.begin(), vunits.end());
//    for (auto it = vunits.begin(); it != vunits.end(); ++it) {
//        if ((*it).size() == 2){
//            cout << (*it)[0] << ", " << (*it)[1] << endl;
//        } else {
//            cout << (*it)[0] << endl;
//        }
//    }

    std::size_t rlen = vunits.size ();
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, rlen);
    long r = static_cast<long>(dist(md));
    
    rotate(vunits.begin(), vunits.begin()+r, vunits.end());

    if (vunits.front().size() == 1) {
        if (vrh[vunits.front()[0]] == "~")
            vunits.erase (vunits.begin());
    }
    if (vunits.back().size() == 1) {
        if (vrh[vunits.back()[0]] == "~")
            vunits.erase (vunits.end()-1);
    }
    
    for (auto it = vunits.begin(); it != vunits.end(); ++it) {
        if ((*it).size() == 2){
            for (unsigned long i = (*it)[0]; i <= (*it)[1]; i++ )
                result += vrh[i];
//            cout << (*it)[0] << ", " << (*it)[1] << endl;
        } else {
//            cout << (*it)[0] << endl;
            result += vrh[(*it)[0]];
        }
    }
    return result;
}

string Mutations::Mutation (string rhythm, unsigned long n) {
    // random mutations, n = number of mutations
    
    size_t rlen = rhythm.length ();
    vector <unsigned long> mutpos;
    //srand (time(NULL));
    unsigned long m = n;
//    unsigned long lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, rlen);

    for (unsigned long i = 0; i < m; i++ ) {
        unsigned long r = static_cast<unsigned long>(dist(md));
        mutpos.push_back(r);
    }
    
    cout << "$ mutations at positions: ";
    for (unsigned long i = 0; i < n; i++) {
        cout << mutpos.at(i) << ", ";
    }
    
    cout << endl;
    string dual = "I:v";
    unsigned long dual_length = dual.length ();
    string ternary = "-iX><w";
    unsigned long ternary_length = ternary.length ();
    string quaternary = "H!";
    const int quat_repl_length = 8;
    string quat_repl[quat_repl_length] = {"!", "H", "::", "II", "-.", ":I", "I:", ".I."};
    unsigned long i = 0;
    for (string::iterator it=rhythm.begin(); it!=rhythm.end(); ++it, i++) {
        int flag = 0;
        for (unsigned long k = 0; k < n; k++) {
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
                        c = dual[static_cast<unsigned long>(rand()) % dual_length];
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
                    rhythm.replace (i,  1,  temp, 0, temp.length()); //, 0, string::npos);
                    break;
                }
            }
            for (string::iterator it2=ternary.begin(); it2!=ternary.end(); ++it2) {
                if (int(*it2) == int(*it)) {
                    char c = *it;
                    while (1) {
                        c = ternary[static_cast<unsigned long>(rand()) % ternary_length];
                        if (int(c) != int(*it))
                            break;
                    }
                    rhythm[i] = c;
                    break;
                }
            }
        }
    }
    
    cout << "Mutation result: " << rhythm << endl;
    return rhythm;
}

string Mutations::Swap (string rhythm, unsigned long n) {
    //random swap(s), n = number of swaps
    size_t rlen = rhythm.length ();
    vector <unsigned long> mutpos;
    srand (static_cast<unsigned int>(time(NULL)));
    unsigned long m = n;
    unsigned long lenm1 = rlen - 1;
    random_device rd;
    mt19937 md(rd());
    uniform_real_distribution<double> dist(0, lenm1);
    while (--m >= 0) {
        unsigned long r = static_cast<unsigned long>(dist(md));
        mutpos.push_back(r);
    }
    
    cout << "$ swapping at positions: ";
    for (unsigned long i = 0; i < n; i++) {
        cout << mutpos.at(i) << ", ";
    }
    cout << endl;
    for (unsigned long i=0; i < n; i++) {
        char c = rhythm[mutpos.at(i)];
        unsigned long swapindex = mutpos.at(i)+1;
        if (swapindex > lenm1) swapindex = 0;
        rhythm[mutpos.at(i)] = rhythm[swapindex];
        rhythm[swapindex] = c;
        //cout << "swap at pos: " << i << endl;
    }
    
    //cout << rhythm << endl;
    return rhythm;
}

string Mutations::Silence (string rhythm, unsigned long n, unsigned long k) {
    // renders a silence with symbols between pos n and k
    
    // check whether there is already silence in the string
    // if yes, then remove the brackets
    unsigned long i = 0;
    for (string::iterator it=rhythm.begin(); it!=rhythm.end(); ++it, i++) {
        if (int(*it) == 40 || int(*it) == 41) // == '(' or ')'
            rhythm.erase(rhythm.begin()+long(i));
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
    unsigned long i, len;
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
            for (; i >= 0; i--) {
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
            for (; i >= 0; i--) {
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
            for (; i >= 0; i--) {
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

string Mutations::Reverse () {
    // original rhythm needed?
    // use of RhythmParser in Modul.cpp
    string result = "";
    unsigned long openb = 0;
    int num_open = 0;
    unsigned long num_symb = vrh.size ();
    
    // how many balanced open brackets?
    // unbalanced brackets, [ or (, cause parse errors earlier
    for (unsigned long i = 0; i < num_symb; i++) {
        if (vrh[i] == "[") {
            num_open++;
        }
    }
    
    if (num_open == 0) {
        // reverse each vrh element
        for (auto vit = vrh.rbegin(); vit != vrh.rend(); vit++) {
//        for (unsigned long i = num_symb-1; i != 0; --i) {
//            if (vrh[i] == "newline") {
            string cur = *vit;
            if (cur == "newline") {
                continue;
            }
//            string cur = vrh[i];
            
            if (cur == "(")
                result += ")";
            else if (cur == ")")
                result += "(";
            else {
                for (auto st = cur.rbegin(); st != cur.rend(); st++) {
                    result += *st;
                }
            }
        }
        return result;
    }
    
    while (num_open-- > 0) {
        // find the next open bracket [
        // because of ReverseBrackets we can always start at i = 0
        for (unsigned long i = 0; i < num_symb; i++) {
            if (vrh[i] == "[") {
                openb = i;
                break;
            }
        }
        // find corresponding closing bracket index
        unsigned long closeb = CloseBracketInd (openb);
        if (closeb > 0)
            ReverseBrackets (openb, closeb);
        result = "";
        // after [ brackets and subdivision integers have been dealt with
        // reverse the complete shorthand string
        for (auto it = vrh.rbegin(); it!=vrh.rend(); ++it) {
            if (*it != "newline") {
                string temp = *it;
                if (temp.size() > 1) {
                    // reverse internal shorthand strings if they are sounding patterns of length > 1
                    for (auto st = temp.rbegin(); st != temp.rend(); st++) {
                        result += *st;
                    }
                } else {
                    // reverse silence brackets
                    if (*it == "(")
                        result += ")";
                    else if (*it == ")")
                        result += "(";
                    else
                        // keep everything else as is
                        result += *it;
                }
            }
        }
    }
    return result;
}


unsigned long Mutations::CloseBracketInd(unsigned long index){
    unsigned long i;
//    if(vrh[index]!="["){
//        return -1;
//    }
    stack <unsigned long> st;
    for(i = index; i < vrh.size(); i++){
        if(vrh[i] == "[") {
            st.push(i);
        } else if(vrh[i] == "]"){
            st.pop();
            if(st.empty()){
                return i;
            }
        }
    }
    return 0;
}

unsigned long Mutations::CloseSilenceBracketInd(unsigned long index){
    unsigned long i;
//    if(vrh[index]!="("){
//        return -1;
//    }
    stack <unsigned long> st;
    for(i = index; i < vrh.size(); i++){
        if(vrh[i] == "(") {
            st.push(i);
        } else if(vrh[i] == ")"){
            st.pop();
            if(st.empty()){
                return i;
            }
        }
    }
    return 0;
}

void Mutations::ReverseBrackets(unsigned long openb, unsigned long closb) {
    vrh[openb] = "]";
    vrh[closb] = "[";
    if (isNum(vrh[openb+1])) {
        auto closPos = vrh.begin() + long(closb);
        vrh.insert(closPos, vrh[openb+1]);
        vrh.erase(vrh.begin() + long(openb) + 1);
    }
}


bool Mutations::isNum (string line) {
    char* p;
    strtol(line.c_str(), &p, 10);
    return (*p == 0);
}

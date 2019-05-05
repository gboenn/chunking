// Parser for the Shorthand Notation of Musical Rhythm (SNMR)
// (c) 2019.  Georg Boenn. All rights reserved.

%{
  #include <cstdio>
  #include <iostream>
  #include <vector>
  #include <string>
  using namespace std;
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern string rstring;
  extern vector<string> vrh;
  void yyerror(const char *s);
  void print_list ();
%}


%token NUMBER
%token RSTR
%token TIE
%token OB CB OP CP 
%token EOL

%%

rhylist: 
| rhylist exp EOL { print_list (); /*vrh.clear();*/ cout << endl; }
 | rhylist EOL { cout << "> "; }
 ;


exp: term { cout << "term." << endl; }
 | exp TIE exp { cout << "exp tie term." << endl; }
 | exp OB exp CB { cout << "ob exp cb." << endl; }
 | OB exp CB { cout << "ob exp cb." << endl; }
 | OB exp CB exp { cout << "ob exp cb." << endl; }
 | exp OB exp CB exp { cout << "ob exp cb." << endl; }
 | OB NUMBER exp CB { cout << "ob number exp cb." << endl; }
 | OB NUMBER exp CB exp { cout << "ob number exp cb." << endl; }
 | exp OB NUMBER exp CB { cout << "ob number exp cb." << endl; }
 | exp OB NUMBER exp CB exp { cout << "ob number exp cb." << endl; }
 | OP exp CP
 | exp OP exp CP
 | OP exp CP exp
 | exp OP exp CP exp
;

term: RSTR { cout << "rstr." << endl; }
| term RSTR { cout << "term rstr." << endl; }
| RSTR term { cout << "rstr term." << endl; }
;

%%
int main(int argc, char** argv)
{
  //  printf("> "); 
  if (argc > 1) {
    if (!(yyin = fopen(argv[1], "r"))) {
      perror(argv[1]);
      return (1);
    }
  }
  yyparse();
  return 0;
}

void print_list () {
  int rsize = vrh.size();
  int i = 0;
  for (i=0; i<rsize; i++) {
    cout << vrh.at(i) << ", ";
  }
  cout << endl;
}

//void yyerror (const char *s) {
//  cout << "Parse error!  Message: " << s << " Line: " << yylineno << endl;
  //  exit (-1);
//}

/*
[[XI]XXI]
rstr.
term.
ob exp cb.
term rstr.
term.
ob exp cb.
term.
[, [, XI, ], XXI, ], 
if [ -> divlist.push_back (2.);
if [ -> divlist.push_back (2.);                                                                                       
if XI -> decode XI and divide by ach element in divlist one by one 

if ] -> pop_back from divlist

if XXI -> decode XXI and divide by ach element in divlist one by one
if ] -> pop_back from divlist


> IX(IIX)~I
rstr.
term.
rstr term.
term.
rstr.
exp tie term.
IX, (, IIX, ), ~, I,

if ( -> then following decodes will be negative influencing next events start time and past events duration
in lilypond this triggers rests of the durations within the ()

if ) behaviour turns back to positive decodings

if ~ (, or if ) ~ then ~ will be ignored in both cases

*/

%{
  #include <iostream>
  #include <string>
  #include <vector>
  #include "rhylang.tab.h"
  using namespace std;
  extern int yylex();
  extern void yyerror(const char *s);
  string rstring;
  vector<string> vrh;
%}
%option noyywrap
%option yylineno
%%

[.:Iv><Xi+wHW-]+ { vrh.push_back(string(yytext));  return RSTR; }
"~"     { vrh.push_back(string(yytext)); return TIE; }
"["     { vrh.push_back(string(yytext)); return OB; }
"]"     { vrh.push_back(string(yytext)); return CB; }
"("     { vrh.push_back(string(yytext)); return OP; }
")"     { vrh.push_back(string(yytext)); return CP; }  

[0-9]+	{ vrh.push_back(string(yytext)); yylval = atoi(yytext); return NUMBER; }

\n      { return EOL; }
"$".*   { /* ignore comments */ }  
[ \t]   { /* ignore white space */ }
.	
%%

void yyerror (const char *s) {
  cout << "Parse error!  Message: " << s << " in line: " << (yylineno -1) << endl;
  //  exit (-1);                                                                                                               
}

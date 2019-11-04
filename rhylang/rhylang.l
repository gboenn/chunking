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

[LBQEFG.:Iv><Xi+wHW-]+ { vrh.push_back(string(yytext));  return RSTR; }
"~"     { vrh.push_back(string(yytext)); return TIE; }
"["     { vrh.push_back(string(yytext)); return OB; }
"]"     { vrh.push_back(string(yytext)); return CB; }
"("     { vrh.push_back(string(yytext)); return OP; }
")"     { vrh.push_back(string(yytext)); return CP; }
"%"  { vrh.push_back(string(yytext)); return NEWVOICE; }
"S"  { vrh.push_back(string(yytext)); return NEWSTAFF; }


[0-9]+	{ vrh.push_back(string(yytext)); yylval = atoi(yytext); return NUMBER; }

\n      { return EOL; }
"$".*   { /* ignore comments */ }
[ \t]   { /* ignore white space */ }
.
%%

void yyerror (const char *s) {
  cout << "Parse error!  Message: " << s << " in or before line: " << (yylineno) << endl;
  //  exit (-1);
}

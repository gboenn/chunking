all: rhylang librhylang
rhylang.tab.c rhylang.tab.h: rhylang.y
	bison -d rhylang.y
lex.yy.c: rhylang.l rhylang.tab.h
	flex rhylang.l
rhylang: lex.yy.c rhylang.tab.c rhylang.tab.h
	g++ rhylang.tab.c lex.yy.c -ll -o rhylang

librhylang: lex.yy.c rhylang.tab.c rhylang.tab.h
	g++ -dynamiclib rhylang.tab.c lex.yy.c -o librhylang.dylib
	cp librhylang.dylib ../.

clean: 
	rm -f rhylang rhylang.tab.c rhylang.tab.h lex.yy.c librhylang.dylib
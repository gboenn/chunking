///////////////////////////////////////////
// Interpret.h
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#ifndef __Interpret_h__

#define __Interpret_h__

#ifndef __chunking_Standards_h__
#include "chunking_Standards.h"
#endif

#ifndef __TextIO_h__
#include "TextIO.h"
#endif

#ifndef	__Modul_h__
#include "Modul.h"
#endif

#include <string.h>
#include <sqlite3.h>

struct ArgBuf 
{
	char text[MAXZEILEN];
};

class Modul;

class Interpret {

	private:

		int i; // index to lines
		int k; // index to characters on line
		int w; // index to words
		int wk; // index to characters of word
		int wc; // counter
		int we;
		int wl;
		int ck;
		int nchars; // length of line 
		int nullcount;
		
		string prompt;

		struct ArgBuf args_obj[MAXLINES];
		string ms;
    
    sqlite3 *rhy;
    int db_err;
    int add_flag;
    string user_session;
    string user_method;
    
    
	public:

		Interpret();
		~Interpret();
		void Dispatch ( TextIO& coms, Modul& mdl, int from_cmd_line=0 );
		void TypeError (TextIO& coms, string ms);
		void SetArgs (string arg, int index) { strcpy (args_obj[index].text, arg.c_str()); }
		void SetModulFunct (string function_name) { ms = function_name; }
    void InsertIntoDB (string);
    void PrintSession (string session_name);
    static int DetermineInstallDirectory ();
    string GetInstallDirectory () { return install_dir; };
    string GetVersionNumber () { return version_number; }
    
    static string install_dir;
    static string version_number;
};

#endif // __Interpret_h__

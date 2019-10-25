///////////////////////////////////////////
// Main.cpp
// Copyright (C) 2018 Georg Boenn
// GNU General Public License version 3.0
// Free Software Foundation
///////////////////////////////////////////

#include "Interpret.h"

//#include "leak_detector.h"
	
int main(int argc, char* argv[]) {

#if BOEHM_GC_SWITCH
    GC_INIT();
#endif
//    GC_find_leak = 1;

	if (argc > 2) {
		if (!strcmp("-m", argv[1])) {
            Interpret interpreter;
			interpreter.SetModulFunct (argv[2]);
			int k = 0;
			for (int i = 3; i<argc; i++, k++)
				interpreter.SetArgs (string(argv[i]), k);
			
			TextIO text ("init program...");
			Modul module;
						
			interpreter.Dispatch (text, module, 1);

			return 0;
		}
	}
	
	cout << "Usage: chunking -m <command> <agruments>" << endl;


//	CHECK_LEAKS();

	return 0;
}

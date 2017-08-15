#include "Interpret.h"

//#include "leak_detector.h"
	
int main(int argc, char* argv[]) {

#if BOEHM_GC_SWITCH
    GC_INIT();
#endif
//    GC_find_leak = 1;

	if (argc > 1) {
		if (!strcmp("-m", argv[1])) {
			Interpret interpreter;
			interpreter.SetModulFunct (argv[2]);
			int k = 0;
			for (int i = 3; i<argc; i++, k++)
				interpreter.SetArgs (string(argv[i]), k);
			
			TextIO text ("init program...");
			Modul module ("AIFF", 1, 0, 16, 44100 );
						
			interpreter.Dispatch (text, module, 1);
			return 0;
		}
		else {
		  cout << "Usage: chunking -m <command> <agruments>" << endl;
		}
	}

#if 0
	TextIO text("init program...");

	Modul module( "AIFF", 1, 0, 16, 44100 );

	Interpret interpreter;

	text.ReadCommands();
	
	interpreter.DoInterpret(text, module);
#endif
//	CHECK_LEAKS();

	return 0;
}

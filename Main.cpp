#include "Interpret.h"

//#include "leak_detector.h"
	
int main(int argc, char* argv[])
{
#if BOEHM_GC_SWITCH
    GC_INIT();
#endif
//    GC_find_leak = 1;
//	cout <<argc <<endl;
	if (argc > 1)
	{
		int i = 0;
//		for (; i<argc; i++)
//			cout << argv[i] << endl;
	
		if (!strcmp("-m", argv[1]))
		{
//			cout << "option modul" << endl;
			Interpret interpreter;
			interpreter.SetModulFunct (argv[2]);
			int k = 0;
			for (i = 3; i<argc; i++, k++)
				interpreter.SetArgs (string(argv[i]), k);
			
			TextIO text ("init program...");
			Modul module ("AIFF", 1, 0, 16, 44100 );
			//text.ReadCommands ();
			
			interpreter.Dispatch (text, module, 1);
			return 0;
		}
	}

	TextIO text("init program...");

	Modul module( "AIFF", 1, 0, 16, 44100 );

	Interpret interpreter;

	text.ReadCommands();
	
	interpreter.DoInterpret(text, module);

//	CHECK_LEAKS();

	return 0;
}

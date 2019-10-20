//#include "/usr/local/include/chunking/Modul.h"
//#include "/usr/local/include/chunking/TextIO.h"

#include <Modul.h>
#include <TextIO.h>

void script1 () {

Modul m;
stringstream s2;
string r = "IXI>I:";
int counter = 5;

while (--counter) {
  s2 << r << endl;
  r = m.Mutation(r,1);
  if (counter % 3 == 0) {
    r = m.Reverse(r);
  }
 }

StringToFile f ("mutations2.txt");
f.Append(s2.str());


stringstream mel;
mel << "60,62,67,64,65,67,69,71" << endl;
StringToFile p ("motive2.txt");
p.Append(mel.str());

m.PrintPhrases("mutations2.txt","motive2.txt",200,1);

 system("/Applications/LilyPond.app/Contents/Resources/bin/lilypond print_phrase.ly");
 system("open -a /Applications/Preview.app/ print_phrase.pdf");
 system("timidity -T 300 print_phrase.midi");
}

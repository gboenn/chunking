void script1 () {

Modul m("a",1,1,1,1);
stringstream s2;
string r = "IXI>I:";
int counter = 10;

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

m.PrintPhrases("mutations2.txt","motive2.txt",130,1);

}

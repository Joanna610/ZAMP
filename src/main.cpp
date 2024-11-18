#include <iostream>
#include "ProgramInterpreter.hh"


using namespace std;

// bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
// {
//   string Cmd4Preproc = "cpp -P ";
//   char Line[LINE_SIZE];
//   ostringstream OTmpStrm;
//   Cmd4Preproc += NazwaPliku;
//   FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
//   if (!pProc) return false;
//   while (fgets(Line,LINE_SIZE,pProc)) {
//     OTmpStrm << Line;
//   }
//   IStrm4Cmds.str(OTmpStrm.str());
//   return pclose(pProc) == 0;
// }

int main(int argc, char *argv[])
{

  ProgramInterpreter interp;
  if (!interp.Read_XML_Config("config/config.xml")) {
    cout << "Nie udało się wczytac pliku XML.\n";
    return 1;
  }

  // istringstream strm4Cmds;
  // if(!ExecPreprocesor("/home/joanna/Desktop/ZAMP/ZAMP/opis_dzialan.cmd", strm4Cmds)) {
  //   cout << "Nie udało się wczytac pliku z opisem działan.\n";
  //   return 1;
  // }

  // Set4LibInterfaces interface;
  // interface.findLibrary(strm4Cmds);


  if(!interp.ExecProgram("/home/joanna/Desktop/ZAMP/ZAMP/opis_dzialan.cmd")) {
    cout << "Nie udało się wczytac pliku z opisem działan.\n";
    return 1;
  }


}

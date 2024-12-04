#include <iostream>
#include "ProgramInterpreter.hh"
#include "Configuration.hh"


using namespace std;


int main(int argc, char *argv[])
{

  ProgramInterpreter interp;

  if(!interp.ExecProgram("/home/joanna/Desktop/ZAMP/ZAMP/opis_dzialan.cmd")) {
    cout << "Nie udało się wczytac pliku z opisem działan.\n";
    return 1;
  }

}

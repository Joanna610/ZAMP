#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <list>


#include "AbstractInterp4Command.hh"
#include "xmlinterp.hh"

using namespace std;
using namespace xercesc;


#define LINE_SIZE 500

using namespace std;


bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
  if (!pProc) return false;
  while (fgets(Line,LINE_SIZE,pProc)) {
    OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}


/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}


int main(int argc, char *argv[])
{
  
  // void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY); // ładuje biblioteke
  // void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  // void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  // void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);


  // AbstractInterp4Command *(*pCreateCmd_Move)(void);
  // void *pFun;

  // if (!pLibHnd_Move) {
  //   cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
  //   return 1;
  // }

  // AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
  // void *pFun_rotate;

  // if (!pLibHnd_Rotate) {
  //   cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
  //   return 1;
  // }

  // AbstractInterp4Command *(*pCreateCmd_Pause)(void);
  // void *pFun_pause;

  // if (!pLibHnd_Pause) {
  //   cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
  //   return 1;
  // }

  // AbstractInterp4Command *(*pCreateCmd_Set)(void);
  // void *pFun_set;

  // if (!pLibHnd_Set) {
  //   cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
  //   return 1;
  // }


  // pFun = dlsym(pLibHnd_Move,"CreateCmd"); // pobiera wskaźnik do funkcji
  // if (!pFun) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  // pFun_rotate = dlsym(pLibHnd_Rotate,"CreateCmd");
  // if (!pFun_rotate) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_rotate);

  // pFun_pause = dlsym(pLibHnd_Pause,"CreateCmd");
  // if (!pFun_pause) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Pause = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_pause);

  // pFun_set = dlsym(pLibHnd_Set,"CreateCmd");
  // if (!pFun_set) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Set = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_set);

  // AbstractInterp4Command *pCmd_move = pCreateCmd_Move();
  // AbstractInterp4Command *pCmd_rotate = pCreateCmd_Rotate();
  // AbstractInterp4Command *pCmd_pause = pCreateCmd_Pause();
  // AbstractInterp4Command *pCmd_set = pCreateCmd_Set();

  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY); // ładuje biblioteke
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);


  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }

  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
  void *pFun_rotate;

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }

  AbstractInterp4Command *(*pCreateCmd_Pause)(void);
  void *pFun_pause;

  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
    return 1;
  }

  AbstractInterp4Command *(*pCreateCmd_Set)(void);
  void *pFun_set;

  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd"); // pobiera wskaźnik do funkcji
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  pFun_rotate = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun_rotate) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_rotate);

  pFun_pause = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!pFun_pause) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_pause);

  pFun_set = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFun_set) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Set = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun_set);

  AbstractInterp4Command *pCmd_move = pCreateCmd_Move();
  AbstractInterp4Command *pCmd_rotate = pCreateCmd_Rotate();
  AbstractInterp4Command *pCmd_pause = pCreateCmd_Pause();
  AbstractInterp4Command *pCmd_set = pCreateCmd_Set();

  istringstream strm4Cmds;
  if(!ExecPreprocesor("/home/joanna/Desktop/ZAMP/ZAMP_zalazek/opis_dzialan.cmd", strm4Cmds)) {
    cout << "Nie udało się wczytac pliku.\n";
    return 0;
  }
  string n;

  Configuration   Config;

  if (!ReadFile("config/config.xml",Config)) return 1;

  while (strm4Cmds) {
 
        strm4Cmds >> n;

        if(n == "Set") {
          pCmd_set->ReadParams(strm4Cmds);
          cout << endl;
          cout << pCmd_set->GetCmdName() << endl;
          cout << endl;
          pCmd_set->PrintSyntax();
          cout << endl;
          pCmd_set->PrintCmd();
          cout << endl;

        }
        else if(n == "Move"){
          pCmd_move->ReadParams(strm4Cmds);
          cout << endl;
          cout << pCmd_move->GetCmdName() << endl;
          cout << endl;
          pCmd_move->PrintSyntax();
          cout << endl;
          pCmd_move->PrintCmd();
          cout << endl;

        }
        else if(n == "Rotate"){

          pCmd_rotate->ReadParams(strm4Cmds);

          cout << endl;
          cout << pCmd_rotate->GetCmdName() << endl;
          cout << endl;
          pCmd_rotate->PrintSyntax();
          cout << endl;
          pCmd_rotate->PrintCmd();
          cout << endl;    
        }
        else if(n == "Pause"){
          pCmd_pause->ReadParams(strm4Cmds);
          cout << endl;
          cout << pCmd_pause->GetCmdName() << endl;
          cout << endl;
          pCmd_pause->PrintSyntax();
          cout << endl;
          pCmd_pause->PrintCmd();
          cout << endl;
        }       
    }
  
  delete pCmd_move;
  delete pCmd_rotate;
  delete pCmd_pause;
  delete pCmd_set;

  dlclose(pLibHnd_Move); 
  dlclose(pLibHnd_Rotate);
  dlclose(pLibHnd_Pause);
  dlclose(pLibHnd_Set);



}

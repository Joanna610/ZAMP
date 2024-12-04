#include "ProgramInterpreter.hh"
#include <iostream>
#include <unistd.h>


using namespace std;

bool ProgramInterpreter::Read_XML_Config(const char* FileName){
    /*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param FileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
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
     pParser->parse(FileName);
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

   _Chann2Serv.Send("Clear\n");
   Cuboid *cuboid = new Cuboid;
  // adding elements to the scene
  for (int i=0; i< rConfig.getListSize();++i){
    
    cuboid->SetName(rConfig[i]._Name.c_str());
    cuboid->SetPosition_m(rConfig[i]._Trans_m);
    cuboid->SetAng_Pitch_deg(rConfig[i]._RotXYZ_deg[0]);
    cuboid->SetAng_Roll_deg(rConfig[i]._RotXYZ_deg[1]);
    cuboid->SetAng_Yaw_deg(rConfig[i]._RotXYZ_deg[2]);
    std::cout << "Adding to scene..." << std::endl;

    _Chann2Serv.AddObjToServer(rConfig[i]._Name, rConfig[i]._Shift, rConfig[i]._Scale, rConfig[i]._Trans_m, rConfig[i]._RGB, rConfig[i]._RotXYZ_deg);
    // _Chann2Serv.Send(data);

    _Scn.AddMobileObj(cuboid);
  }
  delete cuboid;
    return true;
}


bool ProgramInterpreter::ExecPreprocesor(const char* FileName_Prog){
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += FileName_Prog;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
  if (!pProc) return false;
  while (fgets(Line,LINE_SIZE,pProc)) {
    OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

bool ProgramInterpreter::OpenConnection(){
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  int Socket = socket(AF_INET,SOCK_STREAM,0);

  if (Socket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(Socket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }

   _Chann2Serv.Init(Socket);
  return true;
}


bool ProgramInterpreter::ExecProgram(const char* FileName_Prog){
    if(!OpenConnection()) return false;

    if (!Read_XML_Config("config/config.xml")) {
      cout << "Nie udało się wczytac pliku XML.\n";
      return 1;
    }

    for (int i = 0; i< rConfig.getPluginListSize(); i++){
      this->interface.initLibrary(rConfig.getPlugin(i));
    }
    
    // wczytuje plik dzialan
    if(!this->ExecPreprocesor(FileName_Prog)) return false;
    // przesyla ten strumien z ktorego wczytal do klasu obsugujacej strumienie
    this->interface.findLibrary(IStrm4Cmds, _Scn, _Chann2Serv);

    _Chann2Serv.Send("Close\n");
        rConfig.showPlugins();

    return true;
}




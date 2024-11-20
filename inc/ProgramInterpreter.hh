#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH
#include <iostream>


#include "xmlinterp.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
// #include "Configuration.hh"
#include "Set4LibInterfaces.hh"
#include "Scene.hh"

#include "Port.hh"
#include "ComChannel.hh"

#define LINE_SIZE 500

using namespace xercesc;

class ProgramInterpreter {
    Configuration rConfig;
    istringstream IStrm4Cmds;
    Set4LibInterfaces interface;
    Scene _Scn;
    ComChannel _Chann2Serv;

public:
    ProgramInterpreter(){};
    bool Read_XML_Config(const char* FileName);
    bool ExecProgram(const char* FileName_Prog);
    bool ExecPreprocesor(const char* FileName_Prog);
    void showConfiguration();
    // bool OpenConnection(int &rSocket);
    bool OpenConnection();
    bool SendObjToServer();



};
#endif
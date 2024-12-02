#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <iostream>
#include <memory>
#include <map>
#include <dlfcn.h>
#include <cassert>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <thread>


#include "AbstractInterp4Command.hh"
#include "Scene.hh"
#include "ComChannel.hh"

class LibInterface{

    void *_LibHandler;
    std::string CmdName;
    AbstractInterp4Command *(*_pCreateCmd)();
    AbstractInterp4Command *pCmd;
    list<std::thread> list_Thread;
    list<shared_ptr<AbstractInterp4Command>> Lib_Interp;

public:
    bool openLibrary();
    void print();
    void readStream(std::istream& Strm, Scene &_Scn, ComChannel &_CmChnl);
    LibInterface(std::string LibraryName);
    ~LibInterface();
};
#endif
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
    

public:
    bool openLibrary();
    void print();
    AbstractInterp4Command* readStream(std::istream& Strm, Scene &_Scn, ComChannel &_CmChnl);
    LibInterface(std::string LibraryName);
    static void Fun4Thread(AbstractInterp4Command* pInterp, Scene &rScn , ComChannel &rChann);

    ~LibInterface();
};
#endif
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

#include "AbstractInterp4Command.hh"

class LibInterface{

    void *_LibHandler;
    std::string CmdName;
    AbstractInterp4Command *(*_pCreateCmd)();
    AbstractInterp4Command *pCmd;

public:
    bool openLibrary();
    void print();
    void readStream(std::istream& Strm);
    LibInterface(std::string LibraryName);
    ~LibInterface();
};
#endif
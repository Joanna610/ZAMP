#ifndef SET4LIBINTERFACE_HH
#define SET4LIBINTERFACE_HH


#include <map>
#include <memory>
#include <string>

using namespace std;
#include "LibInterface.hh"
#include "Scene.hh"
#include "ComChannel.hh"

class Set4LibInterfaces{

    map<string, shared_ptr<LibInterface>> commandLibs;
    

public:
    Set4LibInterfaces();
    void findLibrary(std::istream& Strm, Scene &_Scene, ComChannel &_CmChnl);
};

#endif
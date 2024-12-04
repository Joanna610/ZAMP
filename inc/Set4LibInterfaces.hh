#ifndef SET4LIBINTERFACE_HH
#define SET4LIBINTERFACE_HH


#include <map>
#include <memory>
#include <string>
#include <list>

using namespace std;
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"
#include "Scene.hh"
#include "ComChannel.hh"


class Set4LibInterfaces{

    map<string, shared_ptr<LibInterface>> commandLibs;
    list<std::thread> list_Thread;
    list<AbstractInterp4Command*> Lib_interp;

public:
    Set4LibInterfaces();
    void initLibrary(std::string Libname);
    void findLibrary(std::istream& Strm, Scene &_Scene, ComChannel &_CmChnl);
    static void Fun4Thread(AbstractInterp4Command* pInterp, Scene &rScn , ComChannel &rChann);

};

#endif
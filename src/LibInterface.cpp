#include "LibInterface.hh"

using namespace std;

LibInterface::LibInterface(std::string LibraryName): _LibHandler(nullptr), 
                                                    CmdName(LibraryName), 
                                                    _pCreateCmd(nullptr), 
                                                    pCmd(nullptr)
                                                    {
    this->openLibrary();
}

LibInterface::~LibInterface(){
    dlclose(_LibHandler); 
}

bool LibInterface::openLibrary(){
    _LibHandler = dlopen(CmdName.c_str(), RTLD_LAZY); 

    if (!_LibHandler) {
        std::cerr << "!!! Brak biblioteki" << std::endl;
        return false;
    }
    void *pFun;

    pFun = dlsym(_LibHandler,"CreateCmd"); // pobiera wskaźnik do funkcji
    if (!pFun) {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
        return false;
    }
    _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
    pCmd = _pCreateCmd();
    return true;
}

void LibInterface::readStream(std::istream& Strm, Scene &_Scn, ComChannel &_CmChnl){
    pCmd->ReadParams(Strm);
    pCmd->ExecCmd(_Scn, "lol", _CmChnl);
}

void LibInterface::print(){
    // pCmd->ReadParams(strm4Cmds);
    cout << endl;
    cout << pCmd->GetCmdName() << endl;
    cout << endl;
    pCmd->PrintSyntax();
    cout << endl;
    pCmd->PrintCmd();
    cout << endl;
}
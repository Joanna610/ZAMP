#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){
    commandLibs["Move"] = std::make_shared<LibInterface>("libInterp4Move.so");
    commandLibs["Rotate"] = std::make_shared<LibInterface>("libInterp4Rotate.so");
    commandLibs["Pause"] = std::make_shared<LibInterface>("libInterp4Pause.so");
    commandLibs["Set"] = std::make_shared<LibInterface>("libInterp4Set.so");
}

// odwoluje sie do konkretnej biblioteki ktora znajdzie
void Set4LibInterfaces::findLibrary(std::istream& Strm, Scene &_Scene, ComChannel &_CmChnl){

    std::string n;
    while (Strm >> n) { 
        auto it = commandLibs.find(n);
        if (it != commandLibs.end()) {
            // wczytuje znaeziona biblioteke i wczytuje jej parametry
            it->second->readStream(Strm, _Scene, _CmChnl);

            it->second->print();
        }
    }
}
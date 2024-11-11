#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){
    commandLibs["Move"] = std::make_shared<LibInterface>("libInterp4Move.so");
    commandLibs["Rotate"] = std::make_shared<LibInterface>("libInterp4Rotate.so");
    commandLibs["Pause"] = std::make_shared<LibInterface>("libInterp4Pause.so");
    commandLibs["Set"] = std::make_shared<LibInterface>("libInterp4Set.so");
}

void Set4LibInterfaces::findLibrary(std::istream& Strm){

    std::string n;
    while (Strm >> n) { 
        auto it = commandLibs.find(n);
        if (it != commandLibs.end()) {
            it->second->readStream(Strm);
            it->second->print();
        }
    }
}
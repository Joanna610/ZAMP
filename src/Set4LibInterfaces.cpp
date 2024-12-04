#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){
}

void Set4LibInterfaces::initLibrary(std::string Libname){
    if(Libname == "libInter4Move.so") commandLibs["Move"] = std::make_shared<LibInterface>("libInterp4Move.so");
    if(Libname == "libInter4Rotate.so") commandLibs["Rotate"] = std::make_shared<LibInterface>("libInterp4Rotate.so");
    if(Libname == "libInter4Pause.so") commandLibs["Pause"] = std::make_shared<LibInterface>("libInterp4Pause.so");
    if(Libname == "libInter4Set.so") commandLibs["Set"] = std::make_shared<LibInterface>("libInterp4Set.so");

}

void Set4LibInterfaces::Fun4Thread(AbstractInterp4Command* pInterp, Scene &rScn , ComChannel &rChann)
{
    cout<< "Start watku: "<<std::this_thread::get_id() << endl;
    if(pInterp->ExecCmd(rScn, "" , rChann)) return;
}

// odwoluje sie do konkretnej biblioteki ktora znajdzie
void Set4LibInterfaces::findLibrary(std::istream& Strm, Scene &_Scene, ComChannel &_CmChnl){
    std::string n;
    AbstractInterp4Command* pInterp = nullptr;

    while (Strm >> n) { 
        auto it = commandLibs.find(n);
        if (it != commandLibs.end()) {
            // wykonywanie sekwencyjne
            pInterp = it->second->readStream(Strm, _Scene, _CmChnl);

            // watki
            std::thread Th(Fun4Thread, pInterp, std::ref(_Scene), std::ref(_CmChnl));
            list_Thread.push_back(std::move(Th)) ;
            it->second->print();
        }
    }
    for(std::thread &rTh : list_Thread) {if(rTh.joinable())rTh.join();}
}
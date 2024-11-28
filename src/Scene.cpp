#include "Scene.hh"

AbstractMobileObj*  Scene::FindMobileObj(const char *sName) {
    // auto it = _mobileObjects.find(sName);  // Szukamy w mapie obiektu o nazwie sName
    // if (it != _mobileObjects.end()) {
        // return it->second;  // Zwracamy wskaźnik, jeśli znaleziono
    // }
    return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {
    // _list_lol.push_back(*pMobObj);
    // _Set_MobileObjs["Move"] = std::make_shared<AbstractMobileObj>("libInterp4Move.so");

}
#include "Scene.hh"

AbstractMobileObj*  Scene::FindMobileObj(const char *sName) {
    // auto it = _mobileObjects.find(sName);  // Szukamy w mapie obiektu o nazwie sName
    // if (it != _mobileObjects.end()) {
        // return it->second;  // Zwracamy wskaźnik, jeśli znaleziono
    // }
    return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {

}
#include "Scene.hh"

AbstractMobileObj*  Scene::FindMobileObj(const char *sName) {
    
    std::map<std::string, std::shared_ptr<Cuboid>>::iterator it = _Set_MobileObjs.find(sName); 
    if (it != _Set_MobileObjs.end()) {
        return it->second.get(); 
    }
    return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj) {
    // _list_lol.push_back(*pMobObj);
    _Set_MobileObjs[pMobObj->GetName()] = make_shared<Cuboid>(pMobObj);

}

int Scene::AmountObjsOnMap() {
    // _list_lol.push_back(*pMobObj);
    return _Set_MobileObjs.size();

}

void Scene::PrintObjOnScene(){
    for (std::map<std::string, std::shared_ptr<Cuboid>>::iterator it = _Set_MobileObjs.begin(); it != _Set_MobileObjs.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << std::endl;
         it->second->PrintCuboid();
    }
}
#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>
#include <string>
#include <list>
#include "AbstractScene.hh"
#include "Cuboid.hh"

using namespace std;

class Scene: public AbstractScene{
    map<string, shared_ptr<Cuboid>> _Set_MobileObjs;
    // list<Cuboid> _list_lol;
    // std::vector<MobileObj>   _Container4Objects;

    public:

    virtual AbstractMobileObj*  FindMobileObj(const char *sName) override;
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;
    int AmountObjsOnMap();
    void PrintObjOnScene();

};
#endif
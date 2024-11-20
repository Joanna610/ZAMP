#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>
#include <string>
#include "AbstractScene.hh"
#include "MobileObj.hh"

using namespace std;

class Scene: public AbstractScene{
    map<string, shared_ptr<MobileObj>> _Set_MobileObjs;

    // std::vector<MobileObj>   _Container4Objects;

    public:

    virtual AbstractMobileObj*  FindMobileObj(const char *sName) override;
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;
};
#endif
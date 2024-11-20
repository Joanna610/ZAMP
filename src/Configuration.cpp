#include "Configuration.hh"
#include <string>
#include <sstream>

#include <cstring>


using namespace std;

void Configuration::AddObject(DataFromXML obj){
    this->_Objects.push_back(obj);
}

void Configuration::showObjects(){
    for (DataFromXML value : _Objects) {
        value.showData();
    }
}

std::string Configuration::getMessage(){
    if(!_Objects.empty()){
        DataFromXML obj;
        obj = _Objects.front();
        _Objects.pop_front();

        std::string msg;

        std::ostringstream str;

        str<<"AddObj Name="<<obj.GetName()<<" Shift="<<obj.GetShift()<<" Scale="<<obj.GetScale()<<" Trans_m="<<obj.GetTransM()<<" RGB="<<obj.GetRGB()<<" RotXYZ_deg="<<obj.GetRotXYZDeg()<<std::endl;

        msg = str.str();
        return msg;
        //"AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
    } else return "ERROR";
}


int Configuration::getListSize(){
    size_t listSize = _Objects.size();
    return (int)listSize;
}



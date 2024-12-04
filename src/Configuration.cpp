#include "Configuration.hh"
#include <string>
#include <sstream>

#include <cstring>


using namespace std;

void Configuration::AddObject(RawCuboidData obj){
    this->_Objects.push_back(obj);
}

void Configuration::AddPlugin(std::string plugin){
    this->_Plugins.push_back(plugin);
}


void Configuration::showObjects(){
    for (RawCuboidData value : _Objects) {
        value.showData();
    }
}


void Configuration::showPlugins(){
    for (string value : _Plugins) {
        cout << "Plugin: " << value<<endl;
    }
}


int Configuration::getListSize(){
    size_t listSize = _Objects.size();
    return (int)listSize;
}

int Configuration::getPluginListSize(){
    size_t listSize = _Plugins.size();
    return (int)listSize;
}

std::string Configuration::getPlugin(int index){
    auto it = _Plugins.begin();
    std::advance(it, index);
    return *it;
}


RawCuboidData Configuration::operator[](unsigned int Ind) { 

    list<RawCuboidData>::iterator it = _Objects.begin();
    std::advance(it, Ind);
    return *it;
}

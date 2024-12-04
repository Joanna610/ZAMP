#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH
#include <list>
#include "Vector3D.hh"
#include "RawCuboidData.hh"

class Configuration {

  std::list<RawCuboidData> _Objects;
  std::list<std::string> _Plugins;

public:

  RawCuboidData operator [](unsigned int Ind); // { auto it = _Objects.begin(); std::advance(it, 2);}

  Configuration() = default;
  void AddObject(RawCuboidData obj);
  void AddPlugin(std::string plugin);

  void showObjects();
  void showPlugins();

  
  std::string AddObjs();
  int getListSize();
  int getPluginListSize();
  std::string getPlugin(int index);

};

#endif

#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH
#include <list>
#include "Vector3D.hh"
#include "DataFromXML.hh"




class Configuration {

  std::list<DataFromXML> _Objects;

public:

  Configuration() = default;
  void AddObject(DataFromXML obj);

  void showObjects();
  void ClearObject(); // usuwało obecne obiekty
  void CleanObjects();
  std::string getMessage();
  int getListSize();
  };

#endif

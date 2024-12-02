#include <iostream>
#include <sstream>
#include "Interp4Move.hh"
#include <unistd.h> 


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0), _Road_Length(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << "   " << GetCmdName() << " " << ObjectName << " " << _Speed_mmS << " " << _Road_Length << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{

  AbstractMobileObj* cube = rScn.FindMobileObj(this->ObjectName.c_str());
  cout << "czesc: "<< cube->GetName()<<endl;
  Vector3D position = cube->GetPositoin_m();
  for(int i = 0; i< this->_Road_Length; ++i){
    position[2] = position[2]+i;
    cube->SetPosition_m(position);

    rComChann.TranslateObj(cube->GetName(), cube->GetPositoin_m());
    cout << cube->GetPositoin_m()<<endl;
    usleep(50000);
  }
  // cout << "================== UWAGA NAZWA CUBA "
  // cube.GetName();
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  std::string line;
  std::getline(Strm_CmdsList, line);
  std::istringstream strumien(line);
  std::string word;
  strumien >> ObjectName;
  // ObjectName = word;
  strumien >> word;
  _Speed_mmS = std::stod(word);
  strumien >> word;
  _Road_Length = std::stod(word);
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}

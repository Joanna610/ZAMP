#include <iostream>
#include <sstream>
#include <cctype>

#include "Interp4Rotate.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}


/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _AngularSpeed(0), _AngleOfRotation(0), _NameOdAxis("X0")
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << "   " << GetCmdName() << " " << ObjectName<< " " << _NameOdAxis << " " << _AngularSpeed  << " " << _AngleOfRotation << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
      usleep(_AngularSpeed*10000);
          cout<< "Start watku w Rotate: "<<std::this_thread::get_id() << endl;

        // ComChannel* CmChnl = static_cast<ComChannel*>(&rComChann);


      rComChann.LockAccess();

  AbstractMobileObj* cube = rScn.FindMobileObj(this->ObjectName.c_str());

  double rot1 = cube->GetAng_Pitch_deg();
  double rot2 = cube->GetAng_Roll_deg();
  double rot3 = cube->GetAng_Yaw_deg();
  Vector3D position = cube->GetPositoin_m();
    rComChann.UnlockAccess();


  for(int i = 0; i < AMOUNT_OF_RATATION; ++i){
  //   cout << "wchodze do petli"<<endl;
      rComChann.LockAccess();

    rot3 += 1;
    if( _NameOdAxis == "OZ"){
      cube->SetAng_Roll_deg(rot3);
    }
    else if(_NameOdAxis == "OY"){
      cube->SetAng_Pitch_deg(rot3);
    }
    else if(_NameOdAxis == "OX"){
      cube->SetAng_Yaw_deg(rot3);
    }
    
    position[0] += 0.01;
    cube->SetPosition_m(position);
    rComChann.UpdateObj(cube->GetName(), cube->GetPositoin_m(), Vector3D(cube->GetAng_Pitch_deg(), cube->GetAng_Roll_deg(), cube->GetAng_Yaw_deg()));
    rComChann.UnlockAccess();

  //   cout << cube->GetPositoin_m()<<endl;
  usleep(_AngularSpeed*10000);
  }

  // // usleep(100000);
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  std::string line;
  std::getline(Strm_CmdsList, line);
  
  std::istringstream strumien(line);
  std::string word;
  strumien >> word;
  ObjectName = word;
  strumien >> word;
  _NameOdAxis = word;
  strumien >> word;
  _AngularSpeed = std::stod(word);
  strumien >> word;
  _AngleOfRotation = std::stod(word);
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  NazwaOsi SzybkoscKatowa[st/s] KatObrotu[st]" << endl;
}

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
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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

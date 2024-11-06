#include <iostream>
#include <sstream>
#include "Interp4Set.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set()
{
  Wsp[0] = 0;
  Wsp[1] = 0;
  Wsp[2] = 0;
  Kat[0] = 0;
  Kat[1] = 0;
  Kat[2] = 0;
}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << "   " << GetCmdName() << " " << NazwaObiektu << " "<< Wsp[0] << " " << Wsp[1] << " "<< Wsp[2] << " "<< Kat[0] << " "<< Kat[1] << " "<< Kat[2] << endl;
}

/*!
 *
 */
// void Interp4Set::SetCmd(double WspX, double WspY, double WspZ, double KatOX, double KatOY, double KatOZ)
// {
//   this->Wsp[0] = WspX;
//   this->Wsp[1] = WspY;
//   this->Wsp[2] = WspZ;
//   this->Kat[0] = KatOX;
//   this->Kat[1] = KatOY;
//   this->Kat[2] = KatOZ;
// }

/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
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
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList) // tutaj jeszcze dla False jak sie nie uda wgrac
{
  std::string line;
  std::getline(Strm_CmdsList, line);
  std::istringstream strumien(line);
  std::string word;
  strumien >> word;
  NazwaObiektu = word;
  strumien >> word;
  Wsp[0] = std::stod(word);
  strumien >> word;
  Wsp[1] = std::stod(word);
  strumien >> word;
  Wsp[2] = std::stod(word);
  strumien >> word;
  Kat[0] = std::stod(word);
  strumien >> word;
  Kat[1] = std::stod(word);
  strumien >> word;
  Kat[2] = std::stod(word);

  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu WspX WspY WspZ KatOX KatOY KatOZ" << endl;
}

#include "ComChannel.hh"

using namespace std;

void ComChannel::Init(int Socket){
  this->_Socket = Socket;
}

int ComChannel::GetSocket() const {
    return this->_Socket;
}

      
void ComChannel::LockAccess() {
    this->_Mutex.lock();
}
/*!
* \brief Otwiera dostęp do gniazda.
*/
void ComChannel::UnlockAccess() {
  this->_Mutex.unlock();
}

void ComChannel::AddObjToServer(std::string Name, Vector3D Shift, Vector3D Scale,Vector3D Trans, Vector3D RGB, Vector3D Rot) {
  std::ostringstream str;
  str<<"AddObj Name="<<Name<<" Shift="<<Shift<<" Scale="<<Scale<<" Trans_m="<<Trans<<" RGB="<<RGB<<" RotXYZ_deg="<<Rot<<std::endl;
  msg = str.str();
  data = msg.c_str();
  // this->_Mutex.lock();
  Send(data);
  // this->_Mutex.unlock();
}

void ComChannel::UpdateObj(std::string Name, Vector3D Trans, Vector3D Rot) {
  std::ostringstream str;
  str<<"UpdateObj Name="<<Name<<" Trans_m="<<Trans<<" RotXYZ_deg="<<Rot<<std::endl;
  msg = str.str();

  data = msg.c_str();
  cout <<data<<endl;

  Send(data);

}

/*!
* \brief Udostępnia mutex w trybie modyfikacji.
*
*  Udostępnia mutex w trybie modyfikacji.
*  Jest to przydatne, gdy planowany jest inny typ zamknięcie,
*  np. poprzez klasę std::lock_gaurd, która daje możliwość
*  bezpieczniejszego zamknięcia.
*/
std::mutex& ComChannel::UseGuard() {
    static std::mutex guard;
    return guard;
}
    
int ComChannel::Send( const char *sMesg)
{
  cout<< "SOKET: "<<_Socket<<endl;
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(_Socket,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}


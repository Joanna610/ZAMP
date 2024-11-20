#include "ComChannel.hh"

using namespace std;

void ComChannel::Init(int Socket){
  this->_Socket = Socket;
}

int ComChannel::GetSocket() const {
    return this->_Socket;
}

      
void ComChannel::LockAccess() {

}
/*!
* \brief Otwiera dostęp do gniazda.
*/
void ComChannel::UnlockAccess() {

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


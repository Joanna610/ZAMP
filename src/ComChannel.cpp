#include "ComChannel.hh"

using namespace std;

void ComChannel::Init(int Socket){
    struct sockaddr_in  DaneAdSerw;

    bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);


    this->_Socket = socket(AF_INET,SOCK_STREAM,0);

    if (Socket < 0) {
        cerr << "*** Blad otwarcia gniazda." << endl;
        return;
    }

    if (connect(Socket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
    {
        cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
        return;
    }
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
    


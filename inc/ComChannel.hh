#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

/*!
 * \file 
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractComChannel
 *
 *  Zawiera definicję klasy abstrakcyjnej AbstractComChannel.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */


#include <mutex>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>

#include "Port.hh"
#include "AbstractComChannel.hh"


   /*!
    * \brief Definiuje interfejs kanału komunikacyjnego z serwerem graficznym.
    *
    * Definiuje interfejs kanału komunikacyjnego z serwerem graficznym.
    * Interfejs ma pozwalać na bezpieczną komunikację w programie wielowątkowym.
    */
    class ComChannel: public AbstractComChannel {
      int _Socket;

     public:

      // virtual ~ComChannel() {}
      
      /*!
       * \brief Inicjalizuje destryptor gniazda.
       *
       * Inicjalizuje destryptora pliku skojarzonego z połączeniem sieciowym z serwerem.
       * \param[in] Socket - zawiera poprawny deskryptor.
       */
       virtual void Init(int Socket) override;
      /*!
       * \brief Udostępnia deskryptor pliku skojarzonego z połączeniem sieciowym z serwerem.
       *
       *  Udostępnia deskryptor skojarzonego z połączeniem sieciowym z serwerem.
       * \return Deskryptor pliku.
       */
       virtual int GetSocket() const override;
      /*!
       * \brief Zamyka dostęp gniazda.
       */
       virtual void LockAccess() override;
      /*!
       * \brief Otwiera dostęp do gniazda.
       */
       virtual void UnlockAccess() override;
       /*!
        * \brief Udostępnia mutex w trybie modyfikacji.
        *
        *  Udostępnia mutex w trybie modyfikacji.
        *  Jest to przydatne, gdy planowany jest inny typ zamknięcie,
        *  np. poprzez klasę std::lock_gaurd, która daje możliwość
        *  bezpieczniejszego zamknięcia.
        */
       virtual std::mutex &UseGuard() override;

       int Send(const char *sMesg);
    };


#endif

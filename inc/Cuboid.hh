#ifndef CUBOID_HH
#define CUBOID_HH


/*!
 * \file 
 * \brief Zawiera definicję klasy abstrakcyjnej AbstractMobileObj
 *
 *  Zawiera definicję klasy abstrakcyjnej AbstractMobileObj.
 *  Wyznacza ona niezbędny interfejs klas pochodnych.
 */

#include "Vector3D.hh"
#include "AbstractMobileObj.hh"

   /*!
    * \brief Definiuje interfejs dla obiektów mobilnych.
    *
    * Definiuje interfejs dla obiektów mobilnych.
    * Zakładamy, że przód obiektu jest wskazywany przez strzałkę osi OX.
    * Nazwy metod są obowiązujące.
    */
    class Cuboid: public AbstractMobileObj {

      Vector3D _Rotation;
      Vector3D _Position;
      std::string _Name;

     public:
        // Cuboid() : _Rotation(), _Position(), _Name("Unnamed") {}
        Cuboid(){
          _Rotation = 0;
          _Position = 0;
          _Name = "";
        }
        Cuboid(AbstractMobileObj* obj) {
          this->_Name = obj->GetName();
          this->_Rotation = (obj->GetAng_Roll_deg(), obj->GetAng_Pitch_deg(), obj->GetAng_Yaw_deg());
          this->_Position = obj->GetPositoin_m();
        }

        Cuboid& operator=(const Cuboid&);
       virtual ~Cuboid() {}
      
       /*!
        * \brief Udostępnia wartość kąta \e roll.
        *
        *  Udostępnia wartość kąta \e pitch reprezentuje rotację
        *  zgodnie z ruchem wskazówek zegara wokół osi \e OX.
        *  \return Wartość kąta \e roll wyrażona w stopniach.
        */
       virtual double GetAng_Roll_deg() const override;
       /*!
        * \brief Udostępnia wartość kąta \e yaw.
        *
        *  Udostępnia wartość kąta \e pitch reprezentuje rotację
        *  zgodnie z ruchem wskazówek zegara wokół osi \e OY.
        *  \return Wartość kąta \e pitch wyrażona w stopniach.
        */
       virtual double GetAng_Pitch_deg() const override;
       /*!
        * \brief Udostępnia wartość kąta \e yaw.
        *
        *  Udostępnia wartość kąta \e yaw reprezentuje rotację
        *  zgodnie z ruchem wskazówek zegara wokół osi \e OZ.
        *  \return Wartość kąta \e yaw wyrażona w stopniach.
        */
       virtual double GetAng_Yaw_deg() const override;

       /*!
        * \brief Zmienia wartość kąta \e roll.
        *
        *  Zmienia wartość kąta \e roll.
        *  \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
        */
       virtual void SetAng_Roll_deg(double Ang_Roll_deg) override;
       /*!
        * \brief Zmienia wartość kąta \e pitch.
        *
        *  Zmienia wartość kąta \e pitch.
        *  \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
        */
       virtual void SetAng_Pitch_deg(double Ang_Pitch_deg) override;
       /*!
        * \brief Zmienia wartość kąta \e yaw.
        *
        *  Zmienia wartość kąta \e yaw.
        *  \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
        */
       virtual void SetAng_Yaw_deg(double Ang_Yaw_deg) override;

       /*!
        * \brief Udostępnia współrzędne aktualnej pozycji obiektu.
        *
        * Udostępnia współrzędne aktualnej pozycji obiektu
        * \return Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
        *         że współrzędne wyrażone są w metrach.
        */
       virtual const Vector3D & GetPositoin_m() const override;
       /*!
        * \brief Zmienia współrzędne aktualnej pozycji obiektu.
        *
        * Zmienia współrzędne aktualnej pozycji obiektu.
        * \param[in] rPos - nowe współrzędne obiektu. Przyjmuje się,
        *         że współrzędne wyrażone są w metrach.
        */
       virtual void SetPosition_m(const Vector3D &rPos)override;

       /*!
        * \brief Zmienia nazwę obiektu.
        *
        *  Zmienia nazwę obiektu, która go identyfikuje.
        *  \param[in]  sName - nowa nazwa obiektu.
        */
        virtual void SetName(const char* sName) override;
       /*!
        * \brief Udostępnia nazwę obiektu.
        *  Udostępnia nazwę identyfikującą obiekt.
        *  \return Nazwa obiektu.
        */
        virtual const std::string & GetName() const override;

        void PrintCuboid() const;
    };



#endif

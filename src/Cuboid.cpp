#include "Cuboid.hh"

 double Cuboid::GetAng_Roll_deg() {
    return _Rotation[0];
 }
/*!
* \brief Udostępnia wartość kąta \e yaw.
*
*  Udostępnia wartość kąta \e pitch reprezentuje rotację
*  zgodnie z ruchem wskazówek zegara wokół osi \e OY.
*  \return Wartość kąta \e pitch wyrażona w stopniach.
*/
double Cuboid::GetAng_Pitch_deg(){
    return _Rotation[1];
}
/*!
* \brief Udostępnia wartość kąta \e yaw.
*
*  Udostępnia wartość kąta \e yaw reprezentuje rotację
*  zgodnie z ruchem wskazówek zegara wokół osi \e OZ.
*  \return Wartość kąta \e yaw wyrażona w stopniach.
*/
double Cuboid::GetAng_Yaw_deg() {
    return _Rotation[2];
}

/*!
* \brief Zmienia wartość kąta \e roll.
*
*  Zmienia wartość kąta \e roll.
*  \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
*/
void Cuboid::SetAng_Roll_deg(double Ang_Roll_deg){
    _Rotation[0] = Ang_Roll_deg;
}
/*!
* \brief Zmienia wartość kąta \e pitch.
*
*  Zmienia wartość kąta \e pitch.
*  \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
*/
void Cuboid::SetAng_Pitch_deg(double Ang_Pitch_deg) {
    _Rotation[1] = Ang_Pitch_deg;
}
/*!
* \brief Zmienia wartość kąta \e yaw.
*
*  Zmienia wartość kąta \e yaw.
*  \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
*/
void Cuboid::SetAng_Yaw_deg(double Ang_Yaw_deg) {
    _Rotation[2] = Ang_Yaw_deg;
}

/*!
* \brief Udostępnia współrzędne aktualnej pozycji obiektu.
*
* Udostępnia współrzędne aktualnej pozycji obiektu
* \return Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
*         że współrzędne wyrażone są w metrach.
*/
const Vector3D & Cuboid::GetPositoin_m() const{
    return _Position;
}
/*!
* \brief Zmienia współrzędne aktualnej pozycji obiektu.
*
* Zmienia współrzędne aktualnej pozycji obiektu.
* \param[in] rPos - nowe współrzędne obiektu. Przyjmuje się,
*         że współrzędne wyrażone są w metrach.
*/
void Cuboid::SetPosition_m(const Vector3D &rPos){
    _Position = rPos;
}

/*!
* \brief Zmienia nazwę obiektu.
*
*  Zmienia nazwę obiektu, która go identyfikuje.
*  \param[in]  sName - nowa nazwa obiektu.
*/
void Cuboid::SetName(const char* sName){
    _Name = sName;
}
/*!
* \brief Udostępnia nazwę obiektu.
*  Udostępnia nazwę identyfikującą obiekt.
*  \return Nazwa obiektu.
*/
const std::string & Cuboid::GetName() const {
    return _Name;
}
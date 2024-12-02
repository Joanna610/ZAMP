#ifndef DATAFROMXML_HH
#define DATAFROMXML_HH

#include "Vector3D.hh"

using namespace std;

// struct data{
//     std::string _Name;
//     Vector3D _Shift;
//     Vector3D _Scale;
//     Vector3D _RGB;
//     Vector3D _RotXYZ_deg;
//     Vector3D _Trans_m;
// };

struct RawCuboidData{
    
    std::string _Name;
    Vector3D _Shift;
    Vector3D _Scale;
    Vector3D _RGB;
    Vector3D _RotXYZ_deg;
    Vector3D _Trans_m;

// public:
    RawCuboidData(){
        _Name = "";
        _Shift = 0;
        _Scale = 0;
        _RGB = 0;
        _RotXYZ_deg = 0;
        _Trans_m = 0;
    }
    ~RawCuboidData() = default;

    // void AddObject(std::string Name, Vector3D Shift, Vector3D Scale, Vector3D RGB, Vector3D RotXYZ_deg, Vector3D Trans_m);

    // std::string GetName(){ return this->_Name;}
    // Vector3D GetShift(){ return this->_Shift;}
    // Vector3D GetScale(){ return this->_Scale;}
    // Vector3D GetRGB(){ return this->_RGB;}
    // Vector3D GetRotXYZDeg(){ return this->_RotXYZ_deg;}
    // Vector3D GetTransM(){ return this->_Trans_m;}


    // void SetName(std::string Name){ this->_Name = Name;}
    // void SetShift(Vector3D Shift){ this->_Shift = Shift;}
    // void SetScale(Vector3D Scale){ this->_Scale = Scale;}
    // void SetRGB(Vector3D RGB){ this->_RGB = RGB;}
    // void SetRotXYZDeg(Vector3D RotXYZ){ this->_RotXYZ_deg = RotXYZ;}
    // void SetTransM(Vector3D TransM){ this->_Trans_m = TransM;}

    // void CleanObject();
    // void showData();

    void AddObject(const char * Name, Vector3D Shift, Vector3D Scale, Vector3D RGB, Vector3D RotXYZ_deg, Vector3D Trans_m){
        _Name = Name;
        _Shift = Shift;
        _Scale = Scale;
        _RGB = RGB;
        _RotXYZ_deg = RotXYZ_deg;
        _Trans_m = Trans_m;
    }

    void CleanObject(){
        _Name = "";
        _Shift = 0;
        _Scale = 0;
        _RGB = 0;
        _RotXYZ_deg = 0;
        _Trans_m = 0;
    }

    void showData(){
        cout << "\nName: "<< _Name;
        cout << "\nShift: "<< _Shift;
        cout << "\nScale: "<< _Scale;
        cout << "\nRGB: "<< _RGB;
        cout << "\nRotXYZ_deg: "<< _RotXYZ_deg;
        cout << "\nTrans_m: "<< _Trans_m;
    }

    RawCuboidData & operator =( const RawCuboidData & x )
    {
        _Name = x._Name;
        _Shift = x._Shift;
        _Scale = x._Scale;
        _RGB = x._RGB;
        _RotXYZ_deg = x._RotXYZ_deg;
        _Trans_m = x._Trans_m;
        return * this;
    }
};

#endif


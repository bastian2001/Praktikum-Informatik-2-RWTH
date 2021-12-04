#pragma once
#include "Fahrzeug.h"
#include "iostream"

using namespace std;
class PKW :
    public Fahrzeug
{
private:
    double p_dVerbrauch;
public:
    PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);
    PKW() = delete;  // PKWs nur mit Namen und Maximalgeschwindigkeit
    ~PKW();

    void vSimulieren() override;
    void vAusgeben(ostream& o) const override;

    PKW& operator=(const PKW& p);
};


ostream& operator<<(ostream& o, const PKW& p);
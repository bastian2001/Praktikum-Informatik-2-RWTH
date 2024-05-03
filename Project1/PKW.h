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
    PKW();
    PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);
    ~PKW();

    void vSimulieren() override;
    void vAusgeben(ostream& o) const override;
    void vEinlesen(istream& i) override;

    void vZeichnen(const Weg& aWeg) const override;

    PKW& operator=(const PKW& p);
};


ostream& operator<<(ostream& o, const PKW& p);
istream& operator>>(istream& i, PKW& p);
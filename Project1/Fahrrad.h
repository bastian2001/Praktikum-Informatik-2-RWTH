#pragma once
#include "Fahrzeug.h"
class Fahrrad :
    public Fahrzeug
{
private:

public:
    double dGeschwindigkeit() const override;
    Fahrrad(string sName, double dMaxGeschwindigkeit);
    Fahrrad();

    Fahrrad& operator=(const Fahrrad& f);

    void vAusgeben(ostream& o) const override;
    void vEinlesen(istream& i) override;

    void vZeichnen(const Weg& aWeg) const override;
};

istream& operator>>(istream& i, Fahrrad& f);
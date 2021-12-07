#pragma once
#include "Fahrzeug.h"
class Fahrrad :
    public Fahrzeug
{
private:

public:
    double dGeschwindigkeit() const override;
    Fahrrad(string sName, double dMaxGeschwindigkeit);
    Fahrrad() = delete; // Fahrräder nur mit Namen und Maximalgeschwindigkeit

    Fahrrad& operator=(const Fahrrad& f);

    void vAusgeben(ostream& o) const override;

    void vZeichnen(const Weg& aWeg) const override;
};

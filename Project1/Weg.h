#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include "Tempolimit.h"
using namespace std;

class Fahrzeug;
class Weg :
    public Simulationsobjekt
{
private:
    const double p_dLaenge;
    list <unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit;
public:
    Weg();
    Weg(string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::autobahn);
    Weg(Weg&) = delete;

    double getTempolimit() const;
    void vSimulieren() override;
    void vAusgeben(ostream& o) const override;
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug);
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);
    static void vKopf();

    double getLaenge() const;
};


ostream& operator<<(ostream& o, const Weg& w);
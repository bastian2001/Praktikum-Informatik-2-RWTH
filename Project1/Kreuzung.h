#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include "Weg.h"
#include <string>

using namespace std;

class Kreuzung :
    public Simulationsobjekt
{
private:
    double p_dTankstelle;
    list<shared_ptr<Weg>> p_pWege;
public:
    Kreuzung();
    Kreuzung(string sName, double dTankstelle);
    Kreuzung(Kreuzung&) = delete;

    void vAddWeg(shared_ptr<Weg> pWeg);
    void vTanken(Fahrzeug& aFzg);
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dZeit = 0);
    void vSimulieren();

    void vAusgeben(ostream& o) const override;
    void vEinlesen(istream& i) override;
    void vWegeZeichnen() const;

    double getTankstelle();

    Weg& pZufaelligerWeg(const Weg& aWeg) const;

    static void vVerbinde(string sName01, string sName10, double dLaenge, shared_ptr<Kreuzung> pKreuzung0, shared_ptr<Kreuzung> pKreuzung1, Tempolimit eTempolimit, bool bUeberholverbot = true);

    Kreuzung& operator=(const Kreuzung& k);
};

istream& operator>>(istream& i, Kreuzung& k);
ostream& operator<<(ostream& o, const Kreuzung& k);
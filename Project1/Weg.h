#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include "Tempolimit.h"
#include "vertagt_liste - Vorlage.h"
using namespace std;

class Fahrzeug;
class Weg :
    public Simulationsobjekt
{
private:
    const double p_dLaenge;
    vertagt::VListe <unique_ptr<Fahrzeug>> p_pFahrzeuge; //Weg ist "Besitzer" der Fahrzeuge
    const Tempolimit p_eTempolimit;
public:
    //Konstruktoren
    Weg();
    Weg(string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::autobahn);
    Weg(Weg&) = delete;

    //Getter
    double getTempolimit() const;
    double getLaenge() const;

    //Operationen
    void vSimulieren() override;
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug); //Fahren
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit); //Parken bis dStartzeit
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);

    //Nutzerausgabe/anzeige
    void vAusgeben(ostream& o) const override;
    void vFahrzeugeZeichnen() const;

    static void vKopf();

};


ostream& operator<<(ostream& o, const Weg& w);
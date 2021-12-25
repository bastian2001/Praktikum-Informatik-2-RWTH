#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include "Tempolimit.h"
#include "vertagt_liste - Vorlage.h"
using namespace std;

class Kreuzung;
class Fahrzeug;
class Weg :
    public Simulationsobjekt
{
private:
    const double p_dLaenge;
    vertagt::VListe <unique_ptr<Fahrzeug>> p_pFahrzeuge; //Weg ist "Besitzer" der Fahrzeuge
    const Tempolimit p_eTempolimit;
    const bool p_bUeberholverbot;
    double p_dSchranke;
    weak_ptr<Weg> p_pRueckweg;
    const weak_ptr<Kreuzung> p_pZielkreuzung;
public:
    //Konstruktoren
    //Weg();
    Weg(string sName, double dLaenge, weak_ptr<Kreuzung> pZielkreuzung, Tempolimit eTempolimit = Tempolimit::autobahn, bool bUeberholverbot = true);
    Weg(Weg&) = delete;

    //Getter
    double getTempolimit() const;
    double getLaenge() const;
    double getSchranke() const;
    shared_ptr<Weg> getRueckweg() const;
    shared_ptr<Kreuzung> getZielkreuzung() const;
    //Setter
    void setSchranke(double dSchranke);
    void setRueckweg(weak_ptr<Weg> pRueckweg);

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
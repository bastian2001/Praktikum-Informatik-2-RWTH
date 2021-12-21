#include "Weg.h"
#include "Fahrzeug.h"
#include "vertagt_liste - Vorlage.h"

#include <iomanip>
#include <iostream>
using namespace std;

Weg::Weg() :
    Simulationsobjekt::Simulationsobjekt(""),
    p_dLaenge(0),
    p_eTempolimit(Tempolimit::autobahn)
{
    cout << "Weg ohne Namen mit ID " << p_iID << " erstellt." << endl;
}

Weg::Weg(string sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot):
    Simulationsobjekt::Simulationsobjekt(sName),
    p_dLaenge(dLaenge),
    p_eTempolimit(eTempolimit),
    p_bUeberholverbot(bUeberholverbot)
{
    cout << "Weg " << sName << " mit Tempolimit " << (int)eTempolimit << " und ID, " << p_iID << (bUeberholverbot ? "mit" : "ohne") << " Überholverbot, erstellt." << endl;
}

double Weg::getTempolimit() const
{
    return (double)p_eTempolimit;
}

void Weg::vSimulieren()
{
    //Aktualisiert die Fahrzeugliste
    p_pFahrzeuge.vAktualisieren();
    for (auto& pFahrzeug : p_pFahrzeuge)
    {
        //Simuliert jedes enthaltene Fahrzeug
        pFahrzeug->vSimulieren();
    }
    //Aktualisiert danach die Fahrzeugliste erneut
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAusgeben(ostream& o) const
{
    o << setfill(' ') << setw(3) << p_iID << "  "
        << setw(10) << setiosflags(ios::left) << p_sName << ' '
        << setw(10) << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::fixed) << p_dLaenge << ' ' << '(';
    for (auto& pFahrzeug : p_pFahrzeuge) {
        o << pFahrzeug->getName() << ", "; //Gibt jeden Fahrzeugnamen aus
    }
    o << ")\n";
    for (auto& p : p_pFahrzeuge) {
        cout << *p; //Da der Weg die Fahrzeuge besitzt, ist eine Ausgabe von außen nicht möglich. Also wird jedes Fahrzeug auf dem Weg mit augegeben
    }
}

void Weg::vFahrzeugeZeichnen() const
{
    for (auto& fahrzeug : p_pFahrzeuge) {
        fahrzeug->vZeichnen(*this);
    }
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug) //Nimmt ein Fahrzeug fahrend auf
{
    cout << pFahrzeug->getName() << " wird fahrend auf " << p_sName << " gesetzt" << endl;
    pFahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(move(pFahrzeug));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit)//Nimmt ein Fahrzeug parkend auf
{
    cout << pFahrzeug->getName() << " wird parkend auf " << p_sName << " gesetzt und fährt nach " << dStartzeit << "h los." << endl;
    pFahrzeug->vNeueStrecke(*this, dStartzeit);
    p_pFahrzeuge.push_front(move(pFahrzeug));
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg) // Gibt ein Fahrzeug ab
{
    auto it = p_pFahrzeuge.begin();
    while(it != p_pFahrzeuge.end()) {
        if (**it == aFzg) { //Sucht das Fahrzeug
            auto pFahrzeug = move(*it);
            p_pFahrzeuge.erase(it); // Entfernt es. Es wird beim nächsten Simulationsschritt bei vAktualisieren dann tatsächlich entfernt
            return move(pFahrzeug); //unique_ptr wird aber bereits jetzt übergeben
        }
        it++;
    }
    return nullptr;
}

void Weg::vKopf()
{
    cout << setfill(' ') << setw(3) << "ID" << "  "
        << setw(10) << setiosflags(ios::left) << "Name" << ' '
        << setw(10) << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::fixed) << "Laenge" << ' '
        << resetiosflags(ios::fixed) << "Fahrzeuge" << endl;
    cout << setfill('-') << setw(77) << '-' << endl;
}

double Weg::getLaenge() const
{
    return p_dLaenge;
}

double Weg::getSchranke() const
{
    if (p_bUeberholverbot)
        return p_dSchranke;
    return p_dLaenge;
}

void Weg::setSchranke(double dSchranke)
{
    p_dSchranke = dSchranke;
}


ostream& operator<<(ostream& o, const Weg& w) {
    w.vAusgeben(o);
    return o;
}
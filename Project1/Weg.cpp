#include "Weg.h"
#include "Fahrzeug.h"

#include <iomanip>
#include <iostream>
using namespace std;

Weg::Weg() :
    Simulationsobjekt::Simulationsobjekt(""),
    p_dLaenge(0),
    p_eTempolimit(Tempolimit::autobahn)
{
}

Weg::Weg(string sName, double dLaenge, Tempolimit eTempolimit):
    Simulationsobjekt::Simulationsobjekt(sName),
    p_dLaenge(dLaenge),
    p_eTempolimit(eTempolimit)
{
}

double Weg::getTempolimit() const
{
    return (double)p_eTempolimit;
}

void Weg::vSimulieren()
{
    for (auto& pFahrzeug : p_pFahrzeuge)
    {
        pFahrzeug->vSimulieren();
    }
}

void Weg::vAusgeben(ostream& o) const
{
    o << setfill(' ') << setw(3) << p_iID << "  "
        << setw(10) << setiosflags(ios::left) << p_sName << ' '
        << setw(10) << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::fixed) << p_dLaenge << ' ' << '(';
    for (auto& pFahrzeug : p_pFahrzeuge) {
        o << pFahrzeug->getName() << ", ";
    }
    o << ")\n";
    for (auto& p : p_pFahrzeuge) {
        cout << *p;
    }
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug)
{
    cout << "Fahrzeug " << pFahrzeug->getName() << " wird fahrend auf " << p_sName << " gesetzt" << endl;
    pFahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(move(pFahrzeug));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit)
{
    cout << "Fahrzeug " << pFahrzeug->getName() << " wird parkend auf " << p_sName << " gesetzt und fährt nach " << dStartzeit << "h los." << endl;
    pFahrzeug->vNeueStrecke(*this, dStartzeit);
    p_pFahrzeuge.push_front(move(pFahrzeug));
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


ostream& operator<<(ostream& o, const Weg& w) {
    w.vAusgeben(o);
    return o;
}
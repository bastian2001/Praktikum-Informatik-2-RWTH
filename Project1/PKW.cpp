#include "PKW.h"

extern double dGlobaleZeit;

PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen):
	p_dVerbrauch(dVerbrauch),
	Fahrzeug(sName, dMaxGeschwindigkeit, dTankvolumen)
{
	cout << "PKW " << sName << " mit Maximalgeschwindigkeit " << dMaxGeschwindigkeit << ", Verbrauch " << dVerbrauch << " l/100km, Tankvolumen " << dTankvolumen << " l und ID " << p_iID << " erstellt\n";
}

PKW::~PKW()
{
	cout << "PKW " << p_sName << " gelöscht\n";
}

void PKW::vSimulieren()
{
	if (dGlobaleZeit - p_dZeit > 0)
		// Es wird angenommen, dass für den gesamten Simulationsschritt noch genug Reserve da ist
		if (p_dTankinhalt > 0) {
			double dStreckeVorher = p_dGesamtStrecke;
			Fahrzeug::vSimulieren();
			double dDeltaStrecke = p_dGesamtStrecke - dStreckeVorher;
			p_dTankinhalt -= dDeltaStrecke * p_dVerbrauch / 100;
		}
		else {
			p_dZeit = dGlobaleZeit;
		}
}

void PKW::vAusgeben(ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	o << ' ' << setprecision(2) << setw(12) << p_dVerbrauch * p_dGesamtStrecke / 100 << endl;
}

PKW& PKW::operator=(const PKW& p)
{
	Fahrzeug::operator=(p);
	p_dVerbrauch = p.p_dVerbrauch;
	return *this;
}

ostream& operator<<(ostream& o, const PKW& p) {
	p.vAusgeben(o);
	return o;
}

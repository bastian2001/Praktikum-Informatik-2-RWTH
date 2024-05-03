#include "Fahrrad.h"
#include "SimuClient.h"

double Fahrrad::dGeschwindigkeit() const
{
	double dSpeed = p_dMaxGeschwindigkeit;
	for (int i = 20; i < p_dGesamtStrecke; i+=20) {
		dSpeed *= .9;
	}
	if (dSpeed < 12)
		dSpeed = 12;
	return dSpeed;
}

Fahrrad::Fahrrad(string sName, double dMaxGeschwindigkeit) :
	Fahrzeug(sName, dMaxGeschwindigkeit, 0) //Tankvolumen 0, da Fahrrad
{
	p_bRespectSpeedLimit = false; // 7.4.4.2 "Max-Geschwindigkeit, die nur für den PKW gilt"

	cout << "Fahrrad " << sName << " mit maximaler Geschwindigkeit " << dMaxGeschwindigkeit << " und ID " << p_iID << " erstellt\n";
}

Fahrrad::Fahrrad():
	Fahrzeug()
{
	p_bRespectSpeedLimit = false;
	cout << "Unbenanntes Fahrzeug mit ID " << p_iID << " erstellt.\n";
}

Fahrrad& Fahrrad::operator=(const Fahrrad& f)
{
	Fahrzeug::operator=(f);
	return *this;
}

void Fahrrad::vAusgeben(ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	o << endl;
}

void Fahrrad::vEinlesen(istream& i) 
{
	Fahrzeug::vEinlesen(i);
}

void Fahrrad::vZeichnen(const Weg& aWeg) const
{
	bZeichneFahrrad(p_sName, aWeg.getName(), p_dAbschnittStrecke / aWeg.getLaenge(), dGeschwindigkeit());
}

istream& operator>>(istream& i, Fahrrad& f)
{
	f.vEinlesen(i);
	return i;
}
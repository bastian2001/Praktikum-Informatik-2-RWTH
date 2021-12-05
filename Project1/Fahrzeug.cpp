#include "Fahrzeug.h"
#include "Parken.h"
#include "Fahren.h"
#include "Fahrausnahme.h"
#include "Streckenende.h"
#include "Losfahren.h"
#include <string>
#include <iostream>

using namespace std;

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug(string sName, double dMaxGeschwindigkeit, double dTankvolumen) :
	Simulationsobjekt(sName),
	p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0 ? dMaxGeschwindigkeit : 0), //keine negative Maximalgeschwindigkeit
	p_dTankvolumen(dTankvolumen),
	p_dTankinhalt(dTankvolumen / 2)
{
	//cout << "Fahrzeug " << p_sName << " mit Maximalgeschwindigkeit " << p_dMaxGeschwindigkeit << " und ID " << p_iID << " erstellt" << endl;
}

void Fahrzeug::vAusgeben(ostream& o) const
{
	o << setfill(' ') << setw(3) << p_iID << "  "
		<< setw(10) << setiosflags(ios::left) << p_sName << ' '
		<< setw(20) << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::fixed) << p_dMaxGeschwindigkeit << ' '
		<< setw(15) << p_dGesamtStrecke << ' '
		<< setw(10) << p_dTankinhalt;
}

void Fahrzeug::vSimulieren()
{
	double delta = dGlobaleZeit - p_dZeit;
	if (delta > 0) {
		double strecke = 0;
		p_dZeit = dGlobaleZeit;
		try {
			strecke = p_pVerhalten->dStrecke(*this, delta);
		}
		catch (Fahrausnahme& e) {
			e.vBearbeiten();
			return;
		}
		p_dGesamtStrecke += strecke;
		p_dAbschnittStrecke += strecke;
		p_dGesamtZeit += delta;
	}
}

void Fahrzeug::vNeueStrecke(Weg& w)
{
	p_pVerhalten = make_unique<Fahren>(w);
	p_dAbschnittStrecke = 0;
	p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vNeueStrecke(Weg& w, double dStartzeit)
{
	p_pVerhalten = make_unique<Parken>(w, dStartzeit);
	p_dAbschnittStrecke = 0;
}

double Fahrzeug::dTanken(double dLiter) {
	double delta = p_dTankvolumen - p_dTankinhalt;
	if (delta > dLiter)
		delta = dLiter;
	p_dTankinhalt += delta;
	return delta;
}

void Fahrzeug::vKopf() {
	cout << setfill(' ') << setw(3) << "ID" << "  "
		<< setw(10) << setiosflags(ios::left) << "Name" << ' '
		<< setw(20) << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::fixed) << "MaxGeschwindigkeit" << ' '
		<< setw(15) << "Gesamtstrecke" << ' '
		<< setw(10) << "Tankinhalt" << ' '
		<< setw(12) << "Verbrauch" << endl;
	cout << setfill('-') << setw(77) << '-' << endl;
}

double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

bool Fahrzeug::getRespectSpeedLimit() const
{
	return p_bRespectSpeedLimit;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& f)
{
	Simulationsobjekt::operator=(f);
	p_dMaxGeschwindigkeit = f.p_dMaxGeschwindigkeit;
	p_dTankvolumen = f.p_dTankvolumen;
	p_dTankinhalt = p_dTankvolumen / 2; //"Daten, die bei der Erstellung festgelegt werden"
	return *this;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

Fahrzeug::~Fahrzeug()
{
	cout << "Fahrzeug " << p_sName << " mit ID " << p_iID << " gelöscht"  << endl;
}

int Fahrzeug::p_iMaxID = 0;

ostream& operator<<(ostream& o, const Fahrzeug& f) {
	f.vAusgeben(o);
	return o;
}

bool operator<(const Fahrzeug& aFahrzeug1, const Fahrzeug& aFahrzeug2) {
	return aFahrzeug1.p_dGesamtStrecke < aFahrzeug2.p_dGesamtStrecke;
}
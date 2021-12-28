#pragma once

#include <string>
#include <limits>
#include <iomanip>
#include <list>

#include "Simulationsobjekt.h"
#include "Verhalten.h"


using namespace std;
class Fahrzeug : public Simulationsobjekt
{
private:
	double p_dGesamtZeit = 0;
	unique_ptr<Verhalten> p_pVerhalten;
protected:
	double p_dTankvolumen; //nicht mehr const wegen Zuweisungsoperator
	double p_dAbschnittStrecke = 0;
	double p_dTankinhalt = 0;
	double p_dMaxGeschwindigkeit;
	bool p_bRespectSpeedLimit = true;
	double p_dGesamtStrecke = 0;
public:
	//Konstruktoren
	Fahrzeug();
	Fahrzeug(string sName, double dMaxGeschwindigkeit = 0, double dTankvolumen = 55);
	Fahrzeug(Fahrzeug&) = delete;
	~Fahrzeug();

	//Getter
	double getAbschnittStrecke() const;
	bool getRespectSpeedLimit() const;
	double getTankinhalt() const;
	double getGesamtStrecke() const;

	//Operationen
	virtual void vSimulieren();
	void vNeueStrecke(Weg& w);
	void vNeueStrecke(Weg& w, double dStartzeit);
	double dTanken(double dLiter = numeric_limits<double>::infinity());

	virtual double dGeschwindigkeit() const;

	//Nutzerinteraktion
	static void vKopf();
	virtual void vZeichnen(const Weg& aWeg) const = 0; //aWeg eigentlich unnötig, da das Fahrzeug über das Verhalten weiß, auf welchem Weg es sich befindet. Daher vDraw
	virtual void vAusgeben(ostream& o) const override;
	virtual void vEinlesen(istream& i) override;

	Fahrzeug& operator=(const Fahrzeug& f);
	bool operator==(const Fahrzeug& f) const;
};

ostream& operator<<(ostream& o, const Fahrzeug& f);
istream& operator>>(istream& i, Fahrzeug& f);
bool operator<(const Fahrzeug& aFahrzeug1, const Fahrzeug& aFahrzeug2);


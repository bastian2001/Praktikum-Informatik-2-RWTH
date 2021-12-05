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
	double p_dTankvolumen; //nicht mehr const wegen Zuweisungsoperator
	double p_dGesamtZeit = 0;
	unique_ptr<Verhalten> p_pVerhalten;
protected:
	double p_dAbschnittStrecke = 0;
	double p_dTankinhalt = 0;
	double p_dMaxGeschwindigkeit;
	bool p_bRespectSpeedLimit = true;

public:
	virtual double dGeschwindigkeit() const;
	double p_dGesamtStrecke = 0;

	Fahrzeug(string sName = "", double dMaxGeschwindigkeit = 0, double dTankvolumen = 55);
	// Fahrzeuge können zwar ohne Namen erstellt werden, da das aber keinen Sinn ergibt, wird dies in den Subklassen blockiert
	Fahrzeug(Fahrzeug&) = delete;
	~Fahrzeug();

	virtual void vAusgeben(ostream& o) const override;
	virtual void vSimulieren();

	//virtual void vDraw() = 0;
	virtual void vZeichnen(const Weg& aWeg) const = 0; //aWeg eigentlich unnötig, da das Fahrzeug über das Verhalten weiß, auf welchem Weg es sich befindet. Daher vDraw

	void vNeueStrecke(Weg& w);
	void vNeueStrecke(Weg& w, double dStartzeit);

	double dTanken(double dLiter = numeric_limits<double>::infinity());

	static int p_iMaxID;
	static void vKopf();

	double getAbschnittStrecke() const;
	bool getRespectSpeedLimit() const;
	double getTankinhalt() const;

	Fahrzeug& operator=(const Fahrzeug& f);
};

ostream& operator<<(ostream& o, const Fahrzeug& f);
bool operator<(const Fahrzeug& aFahrzeug1, const Fahrzeug& aFahrzeug2);


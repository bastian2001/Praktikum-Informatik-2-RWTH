#pragma once

#include <iostream>
#include <string>

using namespace std;

class Simulationsobjekt
{
private:
	static int p_iMaxID;
protected:
	const int p_iID;
	string p_sName; // nicht mehr const, wegen Zuweisungsoperator
	double p_dZeit = 0;
public:
	Simulationsobjekt(string sName = "");
	Simulationsobjekt(Simulationsobjekt&) = delete;
	~Simulationsobjekt();

	virtual void vSimulieren() = 0;
	virtual void vAusgeben(ostream& o) const = 0;

	bool operator==(Simulationsobjekt& f);
	Simulationsobjekt& operator=(const Simulationsobjekt &s);

	string getName(); //damit p_sName protected bleiben kann
};


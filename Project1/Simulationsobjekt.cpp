#include "Simulationsobjekt.h"


int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(string sName):
	p_sName(sName),
	p_iID(p_iMaxID++)
{
	//cout << "Simulationsobjekt " << p_sName << " mit ID " << p_iID << " erstellt\n";
}

Simulationsobjekt::~Simulationsobjekt()
{
	//cout << "Simulationsobjekt " << p_sName << " mit ID " << p_iID << " gelöscht\n";
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& f) const
{
	return this->p_iID == f.p_iID;
}

Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt &s)
{
	this->p_sName = s.p_sName;
	return *this;
}

string Simulationsobjekt::getName() const
{
	return p_sName;
}

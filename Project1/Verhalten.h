#pragma once

#include "Weg.h"

class Verhalten
{
protected:
	Weg& p_aWeg;
public:
	Verhalten() = delete;
	Verhalten(Weg& aWeg);

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;
	//const Weg& getWeg() const;
};
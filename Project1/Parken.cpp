#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"
#include "Weg.h"
#include <iostream>

using namespace std;

extern double dGlobaleZeit;

Parken::Parken(Weg& aWeg, double dStartzeitpunkt):
	Verhalten::Verhalten(aWeg),
	p_dStartzeitpunkt(dStartzeitpunkt)
{
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (p_dStartzeitpunkt < dGlobaleZeit + .000001)
		throw Losfahren(aFzg, p_aWeg);
	return 0;
}

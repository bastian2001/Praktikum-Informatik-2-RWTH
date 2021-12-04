#include "Parken.h"
#include "Fahrzeug.h"
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
	if (p_dStartzeitpunkt > dGlobaleZeit)
		return 0;
	cout << aFzg.getName() << " fährt los!\n";
	return 0;
}

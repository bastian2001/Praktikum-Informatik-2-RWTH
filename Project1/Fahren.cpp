#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"


Fahren::Fahren(Weg& aWeg):
	Verhalten::Verhalten(aWeg)
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double dStreckeResult = p_aWeg.getLaenge() - aFzg.getAbschnittStrecke(); // So lange ist der Weg noch
	dStreckeResult = dStreckeResult < aFzg.dGeschwindigkeit()* dZeitIntervall ? dStreckeResult : aFzg.dGeschwindigkeit() * dZeitIntervall; // So schnell kann das Fahrzeug --> Minimum davon
	dStreckeResult = dStreckeResult < p_aWeg.getTempolimit()* dZeitIntervall ? dStreckeResult : p_aWeg.getTempolimit() * dZeitIntervall; // So schnell darf das Fahrzeug --> Minimum davon
	return dStreckeResult;
}
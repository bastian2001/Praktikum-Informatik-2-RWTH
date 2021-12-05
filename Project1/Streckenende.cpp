#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

void Streckenende::vBearbeiten()
{
	cout << "Streckenende-Ausnahme " << p_aFahrzeug.getName() << " " << p_aWeg.getName() << endl;
}

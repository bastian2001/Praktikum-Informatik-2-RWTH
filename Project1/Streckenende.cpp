#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

//Am Streckende wird der Pointer abgegeben, das Fahrzeug wird gelöscht
void Streckenende::vBearbeiten()
{
	cout << "Streckenende-Ausnahme " << p_aFahrzeug.getName() << " " << p_aWeg.getName() << endl;
	p_aWeg.pAbgabe(p_aFahrzeug);
}

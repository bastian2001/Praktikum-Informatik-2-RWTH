#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug& aFzg, const Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

void Losfahren::vBearbeiten()
{
	cout << "Losfahren-Ausnahme " << p_aFahrzeug.getName() << " " << p_aWeg.getName() << endl;
}

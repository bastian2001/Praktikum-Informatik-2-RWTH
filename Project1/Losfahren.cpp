#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

void Losfahren::vBearbeiten()
{
	cout << "Losfahren-Ausnahme " << p_aFahrzeug.getName() << " " << p_aWeg.getName() << endl;
	unique_ptr<Fahrzeug> pFahrzeug = p_aWeg.pAbgabe(p_aFahrzeug);
	p_aWeg.vAnnahme(move(pFahrzeug));
}

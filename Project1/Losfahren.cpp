#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

void Losfahren::vBearbeiten()
{
	cout << "Losfahren-Ausnahme " << p_aFahrzeug.getName() << " " << p_aWeg.getName() << endl;
	unique_ptr<Fahrzeug> pFahrzeug = p_aWeg.pAbgabe(p_aFahrzeug); //Das parkende Fahrzeug wird vom Weg an pFahrzeug abgegeben
	p_aWeg.vAnnahme(move(pFahrzeug));                             //damit es als fahrendes Fahrzeug wieder gespeichert werden kann
}

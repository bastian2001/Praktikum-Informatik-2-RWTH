#include "Streckenende.h"
#include "Kreuzung.h"

extern double dGlobaleZeit;

Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg) :
	Fahrausnahme(aFzg, aWeg)
{
}

//Am Streckende wird der Pointer abgegeben, das Fahrzeug wird gelöscht
void Streckenende::vBearbeiten()
{
	cout << "Streckenende-Ausnahme " << p_aFahrzeug.getName() << " " << p_aWeg.getName() << endl;
	p_aWeg.getZielkreuzung()->vTanken(p_aFahrzeug);
	p_aWeg.getZielkreuzung()->pZufaelligerWeg(p_aWeg).vAnnahme(move(p_aWeg.pAbgabe(p_aFahrzeug)));
	cout << "ZEIT: " << dGlobaleZeit << "\nKREUZUNG: " << p_aWeg.getZielkreuzung()->getName() << ", " << p_aWeg.getZielkreuzung()->getTankstelle()
		<< "\nWECHSEL: " << p_aWeg.getName() << " -> " << p_aWeg.getRueckweg()->getName() << "\nFAHRZEUG:\n" << p_aFahrzeug << '\n';
}

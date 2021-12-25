#include "Kreuzung.h"
#include "Fahrzeug.h"
#include <random>

Kreuzung::Kreuzung(string sName, double dTankstelle):
	Simulationsobjekt::Simulationsobjekt(sName),
	p_dTankstelle(dTankstelle)
{
}

void Kreuzung::vAddWeg(shared_ptr<Weg> pWeg)
{
	p_pWege.push_back(pWeg);
}

void Kreuzung::vVerbinde(string sName01, string sName10, double dLaenge, shared_ptr<Kreuzung> pKreuzung0, shared_ptr<Kreuzung> pKreuzung1, Tempolimit eTempolimit, bool bUeberholverbot)
{
	shared_ptr<Weg> pWeg01 = make_shared<Weg>(sName01, dLaenge, pKreuzung1, eTempolimit, bUeberholverbot);
	shared_ptr<Weg> pWeg10 = make_shared<Weg>(sName10, dLaenge, pKreuzung0, eTempolimit, bUeberholverbot);
	pWeg01->setRueckweg(pWeg10);
	pWeg10->setRueckweg(pWeg01);
	pKreuzung0->vAddWeg(pWeg01);
	pKreuzung1->vAddWeg(pWeg10);
}

void Kreuzung::vTanken(Fahrzeug& aFzg)
{
	p_dTankstelle = (p_dTankstelle > 0.000001 ? p_dTankstelle -= aFzg.dTanken() : 0) > .000001 ? p_dTankstelle : 0;
	/*if (p_dTankstelle > 0.000001) {
		p_dTankstelle -= aFzg.dTanken();
		if (p_dTankstelle <= 0.000001)
			p_dTankstelle = 0
	}*/

}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dZeit)
{
	if (p_pWege.empty())
		throw "Kein Weg für die Annahme von " + pFahrzeug->getName() + " verfügbar.";
	vTanken(*pFahrzeug);
	p_pWege.front()->vAnnahme(move(pFahrzeug), dZeit);
}

void Kreuzung::vSimulieren()
{
	for (auto& pWeg : p_pWege) {
		pWeg->vSimulieren();
	}
}

void Kreuzung::vAusgeben(ostream& o) const
{
	o << "\nKreuzung: " << p_sName << "\nID: " << p_iID << "\nAbgehende Wege: ";
	for (auto& pWeg : p_pWege) {
		cout << pWeg->getName() << ", ";
	}
	cout << "\nTankstelleninhalt: " << p_dTankstelle << endl;

	for (auto& pWeg : p_pWege) {
		cout << *pWeg << ", ";
	}
	cout << endl;
}

void Kreuzung::vWegeZeichnen() const
{
	for (auto& pWeg : p_pWege) {
		pWeg->vFahrzeugeZeichnen();
	}
}

double Kreuzung::getTankstelle()
{
	return p_dTankstelle;
}

Weg& Kreuzung::pZufaelligerWeg(const Weg& aWeg) const
{
	int length = (int) p_pWege.size();
	if (length == 1) {
		shared_ptr<Weg> temp = aWeg.getRueckweg();
		Weg& tempWeg = *temp;
		return tempWeg;
	}
	static std::mt19937 wegDevice(0);
	std::uniform_int_distribution<int> dist(0, length - 2); //je -1 und "offset"
	int pos = dist(wegDevice);
	auto it = p_pWege.cbegin();
	if (*(aWeg.getRueckweg()) == **it)
		it++;
	for (int i = 0; i < pos; i++) {
		it++;
		if (*(aWeg.getRueckweg()) == **it)
			it++;
	}
	return **it;
}

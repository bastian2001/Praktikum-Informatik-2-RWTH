#include "Simulation.h"
#include "Kreuzung.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include <fstream>
#include <vector>
using namespace std;
extern istream& operator>>(istream&, Fahrrad&);
extern istream& operator>>(istream&, Kreuzung&);
extern istream& operator>>(istream& i, PKW& p);

extern double dGlobaleZeit;

void Simulation::vEinlesen(istream& i, bool bMitGrafik)
{
	int zeile = 1;

	while (!i.eof()) {
		string type;
		try {
			i >> type;
		}
		catch (exception e) {
			string message;
			message = e.what();
			message += zeile;
		}
		if (type == "KREUZUNG") {
			shared_ptr<Kreuzung> k = make_shared<Kreuzung>();
			i >> *k;
			p_pKreuzungen[k->getName()] = k;
		}
		else if (type == "STRASSE") {
			string nameKr0, nameKr1, nameW01, nameW10;
			double laenge;
			bool ueberholverbot;
			int tempolimit;
			Tempolimit t;
			try {
				i >> nameKr0 >> nameKr1 >> nameW01 >> nameW10 >> laenge >> tempolimit >> ueberholverbot;
			}
			catch (exception e) {
				string message = "Mind. ein Parameter der Strasse falsch ";
				message += to_string(zeile);
				throw runtime_error(message);
			}
			switch (tempolimit) {
			case 1:
				t = Tempolimit::innerorts;
				break;
			case 2:
				t = Tempolimit::landstrasse;
				break;
			case 3:
				t = Tempolimit::autobahn;
				break;
			default:
				string message = "Kein gueltiges Tempolimit ";
				message += to_string(zeile);
				throw runtime_error(message);
			}
			try {
				Kreuzung::vVerbinde(nameW01, nameW10, laenge, p_pKreuzungen.at(nameKr0), p_pKreuzungen.at(nameKr1), t, ueberholverbot);
			}
			catch (exception e) {
				string message = e.what();
				message += " " + to_string(zeile);
				throw runtime_error(message);
			}
			catch (...) {
				string message = "Sonstiges Problem in Zeile ";
				message += zeile;
				throw runtime_error(message);
			}
		}
		else if (type == "PKW") {
			unique_ptr<PKW> p = make_unique<PKW>();
			string nameStart;
			double zeitLos;
			try {
				i >> *p >> nameStart >> zeitLos;
				p_pKreuzungen.at(nameStart)->vAnnahme(move(p), zeitLos);
			}
			catch (exception e) {
				string message = e.what();
				message += " ";
				message += to_string(zeile);
				throw runtime_error(message);
			}
		}
		else if (type == "FAHRRAD") {
			unique_ptr<Fahrrad> f = make_unique<Fahrrad>();
			string nameStart;
			double zeitLos;
			try {
				i >> *f >> nameStart >> zeitLos;
				p_pKreuzungen.at(nameStart)->vAnnahme(move(f), zeitLos);
			}
			catch (exception e) {
				string message = e.what();
				message += " ";
				message += to_string(zeile);
				throw runtime_error(message);
			}
		}
		else if (type == "") {
			cout << "Ende des Streams erreicht\n";
			return;
		}
		else {
			string message = "Kein gueltiges Simulationsobjekt ";
			message += to_string(zeile);
			throw runtime_error(message);
		}
		zeile++;
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	double start = dGlobaleZeit;
	while (dGlobaleZeit <= start + dDauer + .000001){
		for (auto& kreuzung : p_pKreuzungen) {
			kreuzung.second->vSimulieren();
		}
		dGlobaleZeit += dZeitschritt;
	}
}

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

void Simulation::vEinlesen(istream& i)
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
			kreuzungen[k->getName()] = k;
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
				Kreuzung::vVerbinde(nameW01, nameW10, laenge, kreuzungen.at(nameKr0), kreuzungen.at(nameKr1), t, ueberholverbot);
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
			i >> *p >> nameStart >> zeitLos;
			try {
				kreuzungen.at(nameStart)->vAnnahme(move(p), zeitLos);
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
				kreuzungen.at(nameStart)->vAnnahme(move(f), zeitLos);
			}
			catch (exception e) {
				string message = e.what();
				message += " ";
				message += to_string(zeile);
				throw runtime_error(message);
			}
		}
		else {
			string message = "Kein gueltiges Simulationsobjekt ";
			message += to_string(zeile);
			throw runtime_error(message);
		}
		string s;
		try {
			getline(i, s);
		}
		catch (exception e) {
			string message;
			message = e.what();
			message += " ";
			message += zeile;
			throw runtime_error(message);
		}
		zeile++;
	}
}

void Simulation::vSimulieren()
{
}

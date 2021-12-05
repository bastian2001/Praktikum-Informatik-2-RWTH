#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include "SimuClient.h"

using namespace std;

//void vAufgabe_1();
//void vAufgabe_1a();
//void vAufgabe_2();
//void vAufgabe_3();
//void vAufgabe_AB1();
//void vAufgabe_4();
//void vAufgabe_5();
//void vAufgabe_6();
void vAufgabe_6b(); // mit Grafik-Implementation

double dGlobaleZeit = 0.0;
double dEpsilon = 0.001;


int main() {
	vAufgabe_6b();
}

void vAufgabe_6b() 
{
	Weg hinweg("Hinweg", 500);
	Weg rueckweg("Rueckweg", 500);
	auto bmw = make_unique<PKW>("BMW", 160, 9, 60);
	auto audi = make_unique<PKW>("Audi", 250, 10, 100);
	auto fahrrad = make_unique<Fahrrad>("BMX", 55);
	auto krassesf = make_unique<Fahrrad>("KrassesFah", 100);

	hinweg.vAnnahme(move(bmw));
	hinweg.vAnnahme(move(audi), 3);
	hinweg.vAnnahme(move(fahrrad));
	hinweg.vAnnahme(move(krassesf), 2);


	Fahrzeug::vKopf();
	Weg::vKopf();
	cout << "einen Schritt (s)imulieren (-> Dauer)\n(M)ehrere Schritte simulieren (-> Schrittweite, Anzahl, Verzoegerung)\n(a)usgeben (-> H/R)\nGlobale (Z)eit ausgeben\n(K)�pfe erneut anzeigen" << endl;


	bInitialisiereGrafik(800, 500);
	int pKoordinaten[] = { 700, 250, 100, 250 };
	bZeichneStrasse("Hinweg", "Rueckweg", 500, 2, pKoordinaten);

	char c; //multipurpose
	double d; //multipurpose
	int i;
	int i2;
	while (true) {
		vSetzeZeit(dGlobaleZeit);
		hinweg.vFahrzeugeZeichnen();
		rueckweg.vFahrzeugeZeichnen();
		cin >> c;
		switch (c) {
		case 'm':
		case 'M':
			cin >> d;
			cin >> i;
			cin >> i2;
			for (int j = 0; j < i; j++) {
				dGlobaleZeit += d;
				vSetzeZeit(dGlobaleZeit);
				hinweg.vSimulieren();
				rueckweg.vSimulieren();
				hinweg.vFahrzeugeZeichnen();
				rueckweg.vFahrzeugeZeichnen();
				vSleep(i2);
			}
			break;
		case 's':
		case 'S':
			cin >> d;
			dGlobaleZeit += d;
			hinweg.vSimulieren();
			rueckweg.vSimulieren();
			break;
		case 'a':
		case 'A':
			cin >> c;
			switch (c) {
			case 'h':
			case 'H':
				hinweg.vAusgeben(cout);
				break;
			case 'r':
			case 'R':
				rueckweg.vAusgeben(cout);
				break;
			}
			break;
		case 'z':
		case 'Z':
			cout << dGlobaleZeit << endl;
			break;
		case 'k':
		case 'K':
			Fahrzeug::vKopf();
			Weg::vKopf();
			break;
		}
	}
}

/*void vAufgabe_6() {
	Weg boxgraben("Boxgraben", 200, Tempolimit::innerorts);
	Weg autobahn("A 1", 800);
	vector<unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(make_unique<PKW>("BMW", 160, 9, 60));
	fahrzeuge.push_back(make_unique<PKW>("Audi", 250, 10, 100));
	fahrzeuge.push_back(make_unique<Fahrrad>("BMX", 55));
	fahrzeuge.push_back(make_unique<Fahrrad>("Krasses F.", 100));
	Fahrzeug::vKopf();
	Weg::vKopf();
	cout << "(s)imulieren (-> Dauer)\n(a)usgeben (-> ID)\nvAnnahme (F)ahren (-> ID, Weg-Anfangsbuchstabe)\nvAnnahme (P)arken (-> ID, Startzeitpunkt, Weg-Anfangsbuchstabe)\nGlobale (Z)eit ausgeben\n(K)�pfe erneut anzeigen" << endl;

	while (true) {
		char operation;
		char streetLetter;
		double deltaT;
		int id;
		double startzeit;
		cin >> operation;
		switch (operation) {
		case 's':
		case 'S':
			cin >> deltaT;
			dGlobaleZeit += deltaT;
			autobahn.vSimulieren();
			boxgraben.vSimulieren();
			break;
		case 'a':
		case 'A':
			cin >> id;
			id -= 2;
			if (id == -2)
				boxgraben.vAusgeben(cout);
			else if (id == -1)
				autobahn.vAusgeben(cout);
			if (id < fahrzeuge.size()) {
				try {
					fahrzeuge[id]->vAusgeben(cout);
				}
				catch (exception e) {
					cout << "Bitte nur Fahrzeuge abfragen, die nicht auf dem Weg sind (Besitz des unique_ptr wurde abgegeben)." << endl;
				}
			}
			break;
		case 'f':
		case 'F':
			cin >> id;
			id-= 2;
			cin >> streetLetter;
			if (id < 0)
				continue;
			if (id < fahrzeuge.size()) {
				switch (streetLetter) {
				case 'b':
				case 'B':
					boxgraben.vAnnahme(move(fahrzeuge[id]));
					break;
				case 'a':
				case 'A':
					autobahn.vAnnahme(move(fahrzeuge[id]));
					break;
				}
			}
			break;
		case 'p':
		case 'P':
			cin >> id;
			cin >> startzeit;
			id -= 2;
			cin >> streetLetter;
			if (id < 0)
				continue;
			if (id < fahrzeuge.size()) {
				switch (streetLetter) {
				case 'b':
				case 'B':
					boxgraben.vAnnahme(move(fahrzeuge[id]), startzeit);
					break;
				case 'a':
				case 'A':
					autobahn.vAnnahme(move(fahrzeuge[id]), startzeit);
					break;
				}
			}
			break;
		case 'z':
		case 'Z':
			cout << dGlobaleZeit << endl;
			break;
		case 'k':
		case 'K':
			Fahrzeug::vKopf();
			Weg::vKopf();
			break;
		}
	}
}*/

/*void vAufgabe_5() {
	Weg weg("Templergraben", 300);
	vector<unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(make_unique<PKW>("BMW", 160, 9, 60));
	fahrzeuge.push_back(make_unique<PKW>("Audi", 250, 10, 100));
	fahrzeuge.push_back(make_unique<Fahrrad>("BMX", 55));
	Fahrzeug::vKopf();
	Weg::vKopf();
	cout << "(s)imulieren (-> Dauer), (a)usgeben (-> ID), vAnnahme (F)ahren (-> ID), vAnnahme (P)arken (-> ID, Startzeitpunkt), Globale (Z)eit ausgeben, (K)�pfe erneut anzeigen" << endl;
	while (true) {
		char operation;
		double deltaT;
		int id;
		double startzeit;
		cin >> operation;
		switch (operation) {
		case 's':
		case 'S':
			cin >> deltaT;
			dGlobaleZeit += deltaT;
			weg.vSimulieren();
			break;
		case 'a':
		case 'A':
			cin >> id;
			id--;
			if (id == -1)
				weg.vAusgeben(cout);
			if (id < fahrzeuge.size()) {
				try {
					fahrzeuge[id]->vAusgeben(cout);
				}
				catch (exception e) {
					cout << "Bitte nur Fahrzeuge abfragen, die nicht auf dem Weg sind (Besitz des unique_ptr wurde abgegeben)." << endl;
				}
			}
			break;
		case 'f':
		case 'F':
			cin >> id;
			id--;
			if (id == -1)
				continue;
			if (id < fahrzeuge.size())
				weg.vAnnahme(move(fahrzeuge[id]));
			break;
		case 'p':
		case 'P':
			cin >> id;
			cin >> startzeit;
			id--;
			if (id == -1)
				continue;
			if (id < fahrzeuge.size())
				weg.vAnnahme(move(fahrzeuge[id]), startzeit);
			break;
		case 'z':
		case 'Z':
			cout << dGlobaleZeit << endl;
			break;
		case 'k':
		case 'K':
			Fahrzeug::vKopf();
			Weg::vKopf();
			break;
		}
	}
}*/

/*void vAufgabe_4() {
	Weg weg("Mein Weg", 100, Tempolimit::innerorts);
	Weg::vKopf();
	cout << weg;
}*/

/*void vAufgabe_3() {
	vector<unique_ptr<Fahrzeug>> f;
	for (int i = 0; i < 2; i++) {
		cout << "Bitte Fahrzeugtyp (F, P) eingeben, dann den Namen und dann die Maximalgeschwindigkeit. Beim PKW auch den Verbrauch und das Tankvolumen (-1 => 55)" << endl;
		char c;
		cin >> c;
		string sName;
		cin >> sName;
		double dMaxGeschwindigkeit;
		cin >> dMaxGeschwindigkeit;
		switch (c) {
		case 'F':
			f.push_back(make_unique<Fahrrad>(sName, dMaxGeschwindigkeit));
			break;
		case 'P':
			double dVerbrauch;
			cin >> dVerbrauch;
			double dTankvolumen;
			cin >> dTankvolumen;
			if (dTankvolumen < 0)
				dTankvolumen = 55;
			f.push_back(make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen));
			break;
		}
	}
	bool bFilled = false;
	for (;;) {
		double dDeltaTime;
		cin >> dDeltaTime;
		if (dDeltaTime <= 0) {
			return;
		}
		else {
			dGlobaleZeit += dDeltaTime;
			Fahrzeug::vKopf();
			auto it = f.cbegin();
			while (it != f.cend()) {
				(*it)->vSimulieren();
				if (!bFilled && dGlobaleZeit >= 3) {
					(*it)->dTanken();
				}
				cout << *(*it) << endl;
				it++;
			}
			if (!bFilled && dGlobaleZeit >= 3) {
				bFilled = true;
			}
		}
		if (*(f[0]) < *(f[1])) {
			cout << "Das Fahrzeug der ID 0 ist weniger weit gefahren" << endl;
		}
	}
}*/

/*void vAufgabe_2() {
	vector<unique_ptr<Fahrzeug>> f;
	for (int i = 0; i < 2; i++) {
		cout << "Bitte Fahrzeugtyp (F, P) eingeben, dann den Namen und dann die Maximalgeschwindigkeit. Beim PKW auch den Verbrauch und das Tankvolumen (-1 => 55)" << endl;
		char c;
		cin >> c;
		string sName;
		cin >> sName;
		double dMaxGeschwindigkeit;
		cin >> dMaxGeschwindigkeit;
		switch (c) {
		case 'F':
			f.push_back(make_unique<Fahrrad>(sName, dMaxGeschwindigkeit));
			break;
		case 'P':
			double dVerbrauch;
			cin >> dVerbrauch;
			double dTankvolumen;
			cin >> dTankvolumen;
			if (dTankvolumen < 0)
				dTankvolumen = 55;
			f.push_back(make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen));
			break;
		}
	}
	bool bFilled = false;
	for (;;) {
		double dDeltaTime;
		cin >> dDeltaTime;
		if (dDeltaTime <= 0) {
			return;
		}
		else {
			dGlobaleZeit += dDeltaTime;
			Fahrzeug::vKopf();
			auto it = f.cbegin();
			while (it != f.cend()) {
				(*it)->vSimulieren();
				if (!bFilled && dGlobaleZeit >= 3) {
					(*it)->dTanken();
				}
				(*it)->vAusgeben();
				it++;
			}
			if (!bFilled && dGlobaleZeit >= 3) {
				bFilled = true;
			}
		}
	}
}*/

/*void vAufgabe_1a() {
	vector<unique_ptr<Fahrzeug>> v;
	for (int i = 0; i < 3; i++) {
		cout << "Bitte Name und H�chstgeschwindigkeit f�r Fahrzeug " << i + 1 << " eingeben" << endl;
		string name = "";
		double speed;
		cin >> name;
		cin >> speed;
		v.push_back(make_unique<Fahrzeug>(name, speed));
	}
	Fahrzeug::vKopf();
	cout << endl;
	for (double d = 0.1; d < 2; d *= 1.3) {
		dGlobaleZeit += d;
		v[0]->vSimulieren();
		v[2]->vSimulieren();
		v[1]->vSimulieren();
		v[2]->vSimulieren();
		v[0]->vAusgeben();
		cout << endl;
		v[1]->vAusgeben();
		cout << endl;
		v[2]->vAusgeben();
		cout << endl;
	}
}

void vAufgabe_1() {
	vector<unique_ptr<Fahrzeug>> v;
	v.push_back(make_unique<Fahrzeug>("BMW123 4", 30));
	v.push_back(make_unique<Fahrzeug>("au"));
	v.push_back(make_unique<Fahrzeug>());
	v.push_back(make_unique<Fahrzeug>());
	Fahrzeug::vKopf();
	cout << endl;
	v[0]->vAusgeben();
	cout << endl;
	v[1]->vAusgeben();
	cout << endl;
}*/

/*void vAufgabe_AB1() {

	int l = 0; // Laufindex f�r gezielte AUsgabe
	vector<int> ausgabe{ 13 };
	double dTakt = 0.4;

	std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
	vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6));
	vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
	{
		auto itL = find(ausgabe.begin(), ausgabe.end(), l);
		if (itL != ausgabe.end()) {
			std::cout << std::endl << l << " Globalezeit = " << dGlobaleZeit << std::endl;
			Fahrzeug::vKopf();
		}

		for (int i = 0; i < vecFahrzeuge.size(); i++)
		{
			vecFahrzeuge[i]->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0) < dTakt / 2)
			{
				vecFahrzeuge[i]->dTanken();
			}
			if (itL != ausgabe.end()) {
				std::cout << *(vecFahrzeuge[i]) << endl;
			}
		}
		l++;
	}
	char c;
	std::cin >> c;
}*/
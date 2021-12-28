#pragma once
#include <istream>
#include <string>
#include <map>
#include "Kreuzung.h"

using namespace std;
class Simulation
{
private:
	map<string, shared_ptr<Kreuzung>> p_pKreuzungen;
public:
	void vEinlesen(istream& i, bool bMitGrafik = false);
	void vSimulieren(double dDauer, double dZeitschritt);
};


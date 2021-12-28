#pragma once
#include <istream>
#include <string>
#include <map>
#include "Kreuzung.h"

using namespace std;
class Simulation
{
private:
	map<string, shared_ptr<Kreuzung>> kreuzungen;
public:
	void vEinlesen(istream& i);
	void vSimulieren();
};


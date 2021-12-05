#pragma once
#include <exception>
#include "Weg.h"
#include "Fahrzeug.h"

using namespace std;


class Fahrausnahme :
	public exception
{
protected:
	Fahrzeug& p_aFahrzeug;
	Weg& p_aWeg;
public:
	Fahrausnahme(Fahrzeug& aFzg, Weg& aWeg);
	Fahrausnahme() = delete;

	virtual void vBearbeiten() = 0;
};


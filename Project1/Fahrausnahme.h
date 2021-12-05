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
	const Weg& p_aWeg;
public:
	Fahrausnahme(Fahrzeug& aFzg, const Weg& aWeg);
	Fahrausnahme() = delete;

	virtual void vBearbeiten() = 0;
};


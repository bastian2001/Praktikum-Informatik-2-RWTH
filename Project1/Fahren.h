#pragma once
#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
class Fahren :
    public Verhalten
{
public:
    Fahren(Weg& aWeg);
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};


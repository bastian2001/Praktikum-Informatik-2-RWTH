#pragma once
#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
class Parken :
    public Verhalten
{
private:
    double p_dStartzeitpunkt;
public:
    Parken(Weg& aWeg, double dStartzeitpunkt);

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};


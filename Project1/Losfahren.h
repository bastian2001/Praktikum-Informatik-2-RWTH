#pragma once
#include "Fahrausnahme.h"
class Losfahren :
    public Fahrausnahme
{
public:
    Losfahren() = delete;
    Losfahren(Fahrzeug& aFzg, Weg& aWeg);

    void vBearbeiten() override;
};


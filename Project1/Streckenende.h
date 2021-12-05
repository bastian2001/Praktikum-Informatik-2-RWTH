#pragma once
#include "Fahrausnahme.h"
class Streckenende :
    public Fahrausnahme
{
public:
    Streckenende() = delete;
    Streckenende(Fahrzeug& aFzg, Weg& aWeg);

    void vBearbeiten() override;
};


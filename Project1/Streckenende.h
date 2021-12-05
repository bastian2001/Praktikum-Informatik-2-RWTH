#pragma once
#include "Fahrausnahme.h"
class Streckenende :
    public Fahrausnahme
{
public:
    Streckenende() = delete;
    Streckenende(Fahrzeug& aFzg, const Weg& aWeg);

    void vBearbeiten() override;
};


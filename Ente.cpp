#pragma once
#include "Ente.h"
Gerenciador_Grafico* Ente::pGG = nullptr;

Ente::Ente() : id(0), pFigura(new sf::Sprite())
{

}

Ente::~Ente()
{
    if (pFigura)
    {
        delete pFigura;
        pFigura = nullptr;
    }
}

int Ente::getId() const
{
    return id;
}
void Ente::setGerenciadorGrafico(Gerenciador_Grafico* g)
{
    pGG = g;
}

Gerenciador_Grafico* Ente::getGerenciadorGrafico()
{
    return pGG;
}

void Ente::desenhar()
{
    Ente::pGG->desenharEnte(this);
}

sf::Sprite* Ente::getFigura() const
{
    return pFigura;
}
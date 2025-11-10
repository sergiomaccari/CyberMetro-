#pragma once
#include "Gerenciador_Grafico.h"
#include <stdlib.h>
#include <time.h>

class Ente
{
protected:
    int id;
    static Gerenciador_Grafico* pGG;
    sf::Sprite* pFigura;

public:
    Ente();
    virtual ~Ente();

    virtual void executar() = 0;
    int getId() const;
    static void setGerenciadorGrafico(Gerenciador_Grafico* g);
    static Gerenciador_Grafico* getGerenciadorGrafico();
    void desenhar();
    sf::Sprite* getFigura() const;
};
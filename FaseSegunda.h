#pragma once
#include "Fase.h"
#include "Robo_CEO.h"
#include "Choquinho.h"

namespace Fases {
    class FaseSegunda : public Fase
    {
    protected:
        void criarChefe(float x, float y);
        void criarObstaculoDificil(float x, float y);
    public:
        FaseSegunda(Jogador* jogador1, Jogador* jogador2);
        virtual ~FaseSegunda();
        virtual void criarInimigos();
        virtual void criarObstaculos();
    };
}
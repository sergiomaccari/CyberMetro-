#pragma once
#include "Entidade.h"

namespace Personagens
{
    class Personagem : public Entidades::Entidade {
    protected:
        int n_vidas;
        float velocidade;
        sf::Vector2f movimento;
    public:
        Personagem(float xi, float yi);
        Personagem();
        virtual ~Personagem();
        void setMovimentoY(float yn);
        sf::Vector2f getMovimento();
        virtual void mover() = 0;
        virtual void salvar()  = 0;
        float getVelocidade();
        void setVelocidade(float vn);
        void operator++();
        void operator--();
    };
}
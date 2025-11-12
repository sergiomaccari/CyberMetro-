#pragma once
#include "Entidade.h"

namespace Personagens
{
    class Personagem : public Entidades::Entidade {
    protected:
        int n_vidas;
        int n_vidas_max;
        float velocidade;
        sf::Vector2f movimento;
        sf::RectangleShape healthBarFundo;
        sf::RectangleShape healthBarAtual;
        static const sf::Vector2f TAMANHO_BARRA_VIDA;
        void atualizarBarraVida();

    public:
        Personagem(float xi, float yi);
        Personagem();
        virtual ~Personagem();
        void setMovimentoY(float yn);
        sf::Vector2f getMovimento();
        virtual void mover() = 0;
        virtual void salvar() = 0;
        float getVelocidade();
        void setVelocidade(float vn);
        void operator++();
        void operator--();
        const sf::RectangleShape& getBarraFundo() const;
        const sf::RectangleShape& getBarraAtual() const;
    };
}
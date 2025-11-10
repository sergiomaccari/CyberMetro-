#pragma once
#include "Fase.h"
#include "Gelinho.h" 
#include "Choquinho.h" 
#include "Robo_Senior.h" 


namespace Fases {
    class FasePrimeira : public Fase
    {
    private:
        sf::Texture texturaTileset;
        std::vector<std::vector<unsigned int>> gridMapa;
        const int TILESET_LARGURA_EM_BLOCOS = 8;
        const float TAMANHO_BLOCO_X = 32.0f;
        const float TAMANHO_BLOCO_Y = 32.0f;
        std::vector<sf::Vector2f> posi_robo_junior;
        std::vector<sf::Vector2f> posi_robo_senior;
        std::vector<sf::Vector2f> posi_plataforma;
        std::vector<sf::Vector2f> posi_gelinho;

    protected:
        void criarRoboSenior(float x, float y);
        void criarGelinho(float x, float y);
        void criarObstaculoDificil(float x, float y); 

    public:
        FasePrimeira(Jogador* jogador1, Jogador* jogador2);
        virtual ~FasePrimeira();
        virtual void criarInimigos();
        virtual void criarObstaculos();
        void criarMapa();
        virtual void desenharMapa();
    };
}
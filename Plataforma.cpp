#include "Plataforma.h"
#include <iostream>

using namespace Personagens;

namespace Obstaculos {

    const float Plataforma::altura_plataforma = 32.0f;
    const float Plataforma::largura_plataforma = 32.0f;


    Plataforma::Plataforma(float xi, float yi) : Obstaculo(xi, yi), null_grav(0)
    {
        if (pGG)
        {
            sf::Texture* tex = pGG->getTextura("C:/testegitjogo/testegitjogo-main/Imagens/plataforma.png");
            if (tex)
            {
                pFigura->setTexture(*tex);
                pFigura->setScale(96.0f / tex->getSize().x, 32.0f / tex->getSize().y);
            }
        }
        else
        {
            std::cerr << "Erro: Gerenciador Grafico nao setado para Plataforma!" << std::endl;
        }


        this->x = xi;
        this->y = yi;
        setPosicaoGrafica(this->x, this->y);
        this->danoso = false;
        this->isMovel = true;
    }

    Plataforma::~Plataforma()
    {

    }

    void Plataforma::obstaculizar(Jogador* pj)
    {
		pj->iniciarObstaculoCooldown(sf::seconds(15.0f));
    }

    void Plataforma::salvar()
    {

    }

    void Plataforma::anti_grav()
    {
        null_grav -= grav;
        this->y -= vel_grav;
    }

    void Plataforma::executar()
    {
        vel_grav += grav;
        this->y += vel_grav;
        anti_grav();
        setPosicaoGrafica(this->x, this->y);
    }

}
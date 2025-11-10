#include "Chao.h" 
using namespace Personagens;

namespace Obstaculos 
{
	Chao::Chao(float xi, float yi) : Obstaculo(xi, yi)
	{
		if (pGG)
		{
			sf::Texture* tex = pGG->getTextura("Imagens/chao.png");
			if (tex)
			{
				pFigura->setTexture(*tex);
				pFigura->setScale(LARGURA_CHAO / tex->getSize().x, ALTURA_CHAO / tex->getSize().y);
			}
		}

		this->x = xi;
		this->y = yi;

		setPosicaoGrafica(this->x, this->y);
		danoso = false;
	}

	Chao::~Chao()
	{

	}

	void Chao::obstaculizar(Jogador* pj)
	{

	}

	void Chao::salvar()
	{

	}

	void Chao::executar()
	{

	}
}
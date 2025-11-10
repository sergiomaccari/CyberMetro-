#pragma once
#include <vector>
#include <list>
#include <set>
#include "Jogador.h"
using namespace Entidades;


namespace Personagens {
	class Inimigo;
}
namespace Obstaculos {
	class Obstaculo;
}

namespace Entidades {
	class Projetil;
}


namespace Gerenciadores
{
	class Gerenciador_Colisoes
	{
	private:
		Personagens::Jogador* p1;
		Personagens::Jogador* p2; 
		std::vector<Personagens::Inimigo*> LIs;
		std::list<Obstaculos::Obstaculo*> LOs;
		std::set<Entidades::Projetil*> LPs;

		const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
		void tratarColisoesJogsObstacs();
		void tratarColisoesJogsInimgs();
		void tratarColisoesJogsProjeteis();
		void tratarColisoesInimgsObstacs();
		void tratarColisoesInimgsProjeteis();
		void tratarColisoesInimgsInimgs();
		void tratarColisoesProjeteisObstacs();
		void tratarColisoesObstacsObstacs();


	public:
		Gerenciador_Colisoes(Personagens::Jogador* p1);
		~Gerenciador_Colisoes();

		void setJogador2(Personagens::Jogador* j2);

		void incluirInimigo(Personagens::Inimigo* pi);
		void incluirObstaculo(Obstaculos::Obstaculo* po);
		void incluirProjetil(Entidades::Projetil* pj);

		void limparProjeteis();
		void limparInimigos();
		void limparObstaculos();

		void executar();
	};
}
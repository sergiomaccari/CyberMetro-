#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Obstaculos {
	class Chao : public Obstaculo
	{
	public:
		Chao(float x, float y);
		~Chao();
		void obstaculizar(Jogador* pj);
		void salvar();
		void executar();
	};
}
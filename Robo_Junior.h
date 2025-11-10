#pragma once
#include "Inimigo.h"

namespace Personagens{
    class Robo_Junior : public Inimigo
    {
    protected:
        int volta = 1; // colocar bool e inicializar em outro lugar.
		float xINI; // posição inicial do inimigo?????????????
        float raio;
        int ALCANCE;

    public:
         Robo_Junior(float xi, float yi);
         ~Robo_Junior();
		 void mover() override;
         void danificar(Jogador* pJogador);
         void salvar();
         void executar();
    };
}

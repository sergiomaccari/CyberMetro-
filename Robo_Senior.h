#pragma once
#include "Inimigo.h"

namespace Personagens {
    class Robo_Senior : public Inimigo
    {
    private:
        int tamanho;
    protected:
        int volta;
        float xINI;
        int ALCANCE;

    public:
        Robo_Senior(float xi, float yi);
        ~Robo_Senior();
        void mover();
        void executar();
        void danificar(Jogador* pJogador);
        void salvar();
    };
}
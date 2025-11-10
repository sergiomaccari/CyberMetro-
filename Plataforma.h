#pragma once
#include "Obstaculo.h"

using namespace Personagens;

namespace Obstaculos {
    class Plataforma : public Obstaculo
    {
    private:
        static const float largura_plataforma;
        static const float altura_plataforma;
        float null_grav;

    public:
        Plataforma(float xi, float yi);
        ~Plataforma();

        void obstaculizar(Jogador* pj);
        void salvar();
        void executar();
        void anti_grav();
    };
}
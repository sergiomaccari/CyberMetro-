#pragma once
#include "Entidade.h"


namespace Entidades
{
    class Projetil : public Entidades::Entidade
    {
    private:
        int dano;
        float vx;
        float vy;
        bool DoBem;
        const float FORCA_GRAVIDADE_PROJETIL;

    public:
        Projetil();
        virtual ~Projetil();
        virtual void executar();
        virtual void salvar();
        void setVelocidade(float velX, float velY);
        void setDoBem(bool b);
        bool getDoBem() const;
    };
}
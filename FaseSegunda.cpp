#include "FaseSegunda.h"
#include "Plataforma.h"
#include "Robo_Junior.h"
#include "Chao.h"
namespace Fases {
    FaseSegunda::FaseSegunda(Jogador* jogador1, Jogador* jogador2)
        : Fase(jogador1, jogador2) 
    {
        criarObstaculos();
        criarInimigos();
    }

    FaseSegunda::~FaseSegunda() {}

    void FaseSegunda::criarInimigos()
    {
        criarChefe(800, 600);
    }

    void FaseSegunda::criarObstaculos()
    {
        Gerenciador_Grafico* pGG = Ente::getGerenciadorGrafico();

        criarPlataforma(15*32, 15*32);

        for (int i = 0; i < LARGURA_TELA * 1; i += LARGURA_CHAO)
        {
            criarChao(i, ALTURA_TELA - 10);
        }
    }


    void FaseSegunda::criarChefe(float x, float y)
    {
        Gerenciador_Grafico* pGG_local = Ente::getGerenciadorGrafico();
        if (!pGG_local) return;

        Personagens::Robo_CEO* chefe = new Personagens::Robo_CEO(x, y);
        chefe->setGerenciadorGrafico(pGG_local);
        chefe->setJogador(pJogador1);
        pListaInimigos->inserir(chefe);
    }

    void FaseSegunda::criarObstaculoDificil(float x, float y)
    {
        Gerenciador_Grafico* pGG_local = Ente::getGerenciadorGrafico();
        if (!pGG_local) return;

        Obstaculos::Choquinho* obst = new Obstaculos::Choquinho(x, y);
        obst->setGerenciadorGrafico(pGG_local);
        pListaObstaculos->inserir(obst);
    }
}
#pragma once
#include "Jogador.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"
#include "Menu.h" 

class Jogo
{
private:
    Gerenciador_Grafico gg;
    Menu menu;
    Personagens::Jogador* pJogador1;
    Personagens::Jogador* pJogador2;
    Fases::Fase* faseAtual;
    EstadoJogo estadoAtual;
    void configurarNovaFase(EstadoJogo novoEstado);
    void limparFaseAtual();

public:
    Jogo();
    ~Jogo();
    void executar();
};
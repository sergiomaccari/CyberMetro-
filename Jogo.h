#pragma once
#include "Jogador.h"
#include "Menu.h" 

namespace Fases {
    class Fase;
}

class Jogo
{
private:
    Gerenciador_Grafico gg;
    Menu menu;
    Personagens::Jogador* pJogador1;
    Personagens::Jogador* pJogador2;
    Fases::Fase* faseAtual;
    EstadoJogo estadoAtual;

    EstadoJogo estadoAnterior;

    sf::Font fontePausa;
    std::vector<sf::Text> opcoesPausa;
    int indicePausa;
    sf::RectangleShape fundoPausa;

    void carregarRecursosPausa();
    void processarInputPausa(sf::Event& evento);
    void desenharPausa();
    void salvarJogo();
    void atualizarDestaquePausa();

    void configurarNovaFase(EstadoJogo novoEstado);
    void limparFaseAtual();

public:
    Jogo();
    ~Jogo();
    void executar();
    void voltarAoMenu();
};
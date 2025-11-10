#include "Jogo.h"
#include "FasePrimeira.h" 
#include "FaseSegunda.h"  

Jogo::Jogo()
    : gg(),
    menu(),
    pJogador1(nullptr),
    pJogador2(nullptr),
    faseAtual(nullptr),
    estadoAtual(EstadoJogo::Menu)
{
    Ente::setGerenciadorGrafico(&gg);

    menu.inicializar();
    pJogador1 = new Personagens::Jogador(1);
    pJogador2 = new Personagens::Jogador(2);

    pJogador2->setAtivo(false);
}

Jogo::~Jogo()
{
    limparFaseAtual();
    if (pJogador1) {
        delete pJogador1;
        pJogador1 = nullptr;
    }
    if (pJogador2) {
        delete pJogador2;
        pJogador2 = nullptr;
    }

	std::cout << "Jogo finalizado." << std::endl;

}

void Jogo::configurarNovaFase(EstadoJogo novoEstado)
{
    limparFaseAtual();

    if (novoEstado == EstadoJogo::Jogando)
    {
        faseAtual = new Fases::FasePrimeira(pJogador1, pJogador2);
    }
    else if (novoEstado == EstadoJogo::FaseDois)
    {
        faseAtual = new Fases::FaseSegunda(pJogador1, pJogador2);
    }
}

void Jogo::limparFaseAtual()
{
    if (faseAtual) {
        delete faseAtual;
        faseAtual = nullptr;
    }
}

void Jogo::executar()
{
    while (estadoAtual != EstadoJogo::Sair && gg.getJanelaOpen())
    {
        if (estadoAtual == EstadoJogo::Menu)
        {
            menu.executar();
            EstadoJogo proximo = menu.getProximoEstado();

            if (proximo != EstadoJogo::Menu)
            {
                estadoAtual = proximo;

                if (estadoAtual == EstadoJogo::Jogando || estadoAtual == EstadoJogo::FaseDois)
                {
                    configurarNovaFase(estadoAtual);
                }
            }
        }
        else if (estadoAtual == EstadoJogo::Jogando || estadoAtual == EstadoJogo::FaseDois)
        {
            gg.update();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                limparFaseAtual();
                estadoAtual = EstadoJogo::Menu;
                continue;
            }

            if (pJogador2->getAtivo() == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                std::cout << "Jogador 2 entrou!" << std::endl;

                pJogador2->setAtivo(true);
                pJogador2->setX(100.0f);
                pJogador2->setY(450.0f);
                pJogador2->setPosicaoGrafica(pJogador2->getX(), pJogador2->getY());
                pJogador2->setGerenciadorGrafico(&gg);

                if (faseAtual) {
                    faseAtual->adicionarJogador2(pJogador2);
                }
            }

            if (faseAtual)
            {
                faseAtual->executar();
            }
        }
    }
}


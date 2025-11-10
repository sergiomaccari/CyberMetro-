#pragma once
#include "Ente.h" 

enum class EstadoJogo {
    Menu,
    Jogando,
    FaseDois,
    Sair
};


class Menu : public Ente
{
private:
    sf::Font fonte;
    std::vector<sf::Text> opcoes;
    int indiceOpcaoSelecionada;

    const sf::Color COR_SELECIONADA = sf::Color::Yellow;
    const sf::Color COR_NORMAL = sf::Color::White;
    const int TAMANHO_FONTE = 40;

    EstadoJogo estadoAtualInterno;

    void carregarFonte();
    void configurarOpcoes();
    void desenharOpcoes();
    void processarEntrada(sf::Event& evento);

public:
    Menu();
    ~Menu();

    void inicializar();

    void moverCima();
    void moverBaixo();
    void executar() override;

    EstadoJogo getProximoEstado() const;
};
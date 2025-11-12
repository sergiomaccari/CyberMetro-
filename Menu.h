#pragma once
#include "Ente.h" 

enum class EstadoJogo {
    Menu,
    Jogando,
    FaseDois,
    Pausado,
    Sair
};


class Menu : public Ente
{
private:
    sf::Font fonte;

    // Nivel do menu
    enum class MenuNivel { PRINCIPAL, FASE1, FASE2 };
    MenuNivel nivelAtual;

    // Vetores de opcoes
    std::vector<sf::Text> opcoesPrincipal;
    std::vector<sf::Text> opcoesFase1;
    std::vector<sf::Text> opcoesFase2;

    // Ponteiro para o vetor ativo
    std::vector<sf::Text>* pOpcoesAtuais;

    int indiceOpcaoSelecionada;

    const sf::Color COR_SELECIONADA = sf::Color::Yellow;
    const sf::Color COR_NORMAL = sf::Color::White;
    const int TAMANHO_FONTE = 40;

    EstadoJogo estadoAtualInterno;

    void carregarFonte();
    void configurarOpcoes();

    // Funcoes auxiliares para o novo menu
    void atualizarDestaque();
    void setNivelMenu(MenuNivel novoNivel, int novoIndice = 0);
    void posicionarTextos(std::vector<sf::Text>& textos);

public:
    Menu();
    ~Menu();
    void inicializar();
    void processarEntrada(sf::Event& evento);
    void desenharOpcoes();
    void moverCima();
    void moverBaixo();
    void executar();
    EstadoJogo getProximoEstado() const;
    void resetarEstadoInterno();
};
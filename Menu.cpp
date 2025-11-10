#include "Menu.h"
#include "Gerenciador_Grafico.h"
#include <iostream>

Menu::Menu()
    : indiceOpcaoSelecionada(0),
    estadoAtualInterno(EstadoJogo::Menu)
{
}

Menu::~Menu() {}

void Menu::inicializar()
{
    if (!pGG) {
        std::cerr << "Gerenciador Grafico (pGG) erro" << std::endl;
        return;
    }
    carregarFonte();
    configurarOpcoes();
}

void Menu::carregarFonte()
{
    if (!fonte.loadFromFile("arial.ttf"))
    {
        std::cerr << "Nao carregou a fonte" << std::endl;
    }
}

void Menu::configurarOpcoes()
{
    std::vector<std::string> textos = {
        "Jogar (Fase 1)",
        "Fase 2",
        "Sair"
    };

    for (size_t i = 0; i < textos.size(); ++i)
    {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setCharacterSize(TAMANHO_FONTE);
        texto.setString(textos[i]);
        texto.setFillColor(COR_NORMAL);

        sf::FloatRect bounds = texto.getLocalBounds();
        texto.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        texto.setPosition(LARGURA_TELA / 2.0f, 400.0f + i * 80.0f);

        opcoes.push_back(texto);
    }

    if (!opcoes.empty())
    {
        opcoes[indiceOpcaoSelecionada].setFillColor(COR_SELECIONADA);
    }
}

void Menu::moverCima()
{
    if (!opcoes.empty())
    {
        opcoes[indiceOpcaoSelecionada].setFillColor(COR_NORMAL);
        indiceOpcaoSelecionada = (int)((indiceOpcaoSelecionada - 1 + opcoes.size()) % opcoes.size());
        opcoes[indiceOpcaoSelecionada].setFillColor(COR_SELECIONADA);
    }
}

void Menu::moverBaixo()
{
    if (!opcoes.empty())
    {
        opcoes[indiceOpcaoSelecionada].setFillColor(COR_NORMAL);
        indiceOpcaoSelecionada = (int)((indiceOpcaoSelecionada + 1) % opcoes.size());
        opcoes[indiceOpcaoSelecionada].setFillColor(COR_SELECIONADA);
    }
}

void Menu::processarEntrada(sf::Event& evento)
{
    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Up)
        {
            moverCima();
        }
        else if (evento.key.code == sf::Keyboard::Down)
        {
            moverBaixo();
        }
    }

    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter)
    {
        std::string selecionado = opcoes[indiceOpcaoSelecionada].getString();

        if (selecionado == "Jogar (Fase 1)")
        {
            estadoAtualInterno = EstadoJogo::Jogando;
        }
        else if (selecionado == "Fase 2")
        {
            estadoAtualInterno = EstadoJogo::FaseDois;
        }
        else if (selecionado == "Sair")
        {
            estadoAtualInterno = EstadoJogo::Sair;
        }
    }
}

void Menu::executar()
{
    estadoAtualInterno = EstadoJogo::Menu;

    if (!pGG || !pGG->getJanela()) {
        estadoAtualInterno = EstadoJogo::Sair;
        return;
    }

    sf::Event evento;
    while (pGG->getJanela()->pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
        {
            estadoAtualInterno = EstadoJogo::Sair;
            return;
        }

        processarEntrada(evento);

        if (estadoAtualInterno != EstadoJogo::Menu)
        {
            return;
        }
    }

    pGG->clear();
    desenharOpcoes();
    pGG->render();
}


void Menu::desenharOpcoes()
{
    if (!pGG || !pGG->getJanela()) return;

    sf::Text titulo("Meu Jogo SFML", fonte, 80);
    titulo.setFillColor(sf::Color::Cyan);
    sf::FloatRect boundsT = titulo.getLocalBounds();
    titulo.setOrigin(boundsT.left + boundsT.width / 2.0f, boundsT.top + boundsT.height / 2.0f);
    titulo.setPosition(LARGURA_TELA / 2.0f, 200.0f);
    pGG->getJanela()->draw(titulo);

    for (const auto& opcao : opcoes)
    {
        pGG->getJanela()->draw(opcao);
    }
}

EstadoJogo Menu::getProximoEstado() const
{
    return estadoAtualInterno;
}
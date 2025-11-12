#include "Jogo.h"
#include "FasePrimeira.h" 
#include "FaseSegunda.h"  
#include "Gerenciador_Grafico.h"

Jogo::Jogo()
    : gg(),
    menu(),
    pJogador1(nullptr),
    pJogador2(nullptr),
    faseAtual(nullptr),
    estadoAtual(EstadoJogo::Menu),
    estadoAnterior(EstadoJogo::Menu),
    indicePausa(0)
{
    Ente::setGerenciadorGrafico(&gg);

    menu.inicializar();
    carregarRecursosPausa();

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

    std::cout << "Jogo encerrado" << std::endl;

}

void Jogo::carregarRecursosPausa()
{
    if (!fontePausa.loadFromFile("arial.ttf"))
    {
        std::cerr << "Erro ao carregar fonte arial.ttf para pausa" << std::endl;
    }

    fundoPausa.setSize(sf::Vector2f(LARGURA_TELA, ALTURA_TELA));
    fundoPausa.setFillColor(sf::Color(0, 0, 0, 150));

    std::vector<std::string> textos = { "Continuar", "Salvar Jogo", "Voltar ao Menu" };
    for (size_t i = 0; i < textos.size(); ++i)
    {
        sf::Text texto(textos[i], fontePausa, 50);
        sf::FloatRect bounds = texto.getLocalBounds();
        texto.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        texto.setPosition(LARGURA_TELA / 2.0f, 350.0f + i * 100.0f);
        opcoesPausa.push_back(texto);
    }
    atualizarDestaquePausa();
}

void Jogo::atualizarDestaquePausa()
{
    for (size_t i = 0; i < opcoesPausa.size(); ++i)
    {
        opcoesPausa[i].setFillColor((i == indicePausa) ? sf::Color::Yellow : sf::Color::White);
    }
}

void Jogo::processarInputPausa(sf::Event& evento)
{
    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::P) {
            estadoAtual = estadoAnterior;
            return;
        }
        else if (evento.key.code == sf::Keyboard::Up) {
            indicePausa = (indicePausa - 1 + opcoesPausa.size()) % opcoesPausa.size();
            atualizarDestaquePausa();
        }
        else if (evento.key.code == sf::Keyboard::Down) {
            indicePausa = (indicePausa + 1) % opcoesPausa.size();
            atualizarDestaquePausa();
        }
    }
    else if (evento.type == sf::Event::KeyReleased)
    {
        if (evento.key.code == sf::Keyboard::Enter) {
            switch (indicePausa)
            {
            case 0:
                estadoAtual = estadoAnterior;
                break;
            case 1:
                salvarJogo();
                break;
            case 2:
                voltarAoMenu();
                break;
            }
        }
    }
}

void Jogo::desenharPausa()
{
    gg.getJanela()->setView(gg.getJanela()->getDefaultView());

    gg.getJanela()->draw(fundoPausa);

    sf::Text titulo("PAUSADO", fontePausa, 80);
    titulo.setFillColor(sf::Color::White);
    sf::FloatRect boundsT = titulo.getLocalBounds();
    titulo.setOrigin(boundsT.left + boundsT.width / 2.0f, boundsT.top + boundsT.height / 2.0f);
    titulo.setPosition(LARGURA_TELA / 2.0f, 200.0f);
    gg.getJanela()->draw(titulo);

    for (const auto& opcao : opcoesPausa)
    {
        gg.getJanela()->draw(opcao);
    }
}

void Jogo::salvarJogo()
{
    std::cout << "teste Jogo salvo" << std::endl;
}

void Jogo::voltarAoMenu()
{
    limparFaseAtual();
    estadoAtual = EstadoJogo::Menu;
    menu.resetarEstadoInterno();
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

    if (faseAtual) {
        faseAtual->setJogo(this);
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
        sf::Event ev;
        while (gg.getJanela()->pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) {
                estadoAtual = EstadoJogo::Sair;
            }

            if (estadoAtual == EstadoJogo::Menu) {
                menu.processarEntrada(ev);
            }
            else if (estadoAtual == EstadoJogo::Pausado) {
                processarInputPausa(ev);
            }
            else if (estadoAtual == EstadoJogo::Jogando || estadoAtual == EstadoJogo::FaseDois)
            {
                if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::P)
                {
                    estadoAnterior = estadoAtual;
                    estadoAtual = EstadoJogo::Pausado;
                }
            }
        }

        if (estadoAtual == EstadoJogo::Jogando || estadoAtual == EstadoJogo::FaseDois)
        {
            if (faseAtual)
            {
                faseAtual->executar();

                if (faseAtual->getTerminou())
                {
                    voltarAoMenu(); // se termianr tem que voltar pro men
                }
            }


            if (pJogador2->getAtivo() == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (pJogador1)
                {
                    std::cout << "Jogador 2 spawnnado" << std::endl;
                    const float offsetX = 50.0f;
                    float spawnX = pJogador1->getX() + offsetX;
                    float spawnY = pJogador1->getY();
                    if (spawnX > MUNDO_X_MAX - 32.0f) {
                        spawnX = pJogador1->getX() - offsetX;
                    }

                    pJogador2->resetar(spawnX, spawnY);

                    pJogador2->setGerenciadorGrafico(&gg);
                    if (faseAtual) {
                        faseAtual->adicionarJogador2(pJogador2);
                    }
                }
            }
        }
        else if (estadoAtual == EstadoJogo::Menu)
        {
            EstadoJogo proximo = menu.getProximoEstado();
            if (proximo != EstadoJogo::Menu) {
                estadoAtual = proximo;
                if (estadoAtual == EstadoJogo::Jogando || estadoAtual == EstadoJogo::FaseDois) {
                    configurarNovaFase(estadoAtual);
                    menu.resetarEstadoInterno();
                }
            }
        }

        // --- 3. DESENHAR ---
        gg.clear();

        if (estadoAtual == EstadoJogo::Menu)
        {
            menu.desenharOpcoes();
        }

        // se o estado nao for menu e a fase existir: desenha
        else if ((estadoAtual == EstadoJogo::Jogando || estadoAtual == EstadoJogo::FaseDois || estadoAtual == EstadoJogo::Pausado) && faseAtual)
        {
            faseAtual->desenharFase();

            if (estadoAtual == EstadoJogo::Pausado) {
                desenharPausa();
            }
        }


        gg.render();
    }
}
#include "Fase.h"
#include "Robo_Junior.h"
#include "Plataforma.h"
#include "Chao.h"
#include "Robo_CEO.h" 
#include "Lista.h"
#include "Projetil.h" 
#include "Robo_Senior.h" 
#include "Jogo.h" 
#include "Gerenciador_Grafico.h" 
#include <iostream> 
#include <SFML/Graphics.hpp>

namespace Fases {
	Fase::Fase(Jogador* jogador1, Jogador* jogador2)
		: Ente(),
		pJogador1(jogador1),
		pJogador2(jogador2),
		pListaInimigos(nullptr),
		pListaObstaculos(nullptr),
		pListaChao(nullptr),
		pColisoes(nullptr),
		pJogo(nullptr),
		areaDeSaida(0.f, 0.f, 0.f, 0.f),
		terminou(false) // <-- INICIALIZAMOS AQUI
	{
		if (!texturaSaida.loadFromFile("Imagens/saida.png"))
		{
			std::cerr << "Erro: Nao foi possivel carregar Imagens/saida.png" << std::endl;
		}
		spriteSaida.setTexture(texturaSaida);


		pListaInimigos = new ListaEntidades();
		pListaObstaculos = new ListaEntidades();
		pListaChao = new ListaEntidades();

		pColisoes = new Gerenciador_Colisoes(pJogador1);

		if (pJogador2 && pJogador2->getAtivo()) {
			pColisoes->setJogador2(pJogador2);
		}
	}

	Fase::~Fase()
	{
		limpar();
	}

	void Fase::setJogo(Jogo* pJ)
	{
		pJogo = pJ;
	}

	void Fase::adicionarJogador2(Jogador* j2)
	{
		pJogador2 = j2;

		if (pColisoes) {
			pColisoes->setJogador2(pJogador2);
		}
	}

	void Fase::verificarFimDeFase()
	{
		// se ja terminou nao precisa checar de novo
		if (terminou || areaDeSaida.width == 0 || !pJogo) {
			return;
		}

		bool jogadorTerminou = false;

		if (pJogador1 && pJogador1->getAtivo()) {
			if (areaDeSaida.intersects(pJogador1->getFigura()->getGlobalBounds())) {
				jogadorTerminou = true;
			}
		}

		if (pJogador2 && pJogador2->getAtivo()) {
			if (areaDeSaida.intersects(pJogador2->getFigura()->getGlobalBounds())) {
				jogadorTerminou = true;
			}
		}

		if (jogadorTerminou) {
			// pJogo->voltarAoMenu(); // <-- REMOVEMOS ISSO
			terminou = true; // <-- ADICIONAMOS ISSO
		}
	}

	void Fase::executar()
	{
		if (pJogador1)
		{
			pJogador1->executar();
		}

		if (pJogador2)
		{
			pJogador2->executar();
		}

		if (pListaInimigos)
		{
			pListaInimigos->executar();
		}

		if (pListaObstaculos) {
			pListaObstaculos->executar();
		}

		if (pListaChao)
		{
			pListaChao->executar();
		}

		if (pColisoes) {
			pColisoes->limparInimigos();
			pColisoes->limparObstaculos();
			pColisoes->limparProjeteis();
			pColisoes->limparChao();

			if (pListaInimigos)
			{
				auto curI = pListaInimigos->getPrimeiro();
				while (curI) {
					Entidade* pEnt = curI->getInfo();
					Personagens::Inimigo* inim = dynamic_cast<Personagens::Inimigo*>(pEnt);
					if (inim && inim->getAtivo()) {
						pColisoes->incluirInimigo(inim);
					}
					curI = curI->getProx();
				}
			}

			if (pListaObstaculos)
			{
				auto curO = pListaObstaculos->getPrimeiro();
				while (curO) {
					Entidade* pEnt = curO->getInfo();
					Obstaculos::Obstaculo* obst = dynamic_cast<Obstaculos::Obstaculo*>(pEnt);
					if (obst && obst->getAtivo()) {
						pColisoes->incluirObstaculo(obst);
					}
					curO = curO->getProx();
				}
			}

			if (pListaChao)
			{
				auto curC = pListaChao->getPrimeiro();
				while (curC) {
					Entidade* pEnt = curC->getInfo();
					Entidades::Chao* chao = dynamic_cast<Entidades::Chao*>(pEnt);
					if (chao && chao->getAtivo()) {
						pColisoes->incluirChao(chao);
					}
					curC = curC->getProx();
				}
			}

			if (pJogador1)
			{
				ListaEntidades* projJog = pJogador1->getProjeteis();
				auto curPJog = projJog->getPrimeiro();
				while (curPJog) {
					Entidade* p = curPJog->getInfo();
					if (p->getAtivo()) {
						Entidades::Projetil* pProj = dynamic_cast<Entidades::Projetil*>(p);
						if (pProj) {
							pColisoes->incluirProjetil(pProj);
						}
					}
					curPJog = curPJog->getProx();
				}
			}

			if (pJogador2)
			{
				ListaEntidades* projJog2 = pJogador2->getProjeteis();
				auto curPJog2 = projJog2->getPrimeiro();
				while (curPJog2) {
					Entidade* p = curPJog2->getInfo();
					if (p->getAtivo()) {
						Entidades::Projetil* pProj = dynamic_cast<Entidades::Projetil*>(p);
						if (pProj) {
							pColisoes->incluirProjetil(pProj);
						}
					}
					curPJog2 = curPJog2->getProx();
				}
			}

			if (pListaInimigos)
			{
				auto curI = pListaInimigos->getPrimeiro();
				while (curI) {
					if (curI->getInfo()->getAtivo()) {
						Personagens::Robo_CEO* robCeo = dynamic_cast<Personagens::Robo_CEO*>(curI->getInfo());
						if (robCeo) {
							ListaEntidades* projrobCeo = robCeo->getProjeteis();
							auto curProbCeo = projrobCeo->getPrimeiro();
							while (curProbCeo) {
								Entidade* p = curProbCeo->getInfo();
								if (p->getAtivo()) {
									Entidades::Projetil* pProj = dynamic_cast<Entidades::Projetil*>(p);
									if (pProj) {
										pColisoes->incluirProjetil(pProj);
									}
								}
								curProbCeo = curProbCeo->getProx();
							}
						}
					}
					curI = curI->getProx();
				}
			}

			pColisoes->executar();
		}

		verificarFimDeFase();
	}

	void Fase::desenharFase()
	{
		Gerenciador_Grafico* pGG = Ente::getGerenciadorGrafico();
		if (pGG)
		{
			pGG->getJanela()->setView(pGG->getJanela()->getDefaultView());
			pGG->desenharBackground();

			if (pJogador1 && pJogador1->getAtivo())
			{
				pGG->setCamera(pJogador1);
			}
			else if (pJogador2 && pJogador2->getAtivo())
			{
				pGG->setCamera(pJogador2);
			}

			desenharMapa();

			pGG->getJanela()->draw(spriteSaida);

			if (pListaObstaculos) pListaObstaculos->desenhar();

			if (pJogador1) {
				if (pJogador1->getAtivo()) pJogador1->desenhar();
				pJogador1->getProjeteis()->desenhar();
			}
			if (pJogador2) {
				if (pJogador2->getAtivo()) pJogador2->desenhar();
				pJogador2->getProjeteis()->desenhar();
			}

			if (pListaInimigos)
			{
				pListaInimigos->desenhar();
				auto curI = pListaInimigos->getPrimeiro();
				while (curI) {
					Entidade* pEnt = curI->getInfo();
					if (pEnt && pEnt->getAtivo()) {
						Personagens::Robo_CEO* robCeo = dynamic_cast<Personagens::Robo_CEO*>(pEnt);
						if (robCeo) {
							robCeo->getProjeteis()->desenhar();
						}
					}
					curI = curI->getProx();
				}
			}
		}
	}


	void Fase::limpar()
	{
		if (pListaInimigos) {
			delete pListaInimigos;
			pListaInimigos = nullptr;
		}
		if (pListaObstaculos) {
			delete pListaObstaculos;
			pListaObstaculos = nullptr;
		}
		if (pListaChao) {
			delete pListaChao;
			pListaChao = nullptr;
		}
		if (pColisoes) {
			delete pColisoes;
			pColisoes = nullptr;
		}
	}


	void Fase::criarRoboJunior(float x, float y)
	{
		Gerenciador_Grafico* pGG_local = Ente::getGerenciadorGrafico();
		if (!pGG_local) return;

		Personagens::Robo_Junior* inimigo = new Personagens::Robo_Junior(x, y);
		inimigo->setGerenciadorGrafico(pGG_local);
		pListaInimigos->inserir(inimigo);
	}

	void Fase::criarRoboJunior(const sf::Vector2f& pos)
	{
		this->criarRoboJunior(pos.x, pos.y);
	}

	void Fase::criarPlataforma(float x, float y, int altura)
	{
		Gerenciador_Grafico* pGG_local = Ente::getGerenciadorGrafico();
		if (!pGG_local) return;

		Obstaculos::Plataforma* plat = new Obstaculos::Plataforma(x, y, altura);
		plat->setGerenciadorGrafico(pGG_local);
		pListaObstaculos->inserir(plat);
	}

	void Fase::criarChao(float x, float y)
	{
		Gerenciador_Grafico* pGG_local = Ente::getGerenciadorGrafico();
		if (!pGG_local) return;

		Entidades::Chao* chao = new Entidades::Chao(x, y);
		chao->setGerenciadorGrafico(pGG_local);
		pListaChao->inserir(chao);
	}

	void Fase::desenharMapa()
	{

	}
	void Fase::criarMapa()
	{

	}

	bool Fase::getTerminou() const
	{
		return terminou;
	}
}
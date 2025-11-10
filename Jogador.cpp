#include "Jogador.h"
#include "Projetil.h"


using namespace Entidades;
namespace Personagens
{
	const float Jogador::PROJETIL_VELOCIDADE_JOGADOR = 3.0f; //deveria ser no .h acho

	Jogador::Jogador(int numJogador) :
		pontos(0),
		cooldown(0),
		playerNum(numJogador),
		ultimaDirecaoX(1.0f),
		estaNoChao(false),
		stun(sf::Time::Zero), 
		obstaculoCooldown(sf::Time::Zero) 
	{
		this->x = 10;
		this->y = 10;
		this->velocidade = 300.0f;
		this->n_vidas = 1000;

		std::string caminhoTextura = (playerNum == 1) ? "Imagens/jogador1.png" : "Imagens/jogador2.png";

		if (pGG)
		{
			sf::Texture* tex = pGG->getTextura(caminhoTextura);
			if (tex)
			{
				pFigura->setTexture(*tex);
				pFigura->setScale(32.0f / tex->getSize().x, 32.0f / tex->getSize().y);
			}
		}
		else
		{
			std::cerr << "Erro: Gerenciador Grafico nao setado para Jogador!" << std::endl;
		}


		pFigura->setPosition(sf::Vector2f(static_cast<float>(this->x), static_cast<float>(this->y)));

	}


	Jogador::Jogador(int numJogador, float xi, float yi) :
		Personagem(xi, yi),
		pontos(0),
		cooldown(0),
		playerNum(numJogador),
		ultimaDirecaoX(1.0f),
		estaNoChao(false),
		stun(sf::Time::Zero), 
		obstaculoCooldown(sf::Time::Zero) 
	{
		
	}


	Jogador::~Jogador()
	{
		movimento = sf::Vector2f(0.0f, 0.0f);
	}

	void Jogador::mover()
	{
		movimento = sf::Vector2f(0.0f, 0.0f);
		tempo = clock.restart();

		if (obstaculoCooldown > sf::Time::Zero)
		{
			obstaculoCooldown -= tempo;
			if (obstaculoCooldown < sf::Time::Zero)
			{
				obstaculoCooldown = sf::Time::Zero;
			}
		}

		if (stun > sf::Time::Zero)
		{
			stun -= tempo;

			if (stun < sf::Time::Zero)
			{
				stun = sf::Time::Zero;
			}

			movimento = { 0.f, 0.f };
			this->x += movimento.x * tempo.asSeconds() * velocidade;
			this->y += movimento.y * tempo.asSeconds() * velocidade;
			setPosicaoGrafica(this->x, this->y);
			return;
		}

		if (playerNum == 1) 
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //+y
				movimento += sf::Vector2f(0.0f, -1.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //+x
			{
				movimento += sf::Vector2f(1.0f, 0.0f);
				ultimaDirecaoX = 1.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//-x
			{
				movimento += sf::Vector2f(-1.0f, 0.0f);
				ultimaDirecaoX = -1.0f;
			}
		}
		else if (playerNum == 2) // p2 setas
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				movimento += sf::Vector2f(0.0f, -1.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				movimento += sf::Vector2f(1.0f, 0.0f);
				ultimaDirecaoX = 1.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				movimento += sf::Vector2f(-1.0f, 0.0f);
				ultimaDirecaoX = -1.0f;
			}
		}

		Personagem::gravidade(&movimento);

		this->x += movimento.x * tempo.asSeconds() * velocidade;
		this->y += movimento.y * tempo.asSeconds() * velocidade;

		setPosicaoGrafica(this->x, this->y);
	}

	void Jogador::executar()
	{
		if (this->getAtivo())
		{
			this->mover();
			this->atirar();
		}
		projeteis.executar();
	}

	void Jogador::salvar() 
	{

	}

	void Jogador::atirar() {
		if (cooldown > 0)
			cooldown--;

		bool tiroPressionado = false;
		if (playerNum == 1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			tiroPressionado = true;
		else if (playerNum == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			tiroPressionado = true;


		if (tiroPressionado && cooldown == 0) {
			Projetil* novoProjetil = new Projetil();
			if (pGG)
			{
				novoProjetil->setGerenciadorGrafico(pGG);
			}

			float spawnX;
			float playerWidth = pFigura->getGlobalBounds().width;
			float projetilWidth = 5.0f;

			if (ultimaDirecaoX > 0)
			{
				spawnX = x + playerWidth;
			}
			else
			{
				spawnX = x - projetilWidth;
			}

			novoProjetil->setX(spawnX);
			novoProjetil->setY(y + 7.5f);

			novoProjetil->setVelocidade(PROJETIL_VELOCIDADE_JOGADOR * ultimaDirecaoX, 0.0f);

			novoProjetil->setDoBem(true);
			projeteis.inserir(novoProjetil);
			cooldown = 120;
		}
	}

	void Jogador::setEstaNoChao(bool noChao)
	{
		estaNoChao = noChao;
	}


	ListaEntidades* Jogador::getProjeteis()
	{
		return &projeteis;
	}


	void Jogador::trava_mov(float t)
	{
		const sf::Time novo_st = sf::seconds(t);
		if (stun < novo_st)
		{
			stun = novo_st;
		}
	}

	void Jogador::iniciarObstaculoCooldown(sf::Time duracao)
	{
		obstaculoCooldown = duracao;
	}

	sf::Time Jogador::getObstaculoCooldown() const
	{
		return obstaculoCooldown;
	}
}
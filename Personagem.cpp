#pragma once
#include "Personagem.h"

namespace Personagens
{
	Personagem::Personagem(float xi, float yi) : Entidade(xi, yi), n_vidas(1), movimento(0.0f, 0.0f), velocidade(0.0)
	{

	}

	Personagem::Personagem() : n_vidas(1), movimento(0.0f, 0.0f), velocidade(0.0)
	{

	}

	Personagem::~Personagem() 
	{
	
	}

	void Personagem::setMovimentoY(float yn)
	{
		movimento.y = yn;
	}

	sf::Vector2f Personagem::getMovimento()
	{
		return movimento;
	}

	void Personagem::setVelocidade(float vn)
	{
		this->velocidade = vn;
	}

	float Personagem::getVelocidade()
	{
		return velocidade;
	}

	void Personagem::operator++()
	{
		this->n_vidas++;
	}

	void Personagem::operator--()
	{
		this->n_vidas--;
		if (this->n_vidas <= 0)
		{
			this->n_vidas = 0;
			this->setAtivo(false); 
		}
	}
}
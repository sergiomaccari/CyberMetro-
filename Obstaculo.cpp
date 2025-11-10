#include "Obstaculo.h"

namespace Obstaculos
{
	Obstaculo::Obstaculo(float xi, float yi) :
		danoso(false),
		isMovel(false)
	{
		this->x = xi;
		this->y = yi;

	}
	Obstaculo::~Obstaculo() {}
	bool Obstaculo::getDanoso() const
	{
		return danoso;
	}

	bool Obstaculo::getMovel() const
	{
		return isMovel;
	}
}
#include "Inimigo.h"


namespace Personagens
{
	Inimigo::Inimigo(float xi, float yi)
	{

		nivel_maldade = rand() % 5 + 1;
	}


	Inimigo::~Inimigo() 
	{
		nivel_maldade = 0;
	}


	void Inimigo::executar() {}


}

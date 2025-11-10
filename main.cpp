#include "Jogo.h"
#include <iostream>

int main()
{
	srand(time(NULL));

	try
	{
		Jogo meuJogo;
		meuJogo.executar();
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "ERRO CATASTROFICO: Falta de memoria!" << std::endl;
		std::cerr << "Excecao: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERRO INESPERADO: Ocorreu uma excecao." << std::endl;
		std::cerr << "Excecao: " << e.what() << std::endl;
		return 2;
	}
	catch (...)
	{
		std::cerr << "ERRO DESCONHECIDO: Ocorreu uma excecao nao-padrao." << std::endl;
		return 3;
	}
	return 0;
}
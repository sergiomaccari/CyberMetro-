#include "ListaEntidades.h"
#include <iostream>
#include "Projetil.h" 
#include "Lista.h" 
#include "Obstaculo.h"

using namespace Entidades;


ListaEntidades::ListaEntidades() {}

ListaEntidades::~ListaEntidades()
{
    Elemento<Entidade>* cur = LEs.getPrimeiro();
    while (cur)
    {
        if (cur->getInfo())
        {
            delete cur->getInfo();
        }
        cur = cur->getProx();
    }
}

void ListaEntidades::inserir(Entidade* e)
{
    LEs.inserir(e);
}
void ListaEntidades::remover(Entidade* e)
{
    LEs.remover(e);
}
std::size_t ListaEntidades::size() const
{
    return LEs.size();
}

Lista<Entidades::Entidade>* ListaEntidades::getLista()
{
    return &LEs;
}

Elemento<Entidades::Entidade>* ListaEntidades::getPrimeiro() const
{
    return LEs.getPrimeiro();
}


void ListaEntidades::executar()
{
    Elemento<Entidade>* cur = LEs.getPrimeiro();
    while (cur)
    {
        Entidade* pEnt = cur->getInfo();
        Elemento<Entidade>* proximo = cur->getProx();
        if (pEnt->getAtivo() == false)
        {
            LEs.remover(pEnt);
            delete pEnt;
        }
        else
        {
            pEnt->executar();
        }

        cur = proximo;
    }
}

void ListaEntidades::desenhar()
{
    Elemento<Entidade>* cur = LEs.getPrimeiro();
    while (cur)
    {
        Entidade* pEnt = cur->getInfo();
        if (pEnt && pEnt->getAtivo())
        {
            Obstaculos::Obstaculo* pObs = dynamic_cast<Obstaculos::Obstaculo*>(pEnt);

         
            if (!pObs || pObs->getMovel())
            {
                pEnt->desenhar();
            }
        }
        cur = cur->getProx();
    }
}
#pragma once
#include <cstddef>
#include <stdexcept>


template<typename T>
class Elemento
{
private:
    T* pInfo;
    Elemento<T>* pProx;

public:
    Elemento() : pInfo(nullptr), pProx(nullptr) {}
    ~Elemento() {}

    void incluir(T* p) { pInfo = p; }
    void setProx(Elemento<T>* pe) { pProx = pe; }
    Elemento<T>* getProx() const { return pProx; }
    T* getInfo() const { return pInfo; }
};

template<typename T>
class Lista
{
private:
    Elemento<T>* pPrimeiro;
    Elemento<T>* pUltimo;
    std::size_t tamanho;
public:
    Lista();
    ~Lista();

    Elemento<T>* getPrimeiro() const 
    { 
        return pPrimeiro; 
    }
    Elemento<T>* getUltimo() const 
    {
        return pUltimo; 
    }

    void inserir(T* item);
    void remover(T* item);
    void limpar();
    std::size_t size() const;
    bool vazia() const;
};


template<typename T>
Lista<T>::Lista() : pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0) {}

template<typename T>
Lista<T>::~Lista()
{
    limpar();
}

template<typename T>
void Lista<T>::limpar()
{
    Elemento<T>* cur = pPrimeiro;
    while (cur)
    {
        Elemento<T>* nxt = cur->getProx();
        delete cur;
        cur = nxt;
    }
    pPrimeiro = nullptr;
    pUltimo = nullptr;
    tamanho = 0;
}


template<typename T>
void Lista<T>::inserir(T* item) 
{
    Elemento<T>* e = new Elemento<T>();
    e->incluir(item);

    if (!pPrimeiro)
    {
        pPrimeiro = pUltimo = e;
    }
    else
    {
        pUltimo->setProx(e);
        pUltimo = e;
    }
    ++tamanho;
}

template<typename T>
void Lista<T>::remover(T* item)
{
    Elemento<T>* prev = nullptr;
    Elemento<T>* cur = pPrimeiro;
    while (cur)
    {
        if (cur->getInfo() == item)
        {
            if (prev) prev->setProx(cur->getProx());
            else pPrimeiro = cur->getProx();
            if (cur == pUltimo) pUltimo = prev;
            delete cur;
            --tamanho;
            return;
        }
        prev = cur;
        cur = cur->getProx();
    }
}

template<typename T>
std::size_t Lista<T>::size() const
{
    return tamanho;
}

template<typename T>
bool Lista<T>::vazia() const
{
    return tamanho == 0;
}
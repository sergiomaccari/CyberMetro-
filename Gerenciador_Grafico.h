#pragma once
#include <ostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <time.h>
#include <unordered_map> 
#include <string>        
#include <iostream>      
#include <filesystem>
#define ALTURA_TELA 900
#define LARGURA_TELA 1600
#define LARGURA_CHAO 32.0f
#define ALTURA_CHAO 32.0f 

class Ente;

namespace Personagens
{
    class Jogador;
}

class Gerenciador_Grafico
{
private:
    sf::RenderWindow* janela;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::RectangleShape rect;
    sf::CircleShape cir;
    sf::View camera;

    std::unordered_map<std::string, sf::Texture> texturas;

    sf::Texture texturaBackground;
    sf::Sprite spriteBackground;

    void iniciaJanela();


public:
    Gerenciador_Grafico();
    ~Gerenciador_Grafico();

    sf::Texture* getTextura(std::string caminho);

    void desenharBackground();

    void desenharEnte(const Ente* pe);
    void update();
    void render();
    void clear();
    void setCamera(Personagens::Jogador* pJog);

    const bool getJanelaOpen() const;
    sf::RenderWindow* getJanela() const;
};
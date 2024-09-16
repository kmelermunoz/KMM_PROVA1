#include "game.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Constructor
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Aplicaci� SFML")
    , mPlayer(sf::Vector2f(80.f, 80.f))  // Canvia el jugador a un quadrat de mida 80x80
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
{
    // Configura les propietats del jugador
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Green);

    // Configura la barrera superior
    mBarrierTop.setSize(sf::Vector2f(100.f, 250.f));
    mBarrierTop.setFillColor(sf::Color::Red);

    // Calcula la posici� central per a la barrera
    float windowWidth = static_cast<float>(mWindow.getSize().x);
    float barrierWidth = mBarrierTop.getSize().x;
    float barrierHeight = mBarrierTop.getSize().y;
    float centerX = (windowWidth - barrierWidth) / 2;

    // Centra la barrera horitzontalment i col�loca-la a la part superior
    mBarrierTop.setPosition(centerX, 0.f);  // Ajusta la posici� Y si cal

    // Configura el quadrat addicional a la dreta
    mExtraSquare.setSize(sf::Vector2f(80.f, 80.f));
    mExtraSquare.setPosition(495.f, 200.f);
    mExtraSquare.setFillColor(sf::Color::Blue);
}

// Bucle principal del joc
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}

// Processa esdeveniments d'entrada
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

// Actualitza la l�gica del joc (per exemple, mou el jugador)
void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;

    // Actualitza la posici� del jugador basada en el moviment i el temps delta
    mPlayer.move(movement * deltaTime.asSeconds());
}

// Renderitza l'escena
void Game::render()
{
    mWindow.clear();        // Esborrar la pantalla
    mWindow.draw(mPlayer);  // Dibuixa el jugador (quadrat)
    mWindow.draw(mBarrierTop);     // Dibuixa la barrera superior
    mWindow.draw(mExtraSquare);    // Dibuixa el quadrat addicional
    mWindow.display();      // Mostra el quadre
}

// Gestiona l'entrada
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

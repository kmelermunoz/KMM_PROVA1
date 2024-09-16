#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();        // Constructor
    void run();    // Bucle principal del joc

private:
    void processEvents();    // Processa l'entrada
    void update(sf::Time deltaTime);  // Actualitza la lògica del joc
    void render();           // Renderitza l'escena

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::RenderWindow mWindow;           // finestra principal
    sf::RectangleShape mPlayer;         // Jugador representat com un quadrat

    // Noves formes
    sf::RectangleShape mBarrierTop;     // Barrera a la part superior
    sf::RectangleShape mBarrierBottom;  // Barrera a la part inferior
    sf::RectangleShape mExtraSquare;    // Quadrat addicional a la dreta

    // Senyals de moviment
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    const float PlayerSpeed = 100.f;    // Velocitat del jugador
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // Temps per fotograma per a 60 FPS
};

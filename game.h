#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

struct Ball
{
    sf::RectangleShape shape;
    float vel_x;
    float vel_y;
    void update(){shape.move(vel_x, vel_y);};
};

struct Paddle
{
    sf::RectangleShape shape;
    float vel_y;
    void update(){shape.move(0, vel_y);};
};

class Game
{
private:
    sf::RenderWindow window;
    const float frameTime;
    sf::Clock clock;
    sf::RectangleShape paddle1;
    Paddle paddle2;
    Ball ball;
    int score1;
    int score2;
    sf::Texture numbersTexture;
    sf::Sprite numbersPlayer1[10];
    sf::Sprite numbersPlayer2[10];
    sf::Texture barTexture;
    sf::Sprite bar;
    void render();
    void update();

public:
    Game();
    void gameLoop();
};

#endif // GAME_H_INCLUDED

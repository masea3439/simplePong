#include "game.h"


Game::Game(): window(sf::VideoMode(600, 400), "Very Normal Pong")
, frameTime(1.0f / 60)
, clock()
, paddle1(sf::Vector2f(5, 20))

{
    paddle1.setPosition(20, 200);
    paddle2.shape = sf::RectangleShape(sf::Vector2f(5, 20));
    paddle2.vel_y = 0;
    paddle2.shape.setPosition(570, 200);
    ball.shape = sf::RectangleShape(sf::Vector2f(10, 10));
    ball.vel_x = -2.0f;
    ball.vel_y = 1.0f;
    ball.shape.setFillColor(sf::Color::White);
}

void Game::gameLoop()
{
    ball.shape.setPosition(sf::Vector2f(300, 200));
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                paddle1.move(0, -4);
                if (paddle1.getPosition().y < 0)
                    paddle1.setPosition(20, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                paddle1.move(0, 4);
                if (paddle1.getPosition().y + 20 > 400)
                    paddle1.setPosition(20, 380);
            }


            update();
            render();

            clock.restart();
        }
        else
        {
            sf::sleep(sf::seconds(frameTime - clock.getElapsedTime().asSeconds()));
        }
    }
}

void Game::update()
{
    ball.update();
    static float x;
    static float y;
    static float size_y;
    static float paddle2_y;
    static float paddle2_size_y;
    static int random;
    static sf::FloatRect ball_box;
    x = ball.shape.getPosition().x;
    y = ball.shape.getPosition().y;

    random = rand() % 8 + 1;
    if (random == 1)
    {
        paddle2_y = paddle2.shape.getPosition().y;
        paddle2_size_y = paddle2.shape.getSize().y;
        if(paddle2_y <= y+size_y/2 && y+size_y/2 <= paddle2_y+paddle2_size_y)
            paddle2.vel_y = 0;
        else
        {
            if (y+size_y/2 < paddle2.shape.getPosition().y+paddle2_size_y/2)
                paddle2.vel_y = -4;
            else
                paddle2.vel_y = 4;
        }
    }

    paddle2.update();

    size_y = ball.shape.getSize().y;
    ball_box = ball.shape.getGlobalBounds();
    if (x < 0 || x > 600)
    {
        ball.vel_x = -2;
        ball.vel_y = (rand() % 200 + 100 )/ 100.0f;
        if (rand()%2 == 1)
            ball.vel_y = -ball.vel_y;
        ball.shape.setPosition(300, y);
        if (x > 600)
            paddle2.shape.setSize(sf::Vector2f(5, paddle2_size_y + 5));
        return;
    }
    if ((y <= 0 && ball.vel_y < 0) || (y + size_y >= 400 && ball.vel_y > 0))
        ball.vel_y = -ball.vel_y;
    if (ball_box.intersects(paddle1.getGlobalBounds()))
        ball.vel_x = fabs(ball.vel_x) + 0.5;
    if (ball_box.intersects(paddle2.shape.getGlobalBounds()))
        ball.vel_x = -fabs(ball.vel_x) - 0.5;
}

void Game::render()
{
    window.clear();
    window.draw(ball.shape);
    window.draw(paddle1);
    window.draw(paddle2.shape);
    window.display();
}

#include <SFML/Graphics.hpp>
#include "map.h"
#include "Hero.h"
#include "view.h"
#include "view.h"

using namespace sf;
using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "The Quest");
    /*view.reset(FloatRect(0, 0, 300, 300));*/

    Image mapImage;
    mapImage.loadFromFile("images/map.png");
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    Hero hero("hero.png", 50, 50, 0, 0);

    float currentFrame = 0;
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::S)) {
            hero.direction = 0; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 48));
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            hero.direction = 1; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 48, 32, 48));
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            hero.direction = 2; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 96, 32, 48));
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            hero.direction = 3; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 144, 32, 48));
        }
        /*hero.bordersInteraction();*/
        hero.movement(time);
        /*viewCentersOnHero(hero.x, hero.y);*/
        window.setView(hero.view);
        window.clear(); //сделать невыохдящую за пределы камеру
        for (int i = 0; i < mapHeight; i++)
            for (int j = 0; j < mapWidth; j++) {
                if (Map[i][j] == ' ') {
                    mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
                }
                if (Map[i][j] == 's') {
                    mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
                }
                if (Map[i][j] == '0') {
                    mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
                }
                mapSprite.setPosition(i * 32, j * 32);
                window.draw(mapSprite);
            }
        window.draw(hero.sprite);
        window.display();
    }

    return 0;
}
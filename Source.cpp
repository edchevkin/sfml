#include <SFML/Graphics.hpp>
#include "hero.h"
#include "map.h"
#include <vector>

using namespace sf;
using namespace std;

float getRandCoord() {
    float r = rt + rand() % (mapWidth - 1) * rt;
    return r;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "The Dungeon Master");

    Image mapImage;
    mapImage.loadFromFile("images/map2.png");
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    Hero hero(512, 512, 32, 48);

    Enemy enemy1(0, 0, 32, 32);
    Enemy enemy2(512, 0, 32, 32);
    Enemy enemy3(0, 512, 32, 32);

    float currentFrame = 0;
    Clock clock;
    float counter = 0;
    float gameTimer = 0;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        gameTimer += time;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        hero.movement(time);
        hero.heroWithEnemyCollision(enemy1, time);
        hero.heroWithEnemyCollision(enemy2, time);
        hero.heroWithEnemyCollision(enemy3, time);
        window.setView(hero.view);

        enemy1.movement(time);
        enemy2.movement(time);
        enemy3.movement(time);

        window.clear();

        for (int i = 0; i < mapHeight; i++)
            for (int j = 0; j < mapWidth; j++) {
                if (MapLayout[i][j] == '0')
                    mapSprite.setTextureRect(IntRect(0, 32, rt, rt));
                if (MapLayout[i][j] == ' ')
                    mapSprite.setTextureRect(IntRect(160, 0, rt, rt));
                mapSprite.setPosition(i * rt, j * rt);
                window.draw(mapSprite);
            }

        window.draw(hero.sprite);

        window.draw(enemy1.sprite);
        window.draw(enemy2.sprite);
        window.draw(enemy3.sprite);

        window.display();
    }
    return 0;
}
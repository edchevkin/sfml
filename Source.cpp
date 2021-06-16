#include <SFML/Graphics.hpp>
#include "enemy.h"
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
    sf::RenderWindow window(sf::VideoMode(500, 500), "The Game");

    Image mapImage;
    mapImage.loadFromFile("images/map2.png");
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    Hero hero(512, 512, 32, 48);

    bool allNotDead = true;
    Enemy enemy1(0, 0, 32, 48);
    Enemy enemy2(512, 0, 32, 48);
    Enemy enemy3(0, 512, 32, 48);

    float currentFrame = 0;
    float counter = 0;
    int counter2 = 0;
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
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, hero.w, hero.h));
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            hero.direction = 1; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 48, hero.w, hero.h));
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            hero.direction = 2; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 96, hero.w, hero.h));
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            hero.direction = 3; hero.speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 4) currentFrame -= 4;
            hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 144, hero.w, hero.h));
        }
        hero.movement(time);
        window.setView(hero.view);

        enemy1.movement(time);
        enemy2.movement(time);
        enemy3.movement(time);

        window.clear();

        for (int i = 0; i < mapHeight; i++)
            for (int j = 0; j < mapWidth; j++) {
                if (MapLayout[i][j] == '0')
                    mapSprite.setTextureRect(IntRect(0, 192, 64, 64));
                if (MapLayout[i][j] == 'w')
                    mapSprite.setTextureRect(IntRect(704, 64, 64, 64));
                if (MapLayout[i][j] == ' ')
                    mapSprite.setTextureRect(IntRect(64, 64, 64, 64));
                mapSprite.setPosition(i * 64, j * 64);
                window.draw(mapSprite);
            }

        window.draw(hero.sprite);

        window.draw(enemy1.hitbox);
        window.draw(enemy2.hitbox);
        window.draw(enemy3.hitbox);

        window.display();
    }

    return 0;
}
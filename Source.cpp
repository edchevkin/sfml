#include <SFML/Graphics.hpp>
//#include "map.h"
#include "Hero.h"

using namespace sf;
using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "The Quest");

    Image mapImage;
    mapImage.loadFromFile("images/map2.png");
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    Hero hero(256, 256, 32, 48);

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
        //if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
        //    hero.direction = 4; hero.speed = 0.1;
        //    currentFrame += 0.0005 * time;
        //    if (currentFrame > 4) currentFrame -= 4;
        //    hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, hero.w, hero.h));
        //}
        //if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
        //    hero.direction = 5; hero.speed = 0.1;
        //    currentFrame += 0.0005 * time;
        //    if (currentFrame > 4) currentFrame -= 4;
        //    hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, hero.w, hero.h));
        //}
        //if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
        //    hero.direction = 6; hero.speed = 0.1;
        //    currentFrame += 0.0005 * time;
        //    if (currentFrame > 4) currentFrame -= 4;
        //    hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 144, hero.w, hero.h));
        //}
        //if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
        //    hero.direction = 7; hero.speed = 0.1;
        //    currentFrame += 0.0005 * time;
        //    if (currentFrame > 4) currentFrame -= 4;
        //    hero.sprite.setTextureRect(IntRect(32 * int(currentFrame), 144, hero.w, hero.h));
        //}
        //if ((Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::S))) {
        //    hero.direction = 8; hero.speed = 0.1;
        //}

        hero.movement(time);
        window.setView(hero.view);
        window.clear(); //сделать невыохдящую за пределы камеру
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
        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace sf;
using namespace std;

class Hero {
public:
    float x, y, w, h, dx, dy, speed = 0;
    int direction = 0;
    int hp = 100;
    float camLength = rt * mapWidth;
    float timeAfterCollision = 0;
    float counter = 0;
    RectangleShape hitbox;
    Image image;
    Texture texture;
    Sprite sprite;
    View view;
    Hero(float X, float Y, float W, float H) {
        w = W; h = H;
        hitbox.setSize(Vector2f(w, h));
        hitbox.setPosition(x, y);
        image.loadFromFile("images/hero.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        x = X; y = Y;
        view.reset(FloatRect(x, y, camLength, camLength));
    }

    void movement(float time) {
        keyboard();

        if (direction == 0) {
            dx = 0; dy = speed;
        }
        else if (direction == 1) {
            dx = -speed; dy = 0;
        }
        else if (direction == 2) {
            dx = speed; dy = 0;
        }
        else if (direction == 3) {
            dx = 0; dy = -speed;
        }

        y += dy * time;
        x += dx * time;
        speed = 0;

        heroWithMapInteractions();
        animation(time);
        hitbox.setPosition(x, y);
        sprite.setPosition(hitbox.getPosition());
        viewCentersOnHero(x, y);
    }

    void keyboard() {
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction = 0; speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction = 1; speed = 0.1;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction = 2; speed = 0.1;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 3; speed = 0.1;
             
        }
    }

    void animation(float time) {
        if (direction == 0) {
            counter += 0.005 * time;
            if (counter > 4) counter -= 4;
            sprite.setTextureRect(IntRect(w * int(counter), 0, w, h));
        }
        if (direction == 1) {
            counter += 0.005 * time;
            if (counter > 4) counter -= 4;
            sprite.setTextureRect(IntRect(w * int(counter), h, w, h));
        }
        if (direction == 2) {
            counter += 0.005 * time;
            if (counter > 4) counter -= 4;
            sprite.setTextureRect(IntRect(w * int(counter), 2 * h, w, h));
        }
        if (direction == 3) {
            counter += 0.005 * time;
            if (counter > 4) counter -= 4;
            sprite.setTextureRect(IntRect(w * int(counter), 3 * h, w, h));
        }
    }

    View viewCentersOnHero(float x, float y) {
        float cameraX = x + w / 2; float cameraY = y + h / 2;
        if (cameraX < camLength / 2) cameraX = camLength / 2;
        if (cameraY < camLength / 2) cameraY = camLength / 2;
        if (cameraX > mapWidth * rt - camLength / 2) cameraX = mapWidth * rt - camLength / 2;
        if (cameraY > mapHeight * rt - camLength / 2) cameraY = mapHeight * rt - camLength / 2;
        view.setCenter(cameraX, cameraY);
        return view;
    }
    void heroWithMapInteractions() {
        if (x < rt) x = rt;
        if (x > (mapWidth - 1) * rt - w) x = (mapWidth - 1) * rt - w;
        if (y < rt) y = rt;
        if (y > (mapHeight - 1) * rt - h) y = (mapHeight - 1) * rt - h;
    }
    void heroWithEnemyCollision(Enemy enemy, float time) {
        if (timeAfterCollision > 10) {
            if (FloatRect(x, y, w, h).intersects(FloatRect(enemy.x, enemy.y, enemy.w, enemy.h))) {
                hp -= 20;
                timeAfterCollision = 0;
            }
        }
        timeAfterCollision += 0.005 * time;
    }
};
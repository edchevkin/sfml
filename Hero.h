#include <SFML/Graphics.hpp>
#include <iostream>
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
    float camLength = 640;
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
        switch (direction) {
        case 0: dx = 0; dy = speed; break;
        case 1: dx = -speed; dy = 0; break;
        case 2: dx = speed; dy = 0; break;
        case 3: dx = 0; dy = -speed; break;
        }

        y += dy * time;
        x += dx * time;
        speed = 0;
        heroWithMapInteractions();
        hitbox.setPosition(x, y);
        sprite.setPosition(hitbox.getPosition());
        viewCentersOnHero(x, y);
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
        //for (int i = x / rt; i < (x + w) / rt; i++)
        //    for (int j = y / rt; j < (y + h) / rt; j++) {
        //        if (MapLayout[i][j] == 'w' || MapLayout[i][j] == '0') {
        //            if (dx > 0 && dy == 0)
        //                x = i * rt - w;
        //            if (dx < 0 && dy == 0)
        //                x = i * rt + rt;
        //            if (dx == 0 && dy > 0)
        //                y= j * rt - h;
        //            if (dx == 0 && dy < 0)
        //                y = j * rt + rt;
        //        }
        //    }
        if (x < rt) x = rt;
        if (x > (mapWidth - 1) * rt - w) x = (mapWidth - 1) * rt - w;
        if (y < rt) y = rt;
        if (y > (mapHeight - 1) * rt - h) y = (mapHeight - 1) * rt - h;
    }
};
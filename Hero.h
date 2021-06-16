#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;
using namespace std;

class Hero {
public:
    float x, y, w, h, dx, dy, speed = 0;
    int direction = 0;
    Image image;
    Texture texture;
    Sprite sprite;
    View view;
    Hero(float X, float Y, float W, float H) {
        w = W; h = H;
        image.loadFromFile("images/hero.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        x = X; y = Y;
        view.reset(FloatRect(x, y, 300, 300));
    }

    void movement(float time) {
        switch (direction) {
        case 0: dx = 0; dy = speed; break;
        case 1: dx = -speed; dy = 0; break;
        case 2: dx = speed; dy = 0; break;
        case 3: dx = 0; dy = -speed; break;
        //case 4: dx = speed; dy = speed; break;
        //case 5: dx = -speed; dy = speed; break;
        //case 6: dx = speed; dy = -speed; break;
        //case 7: dx = -speed; dy = -speed; break;
        //case 8: dx = 0; dy = 0; break;
        }
        y += dy * time;
        x += dx * time;
        speed = 0;
        heroWithMapInteractions();
        sprite.setPosition(x, y);
        viewCentersOnHero(x, y);
    }

    View viewCentersOnHero(float x, float y) {
        view.setCenter(x + w / 2, y + h / 2);
        return view;
    }
    void heroWithMapInteractions() {
        for (int i = x / rt; i < (x + w) / rt; i++)
            for (int j = y / rt; j < (y + h) / rt; j++) {
                if (MapLayout[i][j] == 'w' || MapLayout[i][j] == '0') {
                    if (dx > 0 && dy == 0)
                        x = i * rt - w;
                    if (dx < 0 && dy == 0)
                        x = i * rt + rt;
                    if (dx == 0 && dy > 0)
                        y= j * rt - h;
                    if (dx == 0 && dy < 0)
                        y = j * rt + rt;
                    //if (dx > 0 && dy > 0) {
                    //    x = i * rt - w;
                    //    y = j * rt - h;
                    //}
                    //if (dx < 0 && dy > 0) {
                    //    x = i * rt + rt;
                    //    y = j * rt - h;
                    //}
                    //if (dx > 0 && dy < 0) {
                    //    x = i * rt - w;
                    //    y = j * rt + rt;
                    //}
                    //if (dx < 0 && dy < 0) {
                    //    x = i * rt + rt;
                    //    y = j * rt + rt;
                    //}
                }
            }
    }
};
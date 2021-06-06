#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Hero {
public:
    float x, y, w, h, dx, dy, speed = 0;
    int direction = 0;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    View view;
    Hero(String F, float X, float Y, float W, float H) {
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 32, 48));
        x = X; y = Y;
        view.reset(FloatRect(x, y, 300, 300));
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
        /*bordersInteraction();*/
        sprite.setPosition(x, y);
        viewCentersOnHero(x, y);

    }
    View viewCentersOnHero(float x, float y) {
        view.setCenter(x + 16, y + 24);
        return view;
    }
   /* void bordersInteraction() {
        float tempdx = dx;
        float tempdy = dy;
        for (int i = y / 32; i < (y + h) / 32; i++)
            for (int j = x / 32; j < (x + w) / 32; j++) {
                if (Map[i][j] == '0') {
                    if (dy > 0) {
                         y = i * 32 - h;
                    }
                    else if (dy < 0) {
                        y = i * 32 + 32;
                    }
                    else if (dx > 0) {
                        x = j * 32 - w;
                    }
                    else if (dx < 0) {
                        x = j * 32 + 32;
                    }
                }
            }
    }*/
};
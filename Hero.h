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
    /**
    * \brief class hero
    */
public:
    float x, y, dx, dy, speed = 0; ///< x and y coordinates, dx and dy are x and y velocity, speed - general velocity
    float cameraX, cameraY = 0; ///< variables for handling camera postion
    float w, h = 0; ///< width and heigth of hitbox and sprite
    int direction = 0; ///< variable for handling direction of movement
    int hp = 100; ///< hero max hp
    float camLength = rt * mapWidth; ///< variable for camera width and height
    float timeAfterCollision = 0; ///< counter for making hero immune
    float animCounter = 0; ///< counter to handle animations
    bool alive = true;
    RectangleShape hitbox; ///< hitbox
    Image image; ///< image of models
    Texture texture; ///< texture of models
    Sprite sprite; ///< hero sprite
    View view; ///< camera

    /**
    * \brief hero object initializator
    * 
    * \param X starting x coord of hero
    * 
    * \param Y starting y coord of hero
    * 
    * \param W width of hero hitbox and sprite
    * 
    * \param H height of hero hitbox and sprite
    * 
    */
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

    /**
    * \brief function which handles general hero movement and things connected
    * such as keyboard surveillance, moving animation,
    * interactions of hero with map, sets position of hitbox
    * and sprite
    * 
    * \param time is time elapsed since the last game window
    * update and is used for smoother hero movement
    */
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
        viewCentersOnHero();
    }

    /**
    * \brief keyboard function handles key pressings
    */
    void keyboard() {
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction = 0;
            speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction = 1;
            speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction = 2;
            speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 3; 
            speed = 0.1;
             
        }
    }

    /**
    * \brief animation function manages hero movement animation
    * 
    * \param time is time elapsed since the last game window update
    * and is used for changing hero's sprite
    */
    void animation(float time) {
        
        if (direction == 0) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), 0, w, h));
        }
        if (direction == 1) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), h, w, h));
        }
        if (direction == 2) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), 2 * h, w, h));
        }
        if (direction == 3) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), 3 * h, w, h));
        }
    }

    /**
    * \brief utility function for centering camera on hero
    * 
    * \return sf::View view which is a camera position
    */
    View viewCentersOnHero() {   
        cameraX = x + w / 2; cameraY = y + h / 2;
        if (cameraX < camLength / 2)
            cameraX = camLength / 2;
        if (cameraY < camLength / 2)
            cameraY = camLength / 2;
        if (cameraX > mapWidth * rt - camLength / 2)
            cameraX = mapWidth * rt - camLength / 2;
        if (cameraY > mapHeight * rt - camLength / 2)
            cameraY = mapHeight * rt - camLength / 2;
        view.setCenter(cameraX, cameraY);
        return view;
    }

    /**
    * \brief function which oversees hero not crossing map borders
    */
    void heroWithMapInteractions() {
        if (x < rt)
            x = rt;
        if (x > (mapWidth - 1) * rt - w)
            x = (mapWidth - 1) * rt - w;
        if (y < rt)
            y = rt;
        if (y > (mapHeight - 1) * rt - h)
            y = (mapHeight - 1) * rt - h;
    }

    /**
    * \brief function which checks if hero collides with enemy and
    * reduces hp if so
    * 
    * \param enemy class object
    * 
    * \param time is time elapsed after last game window clear
    * and is used in  timeAfterCollision counter to make hero
    * immune for certain amount of time
    */
    void heroWithEnemyCollision(Enemy enemy, float time) {
        
        if (timeAfterCollision > 10) {
            if (FloatRect(x, y, w, h).intersects(FloatRect(enemy.x, enemy.y, enemy.w, enemy.h))) {
                hp -= enemy.damage;
                timeAfterCollision = 0;
            }
        }
        if (hp <= 0) 
            alive = false;

        timeAfterCollision += 0.005 * time;
    }
};
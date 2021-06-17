#include <SFML/Graphics.hpp>
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace std;
using namespace sf;

/**
* \brief enemy class
*/
class Enemy {
public:	///< actually no private in the class
	float x, y, dx, dy = 0; ///< x and y coord, dx and dy - x and y velocity
	float w, h = 0; ///< width and heigth of enemy sprite and hitbox
	float dirCount = 0; ///< counter for managing enemy movement directions
	float dirCountCap = 2000; ///< countCap for dirCount
	float animCounter = 0; ///< counter for managing animation
	float speed = 0.1; ///< general velocity
	int direction = 0; ///< movement direction
	int damage = 20; ///< damamge delt by enemy
	RectangleShape hitbox; ///< hitbox
	Image image; ///< image of models
	Texture texture; ///< texture of models
	Sprite sprite; ///< enemy sprite
	Enemy(float X, float Y, float W, float H) {
		w = W; h = H;
		x = X; y = Y;
		hitbox.setSize(Vector2f(w, h));
		hitbox.setPosition(x, y);
		hitbox.setFillColor(Color::Red);
		image.loadFromFile("images/enemy.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}

	/**
	* \brief movement function which handles enemy movement and things connected
	* such as walking animation, interacions with map borders
	* sets enemy's hitbox and sprite position
	* 
	* \param time is for smoother enemy movement and is used
	* in dirCounter to manage the direction in which enemy is moving
	*/
	void movement(float time) {

		if (direction == 0) {
			dx = 0; dy = speed;
		}
		else if (direction == 1) {
			dx = 0; dy = -speed;
		}
		else if (direction == 2) {
			dx = speed; dy = 0;
		}
		else if (direction == 3) {
			dx = -speed; dy = 0;
		}

		if (dirCount >= dirCountCap) {
			dirCount = 0;
			direction = RandDir();
		}
		dirCount += time;

		x += dx * time;
		y += dy * time;
		animation(time);
		enemyWithMapInteractions();
		hitbox.setPosition(x, y);
		sprite.setPosition(hitbox.getPosition());
	
	}


	/**
	* \brief function for making enemy not cross the map borders
	*/
	void enemyWithMapInteractions() { 
		
		if (x < rt) {
			x = rt;
			dirCount = dirCountCap;
		}
		if (x > (mapWidth - 1) * rt - w) {
			x = (mapWidth - 1) * rt - w;
			dirCount = dirCountCap;
		}
		if (y < rt) {
			y = rt;
			dirCount = dirCountCap;
		}
		if (y > (mapHeight - 1) * rt - h) {
			y = (mapHeight - 1) * rt - h;
			dirCount = dirCountCap;
		}
	}
	/**
	* \brief animation function handles enemy movement animation
	* 
	* \param time is used in counter animCounter to select what 
	* part of enemy.png programm should give to sprite
	*/
	void animation(float time) {
		if (direction == 0) {
			animCounter += 0.005 * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), 0, w, h));
		}
		if (direction == 1) {
			animCounter += 0.005 * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), 3 * h, w, h));
		}
		if (direction == 2) {
			animCounter += 0.005 * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), 2 * h, w, h));
		}
		if (direction == 3) {
			animCounter += 0.005 * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), h, w, h));
		}
	}
	/**
	* \brief utility function for getting random number 0-3 according
	* to certain condition
	* 
	* \return random number from 0 to 3
	*/
	int RandDir() {
		
		if (direction == 0 || direction == 1) {
			return 2 + rand() % 2;
		}
		else{
			return rand() % 2;
		}
	}
};




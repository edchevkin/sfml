#include <SFML/Graphics.hpp>
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace std;
using namespace sf;

class Enemy {
public:
	float x, y, dx, dy = 0;
	float w, h = 0;
	float dirCount = 0;
	float dirCountCap = 2000;
	float animCounter = 0;
	float speed = 0.1;
	int direction = 0;
	int damage = 20;
	RectangleShape hitbox;
	Image image;
	Texture texture;
	Sprite sprite;
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
		cout << dirCount << endl;
		dirCount += time;

		x += dx * time;
		y += dy * time;
		animation(time);
		enemyWithMapInteractions();
		hitbox.setPosition(x, y);
		sprite.setPosition(hitbox.getPosition());
	
	}

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
	int RandDir() {
		if (direction == 0 || direction == 1) {
			return 2 + rand() % 2;
		}
		else{
			return rand() % 2;
		}
	}
};


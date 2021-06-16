#include <SFML/Graphics.hpp>
#include "hero.h"
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace std;
using namespace sf;

class Enemy {
public:
	float x, y, w, h, dx, dy = 0;
	float count = 0;
	float speed = 0.1;
	int direction = 0;
	int damage = 20;
	int hp = 100;
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
		//image.loadFromFile("images/hero.png");
		//texture.loadFromImage(image);
		//sprite.setTexture(texture);
		//sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void movement(float time) {
		switch (direction) {
		case 0: dx = 0; dy = 0; break;
		case 1: dx = 0; dy = speed; break;
		case 2: dx = -speed; dy = 0; break;
		case 3: dx = speed; dy = 0; break;
		case 4: dx = 0; dy = -speed; break;
		}

		if (count > 3000) {
			direction = getRand();
			count = 0;
		}
		cout << direction << endl;
		count += time;

		x += dx * time;
		y += dy * time;

		enemyWithMapInteractions();
		hitbox.setPosition(x, y);
		//sprite.setPosition(hitbox.getPosition());
	
	}

	void enemyWithMapInteractions() {
		//for (int i = x / rt; i < (x + w) / rt; i++)
		//	for (int j = y / rt; j < (y + h) / rt; j++) {
		//		if (MapLayout[i][j] == 'w' || MapLayout[i][j] == '0') {
		//			if (dx > 0 && dy == 0) {
		//				x = i * rt - w;
		//				count = 3001;
		//			}
		//			if (dx < 0 && dy == 0){
		//				x = i * rt + rt;
		//				count = 3001;
		//			}
		//			if (dx == 0 && dy > 0){
		//				y = j * rt - h;
		//				count = 3001;
		//			}
		//			if (dx == 0 && dy < 0){
		//				y = j * rt + rt;
		//				count = 3001;
		//			}
		//		}
		//	}
		if (x < rt) {
			x = rt;
			count = 3001;
		}
		if (x > (mapWidth - 1) * rt - w) {
			x = (mapWidth - 1) * rt - w;
			count = 3001;
		}
		if (y < rt) {
			y = rt;
			count = 3001;
		}
		if (y > (mapHeight - 1) * rt - h) {
			y = (mapHeight - 1) * rt - h;
			count = 3001;
		}
	}
	int getRand() {
		return 1 + rand() % 4;
	}
};


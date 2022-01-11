#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
int h = 1010;
int w = 600;

void initPos(sf::Sprite* firstSprite, sf::Sprite* secondSprite, sf::Texture* text, bool flag) {
	if (flag) h = 1000;
	(*(firstSprite)).setTexture(*(text));
	(*(secondSprite)).setTexture(*(text));

	(*(firstSprite)).setScale(h / (*(firstSprite)).getLocalBounds().width, w / (*(firstSprite)).getLocalBounds().height);
	(*(secondSprite)).setScale(h / (*(secondSprite)).getLocalBounds().width, w / (*(secondSprite)).getLocalBounds().height);

	(*(firstSprite)).setPosition(0, 0);
	(*(secondSprite)).setPosition(1000, 0);

	h = 1010;
}

void changePos(sf::Vector2f firstImage, sf::Vector2f secondImage, sf::Sprite* firstSprite, sf::Sprite* secondSprite, float rate) {
	firstImage.x <= -999 ? firstImage.x = 1000 : firstImage.x -= rate;
	secondImage.x <= -999 ? secondImage.x = 1000 : secondImage.x -= rate;

	(*(firstSprite)).setPosition(firstImage);
	(*(secondSprite)).setPosition(secondImage);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Window");
	sf::Image img1, img2, img3, img4, img5;
	window.setFramerateLimit(70);

	img1.loadFromFile("Layers/L1.png");
	img2.loadFromFile("Layers/L2.png");
	img3.loadFromFile("Layers/L3.png");
	img4.loadFromFile("Layers/L4.png");
	img5.loadFromFile("Layers/L5.png");

	sf::Texture text1, text2, text3, text4, text5;
	text1.loadFromImage(img1);
	text2.loadFromImage(img2);
	text3.loadFromImage(img3);
	text4.loadFromImage(img4);
	text5.loadFromImage(img5);

	sf::Sprite sp11, sp12, sp21, sp22, sp31, sp32, sp41, sp42, sp51, sp52;
	sf::Vector2f sp1Pos(0, 0);
	sf::Vector2f sp2Pos(1000, 0);

	initPos(&sp11, &sp12, &text1, false);
	initPos(&sp21, &sp22, &text2, false);
	initPos(&sp31, &sp32, &text3, true);
	initPos(&sp41, &sp42, &text4, false);
	initPos(&sp51, &sp52, &text5, false);


	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		changePos(sp11.getPosition(), sp12.getPosition(), &sp11, &sp12, 0.6);
		changePos(sp21.getPosition(), sp22.getPosition(), &sp21, &sp22, 1);
		changePos(sp31.getPosition(), sp32.getPosition(), &sp31, &sp32, 1);
		changePos(sp41.getPosition(), sp42.getPosition(), &sp41, &sp42, 1);
		changePos(sp51.getPosition(), sp52.getPosition(), &sp51, &sp52, 3);

		window.draw(sp11);
		window.draw(sp12);
		window.draw(sp21);
		window.draw(sp22);
		window.draw(sp31);
		window.draw(sp32);
		window.draw(sp41);
		window.draw(sp42);
		window.draw(sp51);
		window.draw(sp52);

		window.display();
		window.clear();
	}

	return 0;
}
#pragma once
#include "Setings.h"
#include "meteor.h"
#include "Playr.h"
#include <vector>

class Game {
public:

	Game() {
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEORS_QTY);
		for (int i = 0; i < METEORS_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
	}

	void play() {
		while (window.isOpen() && player.isAlive()) {
			checkEvents();
			update();
			//if (player.getHp() <= 0) game_state = GAME_OVER;
			checkCollisions();
			draw();
		}
	}

private:

	sf::RenderWindow window;
	std::vector<Meteor*> meteorSprites;
	Player player;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		for (auto meteor : meteorSprites) {
			meteor->update();
		}
		player.update();
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->spawn();
				player.decreaseHp(meteor->getDamage());
			}
		}
	}

	void draw() {
		window.clear();
		for (auto meteor : meteorSprites) {
			window.draw(meteor->getSprite());
		}
		player.draw(window);
		window.display();
	}
};
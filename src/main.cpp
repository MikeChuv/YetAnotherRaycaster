#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Boundary.hpp"
#include "Particle.h"
#include "config.hpp"
#include "Vector.hpp"


int main(){

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	const int windowWidth = config::windowWidth;
	const int windowHeight = config::windowHeight;

	const float circleRadius = 10;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::CircleShape shape(circleRadius);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(circleRadius, circleRadius);

	srand(time(NULL));
	std::vector<Boundary> walls;
//	for(int i = 0; i < config::wallCount; ++i){
//		walls.emplace_back(
//				rand() % windowWidth,
//				rand() % windowHeight,
//				rand() % windowWidth,
//				rand() % windowHeight
//
//		);
//	}
	 walls.emplace_back(0, 0, windowWidth, 0);
	 walls.emplace_back(windowWidth, 0, windowWidth, windowHeight);
	 walls.emplace_back(windowWidth, windowHeight, 0, windowHeight);
	 walls.emplace_back(0, windowHeight, 0, 0);

	Particle particle(100, 200, config::fov);
	sf::Vector2f oldMouse(0, 0);


	while (window.isOpen()){


		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		// vecOps::constrain(mousePosition, circleRadius, windowWidth - circleRadius, circleRadius, windowHeight - circleRadius);
		sf::Vector2f dMouse = oldMouse - mousePosition;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			particle.move(Vector(config::moveStep, 0), walls);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			particle.move(Vector(-config::moveStep, 0), walls);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			particle.move(Vector(0, config::moveStep), walls);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			particle.move(Vector(0, -config::moveStep), walls);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			particle.turn(-1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			particle.turn(1);
		}

		window.clear();
        for(const auto& wall : walls) window.draw(wall);
		//particle.setPosition(mousePosition);
		particle.turn(-dMouse.x / 5);
		particle.look(walls);
        window.draw(particle);

		// shape.setPosition(mousePosition);
		// window.draw(shape);
		oldMouse = mousePosition;
		window.display();

	}
	return 0;

}

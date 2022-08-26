#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Boundary.hpp"
#include "Ray.hpp"
#include "Particle.hpp"
#include "config.hpp"
#include "operations.hpp"
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
	for(int i = 0; i < config::wallCount; ++i){
		walls.push_back(
			Boundary(
				rand() % windowWidth, 
				rand() % windowHeight, 
				rand() % windowWidth, 
				rand() % windowHeight
			)
		);
	}
	// walls.push_back(Boundary(0, 0, windowWidth, 0));
	// walls.push_back(Boundary(windowWidth, 0, windowWidth, windowHeight));
	// walls.push_back(Boundary(windowWidth, windowHeight, 0, windowHeight));
	// walls.push_back(Boundary(0, windowHeight, 0, 0));

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
		for(auto wall : walls) wall.show(window);
		//particle.setPosition(mousePosition);
		particle.turn(-dMouse.x / 5);
		particle.look(walls);
		particle.show(window);
		
		// shape.setPosition(mousePosition);
		// window.draw(shape);
		oldMouse = mousePosition;
		window.display();

	}
	return 0;

}

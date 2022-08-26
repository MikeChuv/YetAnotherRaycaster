#pragma once
#include <SFML/Graphics.hpp>
#include "operations.hpp"
#include "Vector.hpp"

// TODO: inherit from Drawable and define draw function for RenderWindow RenderTarget
class Boundary{

public:

	Vector a, b;

	Boundary(float ax, float ay, float bx, float by){
		a = Vector(ax, ay);
		b = Vector(bx, by);
	}

	float length(){
		Vector wall = a - b;
		return wall.length();
	}


	void show(sf::RenderWindow& window){
		sf::Vertex line[] =
			{
				sf::Vertex(a),
				sf::Vertex(b)
			};

		window.draw(line, 2, sf::Lines);
	}

};
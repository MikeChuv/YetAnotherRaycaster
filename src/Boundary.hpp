#pragma once
#include <SFML/Graphics.hpp>
#include "operations.h"
#include "Vector.hpp"

class Boundary : public sf::Drawable{

public:

	Vector a, b;

	Boundary(float ax, float ay, float bx, float by){
		a = Vector(ax, ay);
		b = Vector(bx, by);
	}

	float length() const{
		Vector wall(a - b);
		return wall.length();
	}

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
        sf::Vertex line[] = { sf::Vertex(a),
                              sf::Vertex(b) };

        target.draw(line, 2, sf::Lines);
    }

};

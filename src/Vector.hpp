#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Vector : public sf::Vector2f {

public:

	Vector() : sf::Vector2f(){}

	Vector(float x, float y) : sf::Vector2f(x, y){}

	explicit Vector(float angle) : sf::Vector2f(cos(angle), sin(angle)){}

	explicit Vector(sf::Vector2f vec) : sf::Vector2f(vec){}

	float getAngle() const {
		return std::atan2(y, x);
	}

	float length() const {
		return std::sqrt(x * x + y * y);
	}

	void normalize(){
		*this /= length();
	}

	void turn(float angle){
		float newAngle = getAngle() + angle;
		float curLength = length();
		x = curLength * cos(newAngle);
		y = curLength * sin(newAngle);
	}

	void constrain(float cxa, float cxb, float cya, float cyb){
		if (x <= cxa) x = cxa;
		if (x >= cxb) x = cxb;
		if (y <= cya) y = cya;
		if (y >= cyb) y = cyb;	
	}

};
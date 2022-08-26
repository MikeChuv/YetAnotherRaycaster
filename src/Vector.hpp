#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Vector : public sf::Vector2f {

public:

	Vector() : sf::Vector2f(){}

	Vector(float x, float y) : sf::Vector2f(x, y){}

	Vector(float angle) : sf::Vector2f(cos(angle), sin(angle)){}

	Vector(sf::Vector2f vec) : sf::Vector2f(vec){}

	float getAngle() const {
		return atan2(y, x);
	}

	float length() const {
		return sqrt(x * x + y * y);
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
#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

namespace vecOps
{
	void normalizeV2f (sf::Vector2f& vec){
		vec /= sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	float lengthV2f (sf::Vector2f vec){
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	sf::Vector2f fromAngle(float angle){
		return sf::Vector2f(cos(angle), sin(angle));
	}

	float angleFromV2f(sf::Vector2f vec){
		return atan2(vec.y, vec.x);
	}

	void constrain(sf::Vector2f& vec, float cxa, float cxb, float cya, float cyb){
		if (vec.x <= cxa) vec.x = cxa;
		if (vec.x >= cxb) vec.x = cxb;
		if (vec.y <= cya) vec.y = cya;
		if (vec.y >= cyb) vec.y = cyb;	
	}
}


namespace mathOps
{
	float radians(float degrees){
		return degrees * M_PI / 180;
	}


	float hypotenuse(float s1, float s2){
		return sqrt(s1 * s1 + s2 * s2);
	}

	float map(float x, float in_min, float in_max, float out_min, float out_max) {
  		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}



}
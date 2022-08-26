#pragma once
#include <SFML/Graphics.hpp>
#include "Boundary.hpp"
#include <iostream>
#include "operations.hpp"
#include "config.hpp"
#include <vector>
#include "Vector.hpp"



class Ray
{

public:
	Vector pos, dir, pt;
	static float maxLength;
	float rayLength;

	Ray(float x, float y, float angle)
	{
		pos = Vector(x, y);
		dir = Vector(angle);
	}
	
	Ray(Vector _pos, float angle)
	{
		pos = _pos;
		dir = Vector(angle);
	}

	void setPosition(Vector _pos){
		pos = _pos;
	}

	void setDirection(float angle){
		dir = Vector(angle);
	}

	void lookAt(Vector point){
		dir = point - pos;
		dir.normalize();
	}

	Vector castOn(Boundary wall){
		// line-line intersection check: 
		// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment

		const Vector w = wall.a - wall.b; // vector - boundary line
		const Vector da = wall.a - pos; // vector from pos to "a" point of boundary

		float den = dir.x * w.y - dir.y * w.x;

		if (abs(den) < 0.00001) {
			// return Vector(-1, -1);
			return Vector(INFINITY, INFINITY);
		}  
		else {
			float t = ( dir.x * da.y - dir.y * da.x ) / den;
			float u = ( da.x * w.y - da.y * w.x ) / den;

			if(t >= 0 && t <= 1 && u >= 0){
				pt = wall.a + t * (wall.b - wall.a);
				return pt;
			}
			else {
				// return Vector(-1, -1);
				return Vector(INFINITY, INFINITY);
			}

		}
	}

	Vector castOn(std::vector<Boundary> walls){
		float record = INFINITY;
		// Vector result = Vector(-1, -1);
		Vector result = Vector(INFINITY, INFINITY);
		for(int i = 0; i < walls.size(); ++i){
			Vector cur = castOn(walls[i]);
			// if (cur.x != -1 && cur.y != -1) {
			if (cur.x != INFINITY && cur.y != INFINITY) {
				float dist = Vector(pos - cur).length();
				if (dist < record) {
					record = dist;
					result = cur;
				} 
			}
		}
		pt = result;
		// rayLength = record;
		// if (pt.x == -1 && pt.y == -1) rayLength = 0;
		if (pt.x == INFINITY && pt.y == INFINITY) rayLength = INFINITY; // change to inf and test
		else rayLength = record;

		return result;
	}


	void show(sf::RenderWindow &window, float headingAngle)
	{		
		// line to show ray
		// float dist = Vector(pt - pos).length();
		// maxLength = rayLength > maxLength ? rayLength : maxLength;
		float opacity = 100 * (maxLength - rayLength) / maxLength;


		// float dAngle = headingAngle - dir.getAngle();
		// if (dAngle < 0) dAngle += 2 * M_PI;
		// if (dAngle > 2 * M_PI) dAngle -= 2 * M_PI;
		// float trueDistance = rayLength * cos(dAngle); // проекция на направление взгляда
		// float opacity = 100 * (maxLength - trueDistance) / maxLength;

		// const float theta = 20;
		// trueDistance -= theta / cos(dAngle);
		// trueDistance *= cos(dAngle);

		// if diatsnce to wall is larger than height of rect is smaller
		// float rh = mathOps::map(trueDistance, 0, Ray::maxLength, config::windowHeight, 0);
		// maybe better shading with this
		// const float wSq = config::windowHeight * config::windowHeight;
		// const float rLSq = rh * rh;
		// const float rLSq = trueDistance * trueDistance;
		// float col = mathOps::map(rLSq, 0, wSq, 0, 50);
		// opacity = mathOps::map(rayLength, 0, wSq, 0, 50);


		sf::Vertex line[] =
			{
				sf::Vertex(pos, sf::Color(255,100,255, 100)),
				sf::Vertex(pt, sf::Color(255,100,255, opacity))
			};

		// if (pt.x != -1 && pt.y != -1) {
		if (pt.x != INFINITY && pt.y != INFINITY) {
			window.draw(line, 2, sf::Lines);
		}
	}
};


float Ray::maxLength = mathOps::hypotenuse(config::windowWidth, config::windowHeight);
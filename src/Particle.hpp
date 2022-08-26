#pragma once
#include <SFML/Graphics.hpp>
#include "Ray.hpp"
#include "operations.hpp"
#include "config.hpp"
#include <vector>
#include <iostream>


class Particle {

public:
	Vector pos;
	std::vector<Ray>rays;
	std::vector<float>distances[config::windowWidth];
	float angleStep = config::angleStep;
	const float radius = 20;
	int rayCount = 0;


	Particle(float x, float y){
		for (float a = 0; a < 360; a += angleStep){
			rays.push_back(Ray(x, y, mathOps::radians(a)));
		}
		pos = Vector(x, y);
		rayCount = rays.size();
	}

	Particle(float x, float y, float fov){
		// for (float a = -fov / 2; a < fov / 2; a += angleStep){
		// 	rays.push_back(Ray(x, y, mathOps::radians(a)));
		// }

		for (float i = config::windowWidth / 2; i > 0; i-=1){
			float phi = atan(i / config::screenDistance); // it should fall
			rays.push_back(Ray(x, y, -phi));
		}
		for (float i = 0; i < config::windowWidth / 2; i+=1){
			float phi = atan(i / config::screenDistance); // it should rise
			rays.push_back(Ray(x, y, phi));
		}
		pos = Vector(x, y);
		rayCount = rays.size();
		// std::cout << "Ray Count: " << rayCount << "\n";
	}

	void turn(float angle){
		for(int i = 0; i < rays.size(); ++i){
			// float currentAngle = vecOps::angleFromV2f(rays[i].dir);
			float currentAngle = rays[i].dir.getAngle();
			rays[i].setDirection(currentAngle + mathOps::radians(angle));
		}
	}

	bool checkBoundaryCollision(std::vector<Boundary> walls){
		bool result = false;
		for(int i = 0; i < walls.size(); ++i){
			float dr = walls[i].length();
			sf::Vector2f p1 = walls[i].a - pos;
			sf::Vector2f p2 = walls[i].b - pos;
			float D = p1.x * p2.y - p2.x * p1.y;
			float incidence = radius * radius * dr * dr - D * D;
			if(incidence >= 0 && !result) result = true;
		}
		return result;
	}

	void move(Vector offset, std::vector<Boundary> walls){
		int dirRayIdx = rays.size() / 2;
		// bool collision = vecOps::lengthV2f(rays[dirRayIdx].castOn(walls) - pos) < radius;
		// bool collision = checkBoundaryCollision(walls);
		// if (!collision) setPosition(rays[dirRayIdx].pos + rays[dirRayIdx].dir * offset);
		float normAngle = rays[dirRayIdx].dir.getAngle() - M_PI_2;
		// sf::Vector2f xoff = vecOps::fromAngle(normAngle);
		// Vector xoff = Vector(normAngle);
		Vector xoff(normAngle);
		setPosition(rays[dirRayIdx].pos + xoff * offset.x + rays[dirRayIdx].dir * offset.y);

	}
	
	Particle(Vector position){
		for (int a = 0; a < 360; a += angleStep){
			rays.push_back(Ray(position, mathOps::radians(a)));
		}
		pos = position;
	}

	void setPosition(Vector position){
		for(int i = 0; i < rays.size(); ++i){
			rays[i].setPosition(position);
		}
		pos = position;
	}

	void look(Boundary wall){
		for(int i = 0; i < rays.size(); ++i){
			Vector pt = rays[i].castOn(wall);
		}
	}


	void look(std::vector<Boundary> walls){
		for(int i = 0; i < rays.size(); ++i){
			Vector pt = rays[i].castOn(walls);
		}
	}


	// TODO: try inherit RenderWindow in a new class and add overloads
	// for rendering rays or walls
	void show(sf::RenderWindow& window){
		float headingAngle = rays[rays.size() / 2].dir.getAngle();
		for(int i = 0; i < rays.size(); ++i){
			sf::RectangleShape rect;
			
			// if ray is not pointing to inf
			if (rays[i].rayLength != INFINITY){ 
				// correcting fisheye effect
				float dAngle = headingAngle - rays[i].dir.getAngle();
				if (dAngle < 0) dAngle += 2 * M_PI;
				if (dAngle > 2 * M_PI) dAngle -= 2 * M_PI;

				float trueDistance = rays[i].rayLength; // проекция на направление взгляда

				// const float theta = 20;
				// trueDistance -= theta / cos(dAngle);
				// trueDistance *= cos(dAngle);

				// if diatsnce to wall is larger than height of rect is smaller
				// float rh = mathOps::map(trueDistance, 0, Ray::maxLength, config::windowHeight, 0);
				// -(rays.size() / 2 - i) * a in left side
				// -(i - rays.size() / 2) * a in right side
				// if(i < rays.size() / 2) trueDistance -= rays.size() / 2 - i;
				// if(i >= rays.size() / 2) trueDistance -= i - rays.size() / 2;
				// float rh = config::windowHeight - trueDistance; // инверсное отображение????

				float rh = mathOps::map(trueDistance, 0, Ray::maxLength, config::windowHeight, 0);
				// std::cout << rh << '\n';
				rect.setSize(sf::Vector2f(1, rh));
				rect.setPosition(i, config::windowHeight/2 - rh/2);

				// maybe better shading with this
				const float wSq = config::windowHeight * config::windowHeight;
				const float rLSq = rh * rh;
				// const float rLSq = trueDistance * trueDistance;
				float col = mathOps::map(rLSq, 0, wSq, 0, 255);

				// float col = 255 * rh / Ray::maxLength;
				rect.setFillColor(sf::Color(255, 255, 255, col));
				window.draw(rect);
			}
			rays[i].show(window, headingAngle);
		}
	}



};

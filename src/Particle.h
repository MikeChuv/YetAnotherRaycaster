//
// Created by mchuv on 11.03.2023.
//

#ifndef YETANOTHERRAYCASTER_PARTICLE_H
#define YETANOTHERRAYCASTER_PARTICLE_H


#include <SFML/Graphics.hpp>
#include "Ray.h"
#include "operations.h"
#include "config.hpp"
#include <vector>
#include <iostream>


class Particle : public sf::Drawable{

public:
    Vector pos;
    std::vector<Ray>rays;
    std::vector<float>distances[config::windowWidth];
    float angleStep = config::angleStep;
    const float radius = 20;
    size_t rayCount = 0;


    Particle(float x, float y);

    explicit Particle(Vector position);

    Particle(float x, float y, float fov);

    void turn(float angle);

    bool checkBoundaryCollision(const std::vector<Boundary>& walls) const;

    void move(Vector offset, const std::vector<Boundary>& walls);


    void setPosition(Vector position);

    void look(const Boundary& wall);

    void look(const std::vector<Boundary>& walls);


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};



#endif //YETANOTHERRAYCASTER_PARTICLE_H

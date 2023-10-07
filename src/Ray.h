#ifndef YETANOTHERRAYCASTER_RAY_H
#define YETANOTHERRAYCASTER_RAY_H

#include <SFML/Graphics.hpp>
#include "Boundary.hpp"
#include <iostream>
#include "operations.h"
#include "config.hpp"
#include <vector>
#include "Vector.hpp"

class Ray : public sf::Drawable{

public:
    Vector pos, dir, pt;
    static float maxLength;
    float rayLength;

    Ray(float x, float y, float angle);

    Ray(Vector _pos, float angle);

    void setPosition(Vector _pos);

    void setDirection(float angle);

    void lookAt(Vector point);

    Vector castOn(const Boundary &wall);

    Vector castOn(const std::vector<Boundary> &walls);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif //YETANOTHERRAYCASTER_RAY_H

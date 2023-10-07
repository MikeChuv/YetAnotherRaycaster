//
// Created by mchuv on 08.03.2023.
//

#include "operations.h"

void vecOps::normalizeV2f (sf::Vector2f& vec){
    vec /= sqrt(vec.x * vec.x + vec.y * vec.y);
}

float vecOps::lengthV2f (sf::Vector2f vec){
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f vecOps::fromAngle(float angle){
    return sf::Vector2f(cos(angle), sin(angle));
}

float vecOps::angleFromV2f(sf::Vector2f vec){
    return atan2(vec.y, vec.x);
}

void vecOps::constrain(sf::Vector2f& vec, float cxa, float cxb, float cya, float cyb){
    if (vec.x <= cxa) vec.x = cxa;
    if (vec.x >= cxb) vec.x = cxb;
    if (vec.y <= cya) vec.y = cya;
    if (vec.y >= cyb) vec.y = cyb;
}


float mathOps::radians(float degrees){
    return degrees * M_PI / 180;
}


float mathOps::hypotenuse(float s1, float s2){
    return sqrt(s1 * s1 + s2 * s2);
}

float mathOps::map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


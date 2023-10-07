
#include "Particle.h"

Particle::Particle(float x, float y){
    for (float a = 0; a < 360; a += angleStep){
        rays.emplace_back(x, y, mathOps::radians(a));
    }
    pos = Vector(x, y);
    rayCount = rays.size();
}

Particle::Particle(Vector position){
    for (int a = 0; a < 360; a += angleStep){
        rays.emplace_back(position, mathOps::radians(a));
    }
    pos = position;
}

Particle::Particle(float x, float y, float fov){
//		for (float a = -fov / 2; a < fov / 2; a += angleStep){
//			rays.emplace_back(x, y, mathOps::radians(a));
//		}

    for (int i = config::windowWidth / 2; i > 0; i-=config::pixelStep){
        float phi = atan((float)i / config::screenDistance); // it should fall
        rays.emplace_back(x, y, -phi);
    }
    for (int i = 0; i < config::windowWidth / 2; i+=config::pixelStep){
        float phi = atan((float)i / config::screenDistance); // it should rise
        rays.emplace_back(x, y, phi);
    }
    pos = Vector(x, y);
    rayCount = rays.size();
    // std::cout << "Ray Count: " << rayCount << "\n";
}

void Particle::turn(float angle){
    float angleInRad = mathOps::radians(angle);
    for(Ray & ray : rays){
        // float currentAngle = vecOps::angleFromV2f(rays[i].dir);
        ray.setDirection(ray.dir.getAngle() + angleInRad);
    }
}

bool Particle::checkBoundaryCollision(const std::vector<Boundary>& walls) const{
    bool result = false;
    for(const Boundary & wall : walls){
        float dr = wall.length();
        sf::Vector2f p1 = wall.a - pos;
        sf::Vector2f p2 = wall.b - pos;
        float D = p1.x * p2.y - p2.x * p1.y;
        float incidence = radius * radius * dr * dr - D * D;
        if(incidence >= 0 && !result) result = true;
    }
    return result;
}

void Particle::move(Vector offset, const std::vector<Boundary>& walls){
    size_t dirRayIdx = rays.size() / 2;
    // bool collision = vecOps::lengthV2f(rays[dirRayIdx].castOn(walls) - pos) < radius;
    // bool collision = checkBoundaryCollision(walls);
    // if (!collision) setPosition(rays[dirRayIdx].pos + rays[dirRayIdx].dir * offset);
    float normAngle = rays[dirRayIdx].dir.getAngle() - M_PI_2;
    // sf::Vector2f xoff = vecOps::fromAngle(normAngle);
    // Vector xoff = Vector(normAngle);
    Vector xoff(normAngle);
    setPosition(Vector(rays[dirRayIdx].pos + xoff * offset.x + rays[dirRayIdx].dir * offset.y));

}


void Particle::setPosition(Vector position){
    for(auto & ray : rays){
        ray.setPosition(position);
    }
    pos = position;
}

void Particle::look(const Boundary& wall){
    for(auto & ray : rays){
        Vector pt = ray.castOn(wall);
    }
}


void Particle::look(const std::vector<Boundary>& walls){
    for(auto & ray : rays){
        Vector pt = ray.castOn(walls);
    }
}


void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
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

//                if (trueDistance < config::screenDistance) continue;
//                 const float theta = 20;
//                 trueDistance -= theta / cos(dAngle);
//                trueDistance -= config::screenDistance;
            trueDistance *= cos(dAngle);
//            trueDistance *= atan((float)i / config::screenDistance);

            // if distance to wall is larger than height of rect is smaller
//				float rh = config::windowHeight - trueDistance; // инверсное отображение????

            float rh = mathOps::map(trueDistance, 0, Ray::maxLength, config::windowHeight, 0);
            // std::cout << rh << '\n';
            rect.setSize(sf::Vector2f(config::pixelStep, rh));
            rect.setPosition(i * config::pixelStep, config::windowHeight/2 - rh/2);

            // maybe better shading with this
            const float wSq = config::windowHeight * config::windowHeight;
            const float rLSq = rh * rh;
            // const float rLSq = trueDistance * trueDistance;
            auto col = (uint8_t)mathOps::map(rLSq, 0, wSq, 0, 255);

            // float col = 255 * rh / Ray::maxLength;
            rect.setFillColor(sf::Color(255, 255, 255, col));
            target.draw(rect);
        }
        target.draw(static_cast<const sf::Drawable&>(rays[i]));
//            rays[i].show(window, headingAngle);
    }
}


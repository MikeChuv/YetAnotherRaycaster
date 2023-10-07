
#ifndef YETANOTHERRAYCASTER_OPERATIONS_H
#define YETANOTHERRAYCASTER_OPERATIONS_H

#include <math.h>
#include <SFML/Graphics.hpp>

namespace vecOps
{
	void normalizeV2f (sf::Vector2f& vec);

	float lengthV2f (sf::Vector2f vec);

	sf::Vector2f fromAngle(float angle);

	float angleFromV2f(sf::Vector2f vec);

	void constrain(sf::Vector2f& vec, float cxa, float cxb, float cya, float cyb);
}


namespace mathOps
{
	float radians(float degrees);

	float hypotenuse(float s1, float s2);

	float map(float x, float in_min, float in_max, float out_min, float out_max);
}

#endif // YETANOTHERRAYCASTER_OPERATIONS_H

#pragma once
#include "operations.h"

namespace config{

	const float fov = 90;
	const int wallCount = 5;

	const int windowWidth = 1280;
	const int windowHeight = 720;

	const float angleStep = fov / windowWidth;
	const float screenDistance = windowWidth / (tan(mathOps::radians(fov / 2)) * 2);
  const int pixelStep = 1;

	const int moveStep = 1;


}

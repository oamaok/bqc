#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "physics/aabb.h"

namespace physics
{
	bool intersects(AABB a, AABB b);
	glm::vec2 minimumTranslation(AABB a, AABB b);
}

#endif
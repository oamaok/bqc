#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "physics/aabb.h"

namespace physics
{
	bool intersects(const AABB& a, const AABB& b);
	glm::vec2 minimumTranslation(const AABB& a, const AABB& b);
}

#endif
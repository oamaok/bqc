#include "physics/physics.h"

namespace physics
{
	bool intersects(AABB a, AABB b)
	{
		return !(a.max.x < b.min.x ||
			a.max.y < b.min.y ||
			a.min.x > b.max.x ||
			a.min.y > b.max.y);
	}

	glm::vec2 minimumTranslation(AABB a, AABB b)
	{
		glm::vec2 amin = a.min;
        glm::vec2 amax = a.max;
        glm::vec2 bmin = b.min;
        glm::vec2 bmax = b.max;

        glm::vec2 mtd(0.0f, 0.0f);

        float left = (bmin.x - amax.x);
        float right = (bmax.x - amin.x);
        float top = (bmin.y - amax.y);
        float bottom = (bmax.y - amin.y);

        if (left > 0 || right < 0) return glm::vec2(0.0f, 0.0f);
        if (top > 0 || bottom < 0) return glm::vec2(0.0f, 0.0f);

        if (abs(left) < right)
            mtd.x = left;
        else
            mtd.x = right;

        if (abs(top) < bottom)
            mtd.y = top;
        else
            mtd.y = bottom;

        if (abs(mtd.x) < abs(mtd.y))
            mtd.y = 0;
        else
            mtd.x = 0; 
        return mtd;
	}
}
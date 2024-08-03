#include "core/aabb.h"

namespace Blocky {
    /// <summary>
    /// Returns true if one aabb is inside the other passed aabb
    /// </summary>
    /// <param name="a"> AABB contains min and max vector</param>
    /// <param name="b"> AABB contains min and max vector</param>
    /// <returns>true if collision false if no collision</returns>
    bool AABB::collide(AABB a, AABB b)
    {
        return
            a.min.x <= b.max.x &&
            a.max.x >= b.min.x &&
            a.min.y <= b.max.y &&
            a.max.y >= b.min.y &&
            a.min.z <= b.max.z &&
            a.max.z >= b.min.z;
    }
}
#include "base-types.hpp"
#include <cmath>

bool kharitonov::checkIntersect(const rectangle_t& r1, const rectangle_t& r2)
{
  return ((std::fabs(r1.pos.x - r2.pos.x) < ((r1.width + r2.width) / 2))
      && (std::fabs(r1.pos.y - r2.pos.y) < ((r1.height + r2.height) / 2)));
}

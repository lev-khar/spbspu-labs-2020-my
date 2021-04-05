#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace kharitonov {
  struct point_t {
    double x;
    double y;
  };

  struct rectangle_t {
    double width;
    double height;
    point_t pos;
  };

  bool checkIntersect(const rectangle_t&, const rectangle_t&);
}

#endif

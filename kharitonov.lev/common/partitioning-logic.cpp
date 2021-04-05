#include "partitioning-logic.hpp"

#include <stdexcept>

#include "base-types.hpp"
#include "matrix.hpp"
#include "shape.hpp"

kharitonov::Matrix kharitonov::partition(const kharitonov::Shape::ArrayShapePtr& shapes, size_t size)
{
  kharitonov::Matrix matrix;

  for (size_t s = 0; s < size; s++)
  {
    if (shapes[s] == nullptr)
    {
      continue;
    }
    size_t desiredLayer = 0;
    for (size_t i = 0; i < matrix.getLayersNumber(); i++)
    {
      desiredLayer = i;
      for (size_t j = 0; j < matrix[i].getLength(); j++)
      {
        if (checkIntersect(matrix[i][j]->getFrameRect(), shapes[s]->getFrameRect()))
        {
          desiredLayer = i + 1;
          break;
        }
      }
      if (desiredLayer == i)
      {
        break;
      }
    }
    if (desiredLayer == matrix.getLayersNumber())
    {
      matrix.addLayer();
    }
    matrix[desiredLayer].addShape(shapes[s]);
  }
  return matrix;
}

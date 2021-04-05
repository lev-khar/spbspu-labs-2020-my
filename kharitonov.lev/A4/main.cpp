#include <iostream>
#include <stdexcept>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "partitioning-logic.hpp"

int main() 
{
  kharitonov::CompositeShape compShape;
  std::shared_ptr<kharitonov::Shape> myCirclePtr;
  std::shared_ptr<kharitonov::Shape> myCircle2Ptr;
  std::shared_ptr<kharitonov::Shape> myRectanglePtr;
  try
  {
    try
    {
      kharitonov::Circle myCircle(kharitonov::point_t{ 15.9, 2.1 }, 5.7);
      myCirclePtr = std::make_shared<kharitonov::Circle>(myCircle);
      kharitonov::Circle myCircle2(kharitonov::point_t{ 14.1, 1.5 }, 55.7);
      myCircle2Ptr = std::make_shared<kharitonov::Circle>(myCircle2);
      kharitonov::Rectangle myRectangle({ 2.7, 13.2, { -1.2, 4.6 } });
      myRectanglePtr = std::make_shared<kharitonov::Rectangle>(myRectangle);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }

    myRectanglePtr->display();

    std::cout << "\nRotation for Rectangle: \n";

    kharitonov::Rectangle newRect00(myRectanglePtr->getFrameRect());
    newRect00.display();
    myRectanglePtr->rotate(30);
    newRect00 = myRectanglePtr->getFrameRect();
    newRect00.display();
    myRectanglePtr->rotate(-30);
    newRect00 = myRectanglePtr->getFrameRect();
    newRect00.display();

    myRectanglePtr->rotate(90);
    newRect00 = myRectanglePtr->getFrameRect();
    newRect00.display();
    myRectanglePtr->rotate(-90);
    newRect00 = myRectanglePtr->getFrameRect();
    newRect00.display();

    myRectanglePtr->rotate(120);
    newRect00 = myRectanglePtr->getFrameRect();
    newRect00.display();
    myRectanglePtr->rotate(-120);
    newRect00 = myRectanglePtr->getFrameRect();
    newRect00.display();

    try
    {
      compShape.append(myCirclePtr);
      compShape.append(myCircle2Ptr);
      compShape.append(myRectanglePtr);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }
    compShape.display();
    std::cout << "\nRotation for CompositeShape: \n";

    kharitonov::Rectangle newRect01 = compShape.getFrameRect();
    newRect01.display();
    compShape.rotate(30);
    newRect01 = compShape.getFrameRect();
    newRect01.display();
    compShape.rotate(-30);
    newRect01 = compShape.getFrameRect();
    newRect01.display();

    compShape.rotate(90);
    newRect01 = compShape.getFrameRect();
    newRect01.display();
    compShape.rotate(-90);
    newRect01 = compShape.getFrameRect();
    newRect01.display();

    compShape.rotate(120);
    newRect01 = compShape.getFrameRect();
    newRect01.display();
    compShape.rotate(-120);
    newRect01 = compShape.getFrameRect();
    newRect01.display();

    compShape.display();

    std::cout << "\nForming Matrix:\n";
    try
    {
      kharitonov::Matrix matrix = compShape.getPartition();
      matrix.display();
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Unexpected Error: " << e.what();
    return 2;
  }
  return 0;
}

#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "base-types.hpp"

int main() {
  kharitonov::Shape* polymorphicObject = nullptr;
  try
  {
    kharitonov::Circle myCircle({ 8.1, 9.4 }, 35.99);
    polymorphicObject = &myCircle;

    polymorphicObject->display();

    polymorphicObject->move({5.4, 9.78});
    polymorphicObject->display();

    std::cout << "\nTest for function getFrameRect for circle:\n";
    kharitonov::Rectangle newRect1(polymorphicObject->getFrameRect());
    newRect1.display();

    std::cout << "\nTest for function getArea for circle: " << polymorphicObject->getArea() << "\n\n";

    polymorphicObject->move(15.4, -9.75);
    polymorphicObject->display();

    std::cout << "\n\nTest for function scale with factor 2.5 for circle:\n";
    polymorphicObject->scale(2.5);
    polymorphicObject->display();
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what();
    return 1;
  }
  try
  {
    kharitonov::Rectangle myRectangle({ 12.8, 34.67, {2, 5} });
    polymorphicObject = &myRectangle;

    polymorphicObject->display();

    polymorphicObject->move(15.4, -9.75);
    polymorphicObject->display();

    std::cout << "\nTest for function getFrameRect for rectangle:\n";
    kharitonov::Rectangle newRect2(polymorphicObject->getFrameRect());
    newRect2.display();

    std::cout << "\nTest for function getArea for rectangle: " << polymorphicObject->getArea();

    std::cout << "\nTest for function scale with factor 1.5 for rectangle:\n";
    polymorphicObject->scale(1.5);
    polymorphicObject->display();
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what();
    return 1;
  }
  return 0;
}

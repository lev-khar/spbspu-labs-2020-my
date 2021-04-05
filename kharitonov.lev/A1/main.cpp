#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main() {
  Shape * polymorphicObjects[2];
  Rectangle myRectangle({12.8, 34.67, {2, 5}});
  Circle myCircle({8.1, 9.4}, 35.99);

  polymorphicObjects[0] = &myCircle;
  polymorphicObjects[1] = &myRectangle;
  polymorphicObjects[0]->display();
  polymorphicObjects[1]->display();

  polymorphicObjects[0]->move({5.4, 9.78});
  polymorphicObjects[0]->display();

  std::cout << "\nTest for function getFrameRect for circle:\n";
  Rectangle newRect1(polymorphicObjects[0]->getFrameRect());
  newRect1.display();

  std::cout << "\nTest for function getArea for circle: " << polymorphicObjects[0]->getArea() << "\n";

  polymorphicObjects[1]->move(15.4, -9.75);
  polymorphicObjects[1]->display();

  std::cout << "\nTest for function getFrameRect for rectangle:\n";
  Rectangle newRect2(polymorphicObjects[1]->getFrameRect());
  newRect2.display();

  std::cout << "\nTest for function getArea for rectangle: " << polymorphicObjects[1]->getArea();
  return 0;
}

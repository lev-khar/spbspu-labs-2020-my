#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"

int main() {
  kharitonov::CompositeShape compShape;
  //first try is for all unexpected errors
  try
  {
    try
    {
      kharitonov::Circle myCircle({ 15.9, 2.1 }, 5.7);
      kharitonov::Rectangle myRectangle({ 2.7, 13.2, { -1.2, 4.6 } });

      compShape.append(std::make_shared<kharitonov::Circle>(myCircle));
      compShape.append(std::make_shared<kharitonov::Rectangle>(myRectangle));
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }

    compShape.display();

    std::cout << "\nTest for function getFrameRect for CompositeShape:\n";
    try
    {
      kharitonov::Rectangle newRect0(compShape.getFrameRect());
      newRect0.display();
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "Error: " << e.what();
      return 2;
    }

    std::cout << "\nAdded one more shape\n";
    try
    {
      kharitonov::Circle addCircle({ 71.99, 2.4 }, 0.8);
      compShape.append(std::make_shared<kharitonov::Circle>(addCircle));
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }

    compShape.display();
    std::cout << "\nFunction getFrameRect for CompositeShape:\n";

    try
    {
      kharitonov::Rectangle newRect1(compShape.getFrameRect());
      newRect1.display();
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "Error: " << e.what();
      return 2;
    }

    std::cout << "\nRemoved the first figure:\n";
    try
    {
      compShape.remove(0);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }

    compShape.display();
    std::cout << "\nFunction getFrameRect for CompositeShape:\n";

    try
    {
      kharitonov::Rectangle newRect2(compShape.getFrameRect());
      newRect2.display();
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "Error: " << e.what();
      return 2;
    }

    std::cout << "\nTest for bracket operator for CompositeShape: ";

    try
    {
      if (compShape[0] != nullptr)
      {
        std::cout << "successful\n";
      }
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }

    std::cout << "\nCopied CompShape:\n";
    kharitonov::CompositeShape copyCompShape(compShape);
    copyCompShape.display();
    std::cout << "\nFunction getFrameRect for CompositeShape:\n";

    try //united those because getCentre calls getFrameRect which can throw logic_error
    {
      kharitonov::Rectangle newRect3(copyCompShape.getFrameRect());
      newRect3.display();

      std::cout << "\nCompShape centre: " << compShape.getCentre().x
          << ", " << compShape.getCentre().y << "\n";

      compShape.move({ 4, 5.8 });
      std::cout << "\nCompShape centre after moving: " << compShape.getCentre().x
          << ", " << compShape.getCentre().y << "\n";
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "Error: " << e.what();
      return 2;
    }

    std::cout << "\nScaled CompShape:\n";

    try
    {
      compShape.scale(1.5);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << "Error: " << e.what();
      return 2;
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "Error: " << e.what();
      return 1;
    }

    compShape.display();
    std::cout << "\nFunction getFrameRect for CompositeShape:\n";

    try
    {
      kharitonov::Rectangle newRect4(compShape.getFrameRect());
      newRect4.display();
    }
    catch (const std::out_of_range& e)
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

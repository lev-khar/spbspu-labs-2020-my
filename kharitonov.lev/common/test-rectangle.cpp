#define _USE_MATH_DEFINES
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(testRectangle)

const double EPSILON = 0.0001;
const double TEST_HEIGHT = 13.4;
const double TEST_WIDTH = 8.92;
const double TEST_FACT = 3.0;

const double TEST_ANGLE_90 = 90;
const double TEST_ANGLE = 20;

const kharitonov::point_t TEST_POS = {-1.2, 2.1};

BOOST_AUTO_TEST_CASE(rectCorrectData)
{
  kharitonov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
  BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getArea(), TEST_HEIGHT * TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectMovementStabilityPoint)
{
  kharitonov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
  const double CHECK_AREA = testRect.getArea();
  const kharitonov::point_t TEST_NEW_POINT = { 39.74, -45.088 };
  testRect.move(TEST_NEW_POINT);
  BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().x, TEST_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().y, TEST_NEW_POINT.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_NEW_POINT.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectMovementStabilityDisplacement)
{
  kharitonov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
  const double DX = 0.57, DY = 9.4, CHECK_AREA = testRect.getArea();
  testRect.move(DX, DY);
  BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().x, TEST_POS.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().y, TEST_POS.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectScalingSquare)
{
  kharitonov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
  const double CHECK_AREA = testRect.getArea();
  testRect.scale(TEST_FACT);
  BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA * TEST_FACT * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_HEIGHT * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_WIDTH * TEST_FACT, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectRotation90)
{
  kharitonov::Rectangle testRect({ TEST_WIDTH, TEST_HEIGHT, TEST_POS });
  const double CHECK_AREA = testRect.getArea();
  testRect.rotate(TEST_ANGLE_90);
  BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().height, TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().width, TEST_HEIGHT, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectRotation)
{
  kharitonov::Rectangle testRect({ TEST_WIDTH, TEST_HEIGHT, TEST_POS });
  const double CHECK_AREA = testRect.getArea();
  testRect.rotate(TEST_ANGLE);
  const double radAngle = TEST_ANGLE * M_PI / 180;
  const double rotatedWidth = TEST_WIDTH * std::sin(radAngle) + TEST_HEIGHT * std::cos(radAngle);
  const double rotatedHeight = TEST_HEIGHT * std::sin(radAngle) + TEST_WIDTH * std::cos(radAngle);
  BOOST_CHECK_CLOSE(testRect.getWidth(), TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getHeight(), TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getArea(), CHECK_AREA, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getCentre().y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().pos.y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().height, rotatedWidth, EPSILON);
  BOOST_CHECK_CLOSE(testRect.getFrameRect().width, rotatedHeight, EPSILON);
}

BOOST_AUTO_TEST_CASE(rectInvalidParameters)
{
   // + & 0
  BOOST_CHECK_THROW(kharitonov::Rectangle testRect({1.0, 0.0, TEST_POS}), std::invalid_argument);
  // - & 0
  BOOST_CHECK_THROW(kharitonov::Rectangle testRect({-34.5, 0.0, TEST_POS}), std::invalid_argument);
  // - & -
  BOOST_CHECK_THROW(kharitonov::Rectangle testRect({-34.5, -24.5, TEST_POS}), std::invalid_argument);
  // - & +
  BOOST_CHECK_THROW(kharitonov::Rectangle testRect({-34.5, 18, TEST_POS}), std::invalid_argument);
  // 0 & 0
  BOOST_CHECK_THROW(kharitonov::Rectangle testRect({0.0, 0.0, TEST_POS}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectInvalidFactor)
{
  kharitonov::Rectangle testRect({TEST_WIDTH, TEST_HEIGHT, TEST_POS});
  BOOST_CHECK_THROW(testRect.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(testRect.scale(-8.99), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

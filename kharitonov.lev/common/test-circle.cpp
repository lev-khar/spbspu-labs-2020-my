#define _USE_MATH_DEFINES
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(testCircle)

const double EPSILON = 0.0001;
const double TEST_RAD = 5.7;
const double TEST_FACT = 3.0;
const kharitonov::point_t TEST_POS = {-1.2, 2.1};

BOOST_AUTO_TEST_CASE(circleCorrectData)
{
  kharitonov::Circle testCircle(TEST_POS, TEST_RAD);
  BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getArea(), M_PI * TEST_RAD * TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, 2 * TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, 2 * TEST_RAD, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleMovementStabilityPoint)
{
  kharitonov::Circle testCircle(TEST_POS, TEST_RAD);
  const kharitonov::point_t TEST_NEW_POINT = { 39.74, -45.088 };
  const double CHECK_AREA = testCircle.getArea();
  testCircle.move(TEST_NEW_POINT);
  BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getArea(), CHECK_AREA, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_NEW_POINT.y, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().x, TEST_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().y, TEST_NEW_POINT.y, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, 2 * TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, 2 * TEST_RAD, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleMovementStabilityDisplacement)
{
  kharitonov::Circle testCircle(TEST_POS, TEST_RAD);
  const double DX = -77.9, DY = 0.34, CHECK_AREA = testCircle.getArea();
  testCircle.move(DX, DY);
  BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getArea(), CHECK_AREA, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_POS.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_POS.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().x, TEST_POS.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().y, TEST_POS.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, 2 * TEST_RAD, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, 2 * TEST_RAD, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleScalingSquare)
{
  kharitonov::Circle testCircle(TEST_POS, TEST_RAD);
  const double CHECK_AREA = testCircle.getArea();
  testCircle.scale(TEST_FACT);
  BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RAD * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getCentre().y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getArea(), CHECK_AREA * TEST_FACT * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.x, TEST_POS.x, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().pos.y, TEST_POS.y, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().height, TEST_FACT * TEST_RAD * 2, EPSILON);
  BOOST_CHECK_CLOSE(testCircle.getFrameRect().width, TEST_FACT * TEST_RAD * 2, EPSILON);
}

BOOST_AUTO_TEST_CASE(circleInvalidRadius)
{
  BOOST_CHECK_THROW(kharitonov::Circle testCircle(TEST_POS, 0.0), std::invalid_argument);
  BOOST_CHECK_THROW(kharitonov::Circle testCircle(TEST_POS, -34.5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(circleInvalidFactor)
{
  kharitonov::Circle testCircle(TEST_POS, TEST_RAD);
  BOOST_CHECK_THROW(testCircle.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(testCircle.scale(-8.99), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "partitioning-logic.hpp"
#include "matrix.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(testPartitioning)

const double EPSILON = 0.0001;
const int TEST_SIZE = 3;
const double TEST_RAD_0 = 5.7;
const kharitonov::point_t TEST_POS_CIRC_0 = { 15.9, 2.1 };
const double TEST_RAD_1 = 55.7;
const kharitonov::point_t TEST_POS_CIRC_1 = { 13.8, 5.4 };
const double TEST_HEIGHT_0 = 3.2;
const double TEST_WIDTH_0 = 2.7;
const kharitonov::point_t TEST_POS_RECT_0 = { -1.2, 4.6 };

struct fixture
{
  kharitonov::Shape::ShapePtr myCirclePtr0;
  kharitonov::Shape::ShapePtr myCirclePtr1;
  kharitonov::Shape::ShapePtr myRectanglePtr0;
  kharitonov::Shape::ArrayShapePtr shapes;

  fixture() :
    myCirclePtr0(std::make_shared<kharitonov::Circle>(
        kharitonov::Circle(TEST_POS_CIRC_0, TEST_RAD_0))),
    myCirclePtr1(std::make_shared<kharitonov::Circle>(
        kharitonov::Circle(TEST_POS_CIRC_1, TEST_RAD_1))),
    myRectanglePtr0(std::make_shared<kharitonov::Rectangle>(
        kharitonov::Rectangle({ TEST_WIDTH_0, TEST_HEIGHT_0, TEST_POS_RECT_0 })))
  {
    shapes = std::make_unique<kharitonov::Shape::ShapePtr[]>(TEST_SIZE);
    shapes[0] = myCirclePtr0;
    shapes[1] = myCirclePtr1;
    shapes[2] = myRectanglePtr0;
  }
};

BOOST_FIXTURE_TEST_CASE(partitionIntersect, fixture)
{
  BOOST_CHECK_EQUAL(kharitonov::checkIntersect(myCirclePtr0->getFrameRect(), myCirclePtr1->getFrameRect()), true);
  BOOST_CHECK_EQUAL(kharitonov::checkIntersect(myCirclePtr0->getFrameRect(), myRectanglePtr0->getFrameRect()), false);
}

BOOST_FIXTURE_TEST_CASE(partitionLogicCorrect, fixture)
{
  kharitonov::Matrix testMatrix = kharitonov::partition(shapes, TEST_SIZE);

  BOOST_CHECK_EQUAL(testMatrix.getLayersNumber(), 2);
  BOOST_CHECK_EQUAL(testMatrix[0][0], myCirclePtr0);
  BOOST_CHECK_EQUAL(testMatrix[0][1], myRectanglePtr0);
  BOOST_CHECK_EQUAL(testMatrix[1][0], myCirclePtr1);
  BOOST_CHECK_EQUAL(testMatrix[0].getLength(), 2);
  BOOST_CHECK_EQUAL(testMatrix[1].getLength(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

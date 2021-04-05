#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "partitioning-logic.hpp"
#include "matrix.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(testMatrix)

const double EPSILON = 0.0001;
const int TEST_ARR_SIZE = 3;
const int TEST_LAYERS_NUM = 2;
const int TEST_LAYER0_LEN = 2;
const int TEST_LAYER1_LEN = 1;
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
  kharitonov::Matrix matrix;

  fixture() :
    myCirclePtr0(std::make_shared<kharitonov::Circle>(
        kharitonov::Circle(TEST_POS_CIRC_0, TEST_RAD_0))),
    myCirclePtr1(std::make_shared<kharitonov::Circle>(
        kharitonov::Circle(TEST_POS_CIRC_1, TEST_RAD_1))),
    myRectanglePtr0(std::make_shared<kharitonov::Rectangle>(
        kharitonov::Rectangle({ TEST_WIDTH_0, TEST_HEIGHT_0, TEST_POS_RECT_0 })))
  {
    kharitonov::Shape::ArrayShapePtr shapes = std::make_unique<kharitonov::Shape::ShapePtr[]>(TEST_ARR_SIZE);
    shapes[0] = myCirclePtr0;
    shapes[1] = myRectanglePtr0;
    shapes[2] = myCirclePtr1;
    matrix = kharitonov::partition(shapes, TEST_ARR_SIZE);
  }
};

BOOST_FIXTURE_TEST_CASE(matrixEmptyConstructor, fixture)
{
  kharitonov::Matrix emptyMatrix;
  BOOST_CHECK_EQUAL(emptyMatrix.getLayersNumber(), 0);
  BOOST_CHECK_THROW(emptyMatrix[0], std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(matrixCopyConstructor, fixture)
{
  kharitonov::Matrix copiedMatrix(matrix);

  BOOST_CHECK_EQUAL(copiedMatrix.getLayersNumber(), TEST_LAYERS_NUM);
  BOOST_CHECK_EQUAL(copiedMatrix[0].getLength(), TEST_LAYER0_LEN);
  BOOST_CHECK_EQUAL(copiedMatrix[1].getLength(), TEST_LAYER1_LEN);
  BOOST_CHECK_EQUAL(copiedMatrix[0][0], matrix[0][0]);
  BOOST_CHECK_EQUAL(copiedMatrix[0][1], matrix[0][1]);
  BOOST_CHECK_EQUAL(copiedMatrix[1][0], matrix[1][0]);
}

BOOST_FIXTURE_TEST_CASE(matrixCopyOperator, fixture)
{
  kharitonov::Matrix copiedMatrix = matrix;

  BOOST_CHECK_EQUAL(copiedMatrix.getLayersNumber(), TEST_LAYERS_NUM);
  BOOST_CHECK_EQUAL(copiedMatrix[0].getLength(), TEST_LAYER0_LEN);
  BOOST_CHECK_EQUAL(copiedMatrix[1].getLength(), TEST_LAYER1_LEN);
  BOOST_CHECK_EQUAL(copiedMatrix[0][0], matrix[0][0]);
  BOOST_CHECK_EQUAL(copiedMatrix[0][1], matrix[0][1]);
  BOOST_CHECK_EQUAL(copiedMatrix[1][0], matrix[1][0]);
}

BOOST_FIXTURE_TEST_CASE(matrixMove, fixture)
{
  kharitonov::Matrix movedMatrix = std::move(matrix);

  BOOST_CHECK_EQUAL(movedMatrix.getLayersNumber(), TEST_LAYERS_NUM);
  BOOST_CHECK_EQUAL(movedMatrix[0].getLength(), TEST_LAYER0_LEN);
  BOOST_CHECK_EQUAL(movedMatrix[1].getLength(), TEST_LAYER1_LEN);
  BOOST_CHECK_EQUAL(movedMatrix[0][0], myCirclePtr0);
  BOOST_CHECK_EQUAL(movedMatrix[0][1], myRectanglePtr0);
  BOOST_CHECK_EQUAL(movedMatrix[1][0], myCirclePtr1);

  BOOST_CHECK_EQUAL(matrix.getLayersNumber(), 0);
  BOOST_CHECK_THROW(matrix[0], std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(matrixBracketsOperator, fixture)
{
  BOOST_CHECK_EQUAL(matrix[0][0], myCirclePtr0);
  BOOST_CHECK_EQUAL(matrix[0][1], myRectanglePtr0);
  BOOST_CHECK_EQUAL(matrix[1][0], myCirclePtr1);
}

BOOST_FIXTURE_TEST_CASE(matrixOutOfBoundsBracketsOperator, fixture)
{
  BOOST_CHECK_THROW(matrix[TEST_LAYERS_NUM + 1], std::out_of_range);
  BOOST_CHECK_THROW(matrix[0][TEST_LAYER0_LEN + 1], std::out_of_range);
}


BOOST_FIXTURE_TEST_CASE(matrixCorrectAddLayer, fixture)
{
  matrix.addLayer();
  BOOST_CHECK_EQUAL(matrix.getLayersNumber(), TEST_LAYERS_NUM + 1);
  BOOST_CHECK_EQUAL(matrix[0].getLength(), TEST_LAYER0_LEN);
  BOOST_CHECK_EQUAL(matrix[1].getLength(), TEST_LAYER1_LEN);
  BOOST_CHECK_EQUAL(matrix[0][0], myCirclePtr0);
  BOOST_CHECK_EQUAL(matrix[0][1], myRectanglePtr0);
  BOOST_CHECK_EQUAL(matrix[1][0], myCirclePtr1);
}

BOOST_FIXTURE_TEST_CASE(matrixOutOfBoundsAddLayer, fixture)
{
  matrix.addLayer();
  BOOST_CHECK_THROW(matrix[TEST_LAYERS_NUM + 2], std::out_of_range);
  BOOST_CHECK_THROW(matrix[0][TEST_LAYER0_LEN + 1], std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(matrixCorrectAddFigure, fixture)
{
  kharitonov::Shape::ShapePtr myRectanglePtr1 = std::make_shared<kharitonov::Rectangle>(
      kharitonov::Rectangle({ TEST_WIDTH_0 + 1, TEST_HEIGHT_0 + 1, TEST_POS_RECT_0 }));
  matrix[0].addShape(myRectanglePtr1);

  BOOST_CHECK_EQUAL(matrix.getLayersNumber(), TEST_LAYERS_NUM);
  BOOST_CHECK_EQUAL(matrix[0].getLength(), TEST_LAYER0_LEN + 1);
  BOOST_CHECK_EQUAL(matrix[1].getLength(), TEST_LAYER1_LEN);
  BOOST_CHECK_EQUAL(matrix[0][0], myCirclePtr0);
  BOOST_CHECK_EQUAL(matrix[0][1], myRectanglePtr0);
  BOOST_CHECK_EQUAL(matrix[0][2], myRectanglePtr1);
  BOOST_CHECK_EQUAL(matrix[1][0], myCirclePtr1);
}

BOOST_AUTO_TEST_SUITE_END()

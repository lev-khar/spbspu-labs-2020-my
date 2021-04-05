#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "partitioning-logic.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(testCompShape)

const double EPSILON = 0.0001;
const int TEST_SIZE = 2;
const double TEST_RAD = 5.7;
const double TEST_RAD_2 = 55.7;
const double TEST_HEIGHT = 13.2;
const double TEST_WIDTH = 2.7;
const double TEST_FACT = 3.0;
const double TEST_SMALL_FACT = 0.5;
const double TEST_ANGLE_90 = 90;
const double TEST_ANGLE = 45;
const kharitonov::point_t TEST_POS_CIRC_2 = { 13.8, 5.4 };
const kharitonov::point_t TEST_POS_CIRC = { 15.9, 2.1 };
const kharitonov::point_t TEST_POS_RECT = { -1.2, 4.6 };

const double TEST_HEIGHT_COMP = 14.8;
const double TEST_WIDTH_COMP = 24.15;
const kharitonov::point_t TEST_POS_COMP = { 9.525, 3.8 };
const kharitonov::point_t TEST_POS_NEW_POINT = { 1.3, 2.5 };

struct fixture
{
  kharitonov::Shape::ShapePtr myCirclePtr;
  kharitonov::Shape::ShapePtr myRectanglePtr;
  kharitonov::CompositeShape compShape;

  fixture():
    myCirclePtr(std::make_shared<kharitonov::Circle>(
        kharitonov::Circle(TEST_POS_CIRC, TEST_RAD))),
    myRectanglePtr(std::make_shared<kharitonov::Rectangle>(
        kharitonov::Rectangle({TEST_WIDTH, TEST_HEIGHT, TEST_POS_RECT})))
  {
    compShape.append(myCirclePtr);
    compShape.append(myRectanglePtr);
  }
};

//Checking consturctors and operators
BOOST_FIXTURE_TEST_CASE(compShapeEmptyConstructor, fixture)
{
  kharitonov::CompositeShape emptyCompShape;
  BOOST_CHECK_EQUAL(emptyCompShape.getSize(), 0);
  BOOST_CHECK_EQUAL(emptyCompShape.getArea(), 0.0);
  BOOST_CHECK_THROW(emptyCompShape.getFrameRect(), std::logic_error);
  BOOST_CHECK_THROW(emptyCompShape.getCentre(), std::logic_error);
  BOOST_CHECK_THROW(emptyCompShape.move({ 0, 0 }), std::logic_error);
  BOOST_CHECK_THROW(emptyCompShape.rotate(10), std::logic_error);
  BOOST_CHECK_THROW(emptyCompShape.remove(0), std::out_of_range);
  BOOST_CHECK_THROW(emptyCompShape[0], std::out_of_range);
  BOOST_CHECK_THROW(emptyCompShape.scale(TEST_FACT), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(compShapeCopyConstructor, fixture)
{
  kharitonov::CompositeShape copiedCompShape(compShape);

  BOOST_CHECK_EQUAL(copiedCompShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(copiedCompShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().height, TEST_HEIGHT_COMP, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().width, TEST_WIDTH_COMP, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().pos.x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().pos.y, TEST_POS_COMP.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeCopyOperator, fixture)
{
  kharitonov::CompositeShape copiedCompShape = compShape;

  BOOST_CHECK_EQUAL(copiedCompShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(copiedCompShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().height, TEST_HEIGHT_COMP, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().width, TEST_WIDTH_COMP, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().pos.x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(copiedCompShape.getFrameRect().pos.y, TEST_POS_COMP.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeMove, fixture)
{
  kharitonov::CompositeShape movedCompShape = std::move(compShape);

  BOOST_CHECK_EQUAL(movedCompShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(movedCompShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(movedCompShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(movedCompShape.getFrameRect().height, TEST_HEIGHT_COMP, EPSILON);
  BOOST_CHECK_CLOSE(movedCompShape.getFrameRect().width, TEST_WIDTH_COMP, EPSILON);
  BOOST_CHECK_CLOSE(movedCompShape.getFrameRect().pos.x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(movedCompShape.getFrameRect().pos.y, TEST_POS_COMP.y, EPSILON);

  BOOST_CHECK_EQUAL(compShape.getSize(), 0);
  BOOST_CHECK_EQUAL(compShape.getArea(), 0.0);
  BOOST_CHECK_THROW(compShape.getFrameRect(), std::logic_error);
  BOOST_CHECK_THROW(compShape.getCentre(), std::logic_error);
  BOOST_CHECK_THROW(compShape.move({ 0, 0 }), std::logic_error);
  BOOST_CHECK_THROW(compShape.rotate(10), std::logic_error);
  BOOST_CHECK_THROW(compShape.remove(0), std::out_of_range);
  BOOST_CHECK_THROW(compShape[0], std::out_of_range);
  BOOST_CHECK_THROW(compShape.scale(TEST_FACT), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(compShapeBracketsOperator, fixture)
{
  BOOST_CHECK_THROW(compShape[TEST_SIZE + 1], std::out_of_range);
  BOOST_CHECK_EQUAL(compShape[0], myCirclePtr);
  BOOST_CHECK_EQUAL(compShape[1], myRectanglePtr);
}

//Check getters
BOOST_FIXTURE_TEST_CASE(compShapeCorrectGetters, fixture)
{
  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, TEST_HEIGHT_COMP, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, TEST_WIDTH_COMP, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, TEST_POS_COMP.y, EPSILON);
  const double calculatedArea = myCirclePtr->getArea() + myRectanglePtr->getArea();
  BOOST_CHECK_CLOSE(compShape.getArea(), calculatedArea, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapePartitionLogicCorrect, fixture)
{
  kharitonov::Shape::ShapePtr myCirclePtr2 = std::make_shared<kharitonov::Circle>(
    kharitonov::Circle(TEST_POS_CIRC_2, TEST_RAD_2));

  compShape.append(myCirclePtr2);

  kharitonov::Matrix testMatrix = compShape.getPartition();

  BOOST_CHECK_EQUAL(testMatrix.getLayersNumber(), 2);
  BOOST_CHECK_EQUAL(testMatrix[0][0], myCirclePtr);
  BOOST_CHECK_EQUAL(testMatrix[0][1], myRectanglePtr);
  BOOST_CHECK_EQUAL(testMatrix[1][0], myCirclePtr2);
  BOOST_CHECK_EQUAL(testMatrix[0].getLength(), 2);
  BOOST_CHECK_EQUAL(testMatrix[1].getLength(), 1);
}

//Checking move(), scale() and rotate()
BOOST_FIXTURE_TEST_CASE(compShapeMovementStabilityPoint, fixture)
{
  const double originalArea = compShape.getArea();
  const double originalFrameHeight = compShape.getFrameRect().height;
  const double originalFrameWidth = compShape.getFrameRect().width;

  compShape.move(TEST_POS_NEW_POINT);

  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().x, TEST_POS_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().y, TEST_POS_NEW_POINT.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, TEST_POS_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, TEST_POS_NEW_POINT.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeMovementDisplacement, fixture)
{
  const double originalArea = compShape.getArea();
  const double originalFrameHeight = compShape.getFrameRect().height;
  const double originalFrameWidth = compShape.getFrameRect().width;
  const double originalPosX = compShape.getCentre().x;
  const double originalPosY = compShape.getCentre().y;
  const double originalFramePosX = compShape.getFrameRect().pos.x;
  const double originalFramePosY = compShape.getFrameRect().pos.y;

  compShape.move(TEST_POS_NEW_POINT.x, TEST_POS_NEW_POINT.y);

  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().x, originalPosX + TEST_POS_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().y, originalPosY + TEST_POS_NEW_POINT.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, originalFramePosX + TEST_POS_NEW_POINT.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, originalFramePosY + TEST_POS_NEW_POINT.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeBigScalingBehaviourCorrect, fixture)
{
  const double originalArea = compShape.getArea();
  const double originalFrameHeight = compShape.getFrameRect().height;
  const double originalFrameWidth = compShape.getFrameRect().width;
  const double originalFramePosX = compShape.getFrameRect().pos.x;
  const double originalFramePosY = compShape.getFrameRect().pos.y;

  const kharitonov::point_t modifiedCirclePos = { TEST_POS_COMP.x + TEST_FACT * (TEST_POS_CIRC.x - TEST_POS_COMP.x),
      TEST_POS_COMP.y + TEST_FACT * (TEST_POS_CIRC.y - TEST_POS_COMP.y) };
  const kharitonov::point_t modifiedRectanglePos = { TEST_POS_COMP.x + TEST_FACT * (TEST_POS_RECT.x - TEST_POS_COMP.x),
      TEST_POS_COMP.y + TEST_FACT * (TEST_POS_RECT.y - TEST_POS_COMP.y) };

  compShape.scale(TEST_FACT);

  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea * TEST_FACT * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth * TEST_FACT, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, originalFramePosX, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, originalFramePosY, EPSILON);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.x, modifiedCirclePos.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.y, modifiedCirclePos.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.x, modifiedRectanglePos.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.y, modifiedRectanglePos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeSmallScalingBehaviourCorrect, fixture)
{
  const double originalArea = compShape.getArea();
  const double originalFrameHeight = compShape.getFrameRect().height;
  const double originalFrameWidth = compShape.getFrameRect().width;
  const double originalFramePosX = compShape.getFrameRect().pos.x;
  const double originalFramePosY = compShape.getFrameRect().pos.y;

  const kharitonov::point_t modifiedCirclePos = { TEST_POS_COMP.x + TEST_SMALL_FACT * (TEST_POS_CIRC.x - TEST_POS_COMP.x),
      TEST_POS_COMP.y + TEST_SMALL_FACT * (TEST_POS_CIRC.y - TEST_POS_COMP.y) };
  const kharitonov::point_t modifiedRectanglePos = { TEST_POS_COMP.x + TEST_SMALL_FACT * (TEST_POS_RECT.x - TEST_POS_COMP.x),
      TEST_POS_COMP.y + TEST_SMALL_FACT * (TEST_POS_RECT.y - TEST_POS_COMP.y) };

  compShape.scale(TEST_SMALL_FACT);

  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea * TEST_SMALL_FACT * TEST_SMALL_FACT, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, originalFrameHeight * TEST_SMALL_FACT, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, originalFrameWidth * TEST_SMALL_FACT, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, originalFramePosX, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, originalFramePosY, EPSILON);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.x, modifiedCirclePos.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape[0]->getFrameRect().pos.y, modifiedCirclePos.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.x, modifiedRectanglePos.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape[1]->getFrameRect().pos.y, modifiedRectanglePos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeScalingBehaviourBad, fixture)
{
  BOOST_CHECK_THROW(compShape.scale(0), std::logic_error);
  BOOST_CHECK_THROW(compShape.scale(-1), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(compShapeRotation90, fixture)
{
  const double originalArea = compShape.getArea();
  compShape.rotate(TEST_ANGLE_90);

  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape.getCentre().x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getCentre().y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, TEST_WIDTH_COMP, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, TEST_HEIGHT_COMP, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, TEST_POS_COMP.x, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, TEST_POS_COMP.y, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeRotation, fixture)
{
  const double originalArea = compShape.getArea();
  const kharitonov::point_t originalCentre = compShape.getCentre();
  double radAngle = std::fmod(TEST_ANGLE,180);
  if (radAngle <= 0)
  {
    radAngle += 180;
  }
  radAngle = radAngle * M_PI / 180;
  const double rotatedCircCentreX = originalCentre.x + (TEST_POS_CIRC.x - originalCentre.x) * std::cos(radAngle) 
      - (TEST_POS_CIRC.y - originalCentre.y) * std::sin(radAngle);
  const double rotatedCircCentreY = originalCentre.y + (TEST_POS_CIRC.x - originalCentre.x) * std::sin(radAngle)
      + (TEST_POS_CIRC.y - originalCentre.y) * std::cos(radAngle);
  const double rotatedRectCentreX = originalCentre.x + (TEST_POS_RECT.x - originalCentre.x) * std::cos(radAngle)
      - (TEST_POS_RECT.y - originalCentre.y) * std::sin(radAngle);
  const double rotatedRectCentreY = originalCentre.y + (TEST_POS_RECT.x - originalCentre.x) * std::sin(radAngle)
      + (TEST_POS_RECT.y - originalCentre.y) * std::cos(radAngle);

  compShape.rotate(TEST_ANGLE);

  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  BOOST_CHECK_CLOSE(compShape[0]->getCentre().x, rotatedCircCentreX, EPSILON);
  BOOST_CHECK_CLOSE(compShape[0]->getCentre().y, rotatedCircCentreY, EPSILON);
  BOOST_CHECK_CLOSE(compShape[1]->getCentre().x, rotatedRectCentreX, EPSILON);
  BOOST_CHECK_CLOSE(compShape[1]->getCentre().y, rotatedRectCentreY, EPSILON);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea, EPSILON);
}

//Checking append() and remove()
BOOST_FIXTURE_TEST_CASE(compShapeAppendCorrect, fixture)
{
  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  double originalArea = compShape.getArea();
  const kharitonov::Circle checkCircle(TEST_POS_CIRC, TEST_RAD + 10);
  double addedArea = checkCircle.getArea();
  compShape.append(std::make_shared<kharitonov::Circle>(checkCircle));
  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE + 1);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea + addedArea, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeAppendBad, fixture)
{
  BOOST_CHECK_THROW(compShape.append(nullptr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(compShapeRemoveCorrect, fixture)
{
  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE);
  double originalArea = compShape.getArea();
  double removedArea = compShape[TEST_SIZE - 1]->getArea();
  compShape.remove(TEST_SIZE - 1);
  BOOST_CHECK_EQUAL(compShape.getSize(), TEST_SIZE - 1);
  BOOST_CHECK_CLOSE(compShape.getArea(), originalArea - removedArea, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(compShapeRemoveBad, fixture)
{
  BOOST_CHECK_THROW(compShape.remove(TEST_SIZE + 1), std::out_of_range);
  BOOST_CHECK_THROW(compShape.remove(-1), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

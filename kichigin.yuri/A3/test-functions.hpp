#ifndef TEST_FUNCTIONS
#define TEST_FUNCTIONS

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const int AMOUNT_OF_TESTS = 16;

bool areRectangleParametersConstantAfterMove();//Number 1
bool areCircleParametersConstantAfterMove();//Number 2
bool isRectangleAreaChangedSquaredAfrerScale();//Number 3
bool isCircleAreaChangedSquaredAfrerScale();//Number 4
bool doesRectangleConstructorWorkCorrectWithUncorrectParameters();//Number 5
bool doesRectangleSetWidthWorkCorrectWithUncorrectParameters();//Number 6
bool doesRectangleSetHeighthWorkCorrectWithUncorrectParameters();//Number 7
bool doesRectangleScalehWorkCorrectWithUncorrectParameters();//Number 8
bool doesCircleConstructorWorkCorrectWithUncorrectParameters();//Number 9
bool doesCircleSetRadiusWorkCorrectWithUncorrectParameters();//Number 10
bool doesCircleScaleWorkCorrectWithUncorrectParameters();//Number 11
bool doesCompositeShapeAddShapeWorkCorrectWithUncorrectParameters();//Number 12
bool doesCompositeShapeDeleteShapeWorkCorrectWithUncorrectParameters();//Number 13
bool doesCompositeShapeOperatorIndexWorkCorrectWithUncorrectParameters();//Number 14
bool areCompositeShapeParametersConstantAfterMove();//Number 15
bool isCompositeShapeAreaChangedSquaredAfrerScale();//Number 16

#endif//!TEST_FUNCTIONS

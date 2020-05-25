#include <iostream>
#include "test-functions.hpp"

typedef bool (*functuon)();

int main()
{
  functuon testArray[AMOUNT_OF_TESTS];
  testArray[0] = areRectangleParametersConstantAfterMove;
  testArray[1] = areCircleParametersConstantAfterMove;
  testArray[2] = isRectangleAreaChangedSquaredAfrerScale;
  testArray[3] = isCircleAreaChangedSquaredAfrerScale;
  testArray[4] = doesRectangleConstructorWorkCorrectWithUncorrectParameters;
  testArray[5] = doesRectangleSetWidthWorkCorrectWithUncorrectParameters;
  testArray[6] = doesRectangleSetHeighthWorkCorrectWithUncorrectParameters;
  testArray[7] = doesRectangleScalehWorkCorrectWithUncorrectParameters;
  testArray[8] = doesCircleConstructorWorkCorrectWithUncorrectParameters;
  testArray[9] = doesCircleSetRadiusWorkCorrectWithUncorrectParameters;
  testArray[10] = doesCircleScaleWorkCorrectWithUncorrectParameters;
  bool isCorrect = false;
  int controlValue = 0;
  for (int i = 0; i < AMOUNT_OF_TESTS; i++)
  {
    isCorrect = testArray[i]();
    if (controlValue == 0 && !isCorrect)
    {
      controlValue = 1;
    }
    std::cout << "Test number " << i + 1 << ": " << (isCorrect ? "Correct\n" : "Urcorrect\n");
  }
  return controlValue;
}

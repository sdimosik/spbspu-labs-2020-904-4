#include <iostream>
#include "test-functions.hpp"

typedef bool (*functuon)();

int main()
{
  functuon testArray[AMOUNT_OF_TESTS];
  testArray[0] = doesRectangleRotateWorksCorrect;
  testArray[1] = doesCircleRotateWorksCorrect;
  testArray[2] = doesCompositeShapeRotateWorksCorrect;
  testArray[3] = doesMatrixGetShapeWorkCorrectWithUncorrectParameters;
  testArray[4] = doesMatrixGetLayerCurrentSizeWorkCorrectWithUncorrectParameters;
  bool isCorrect = false;
  int controlValue = 0;
  for (int i = 0; i < AMOUNT_OF_TESTS; i++)
  {
    isCorrect = testArray[i]();
    if (controlValue == 0 && !isCorrect)
    {
      controlValue = 1;
    }
    std::cout << "Test number " << i + 1 << ": " << (isCorrect ? "Correct\n" : "Uncorrect\n");
  }
  return controlValue;
}

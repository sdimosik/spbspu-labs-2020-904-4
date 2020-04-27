#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void printData(const Shape& sh)
{
  std::cout << "Area:" << sh.getArea();
  rectangle_t rct = sh.getFrameRect();
  std::cout << "\nCoordinate x: " << rct.pos.x << "\nCoordinate y: " << rct.pos.y;
  std::cout << "\nHeight: " << rct.height << "\nWidth: " << rct.width << "\n\n";
}

int main()
{
  std::cout << "RECTANGLE:\n";
  Rectangle rect1({ 2,3 }, 10, 20);
  printData(rect1);
  std::cout << "After moving:\n";
  rect1.move(2.6, 5.3);
  printData(rect1);
  std::cout << "After moving to particular point:\n";
  rect1.move({ 13, 15 });
  printData(rect1);
  std::cout << "Second rectangle:\n";
  Rectangle rect2({ 2, 3 }, 10, 20);
  printData(rect2);
  std::cout << "After moving:\n";
  rect2.move(2.6, 5.3);
  printData(rect2);
  std::cout << "After moving to particular point:\n";
  rect2.move({ 13, 15 });
  printData(rect2);
  std::cout << "\nCIRCLE:\n";
  Circle circ1({ 1, 6 }, 5.6);
  printData(circ1);
  std::cout << "After moving:\n";
  rect1.move(6.7, 2.4);
  printData(circ1);
  std::cout << "After moving to particular point:\n";
  rect1.move({ 10, 15 });
  printData(circ1);
  std::cout << "Second circle:\n";
  Circle circ2({ 2.6, 9.5 }, 4.5);
  printData(circ2);
  std::cout << "After moving:\n";
  circ2.move(2.6, 5.3);
  printData(circ2);
  std::cout << "After moving to particular point:\n";
  circ2.move({ 13, 15 });
  printData(circ2);
  return 0;
}

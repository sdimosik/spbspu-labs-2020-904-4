#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try
  {
    point_t pos1{ 0,0 };
    point_t pos2{ 7.25, -0.125 };
    point_t pos3{ -25, 10 };
    point_t pos4{ -6.3, -4.5 };
    Circle circle(1, pos1);
    Rectangle rectangle(3, 0.75, pos2);
    Shape* figure1 = &circle;
    Shape* figure2 = &rectangle;
    double area1 = figure1->getArea();
    double area2 = figure2->getArea();
    std::cout << "Areas of figures:" << "\nfigure1: " << area1 << "\nfigure2: " << area2 << "\n";
    std::cout << "Center of figure1: x=" << figure1->getCenter().x << " y=" << figure1->getCenter().y << "\n";
    figure1->move(pos3);
    std::cout << "Center of figure1: x=" << figure1->getCenter().x << " y=" << figure1->getCenter().y << "\n";
    figure1->move(-75, 15);
    std::cout << "Center of figure1: x=" << figure1->getCenter().x << " y=" << figure1->getCenter().y
        << "\nCenter of figure2: x=" << figure2->getCenter().x << " y=" << figure2->getCenter().y << "\n";
    figure2->move(pos4);
    std::cout << "Center of figure2: " << "x=" << figure2->getCenter().x << " y=" << figure2->getCenter().y << "\n";
    figure2->move(10, -50);
    std::cout << "Center of figure2: " << "x=" << figure2->getCenter().x << " y=" << figure2->getCenter().y
        << "\nFrame rectangle of figure1(circle)\nHeight: " << figure1->getFrameRect().height
        << "\nWidth: " << figure1->getFrameRect().width << "\nFrame rectangle of figure2(rectangle)\nHeight: " 
        << figure2->getFrameRect().height << "\nWidth: " << figure2->getFrameRect().width << std::endl;
  }
  catch (const std::invalid_argument& ex)
  {
    std::cout << ex.what() << std::endl;
    return 1;
  }
  return 0;
}

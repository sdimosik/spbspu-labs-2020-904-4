#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    khilchenko::point_t pos1{ 0, 0 };
    khilchenko::point_t pos2{ 7.25, -0.125 };
    khilchenko::point_t pos3{ -25, 10 };
    khilchenko::point_t pos4{ -6.3, -4.5 };
    khilchenko::Circle circle(1, pos1);
    khilchenko::Rectangle rectangle(3, 0.75, pos2);
    khilchenko::Shape *figure1 = &circle;
    khilchenko::Shape *figure2 = &rectangle;
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
        << "\nFrame rectangle of figure1(circle) before scaling\nHeight: " << figure1->getFrameRect().height << "\nWidth: "
        << figure1->getFrameRect().width << "\nFrame rectangle of figure2(rectangle) before scaling\nHeight: "
        << figure2->getFrameRect().height << "\nWidth: " << figure2->getFrameRect().width;
    figure1->scale(2);
    figure2->scale(2);
    std::cout << "\nFrame rectangle of figure1(circle) after scaling\nHeight: " << figure1->getFrameRect().height << "\nWidth: "
        << figure1->getFrameRect().width << "\nFrame rectangle of figure2(rectangle) after scaling\nHeight: "
        << figure2->getFrameRect().height << "\nWidth: " << figure2->getFrameRect().width << "\nAreas of figures after scalling:"
        << "\nCircle: " << figure1->getArea() << "\nRectangle: " << figure2->getArea() << std::endl;
    figure1->move({0,0});
    figure2->move({5,5});
    std::shared_ptr<khilchenko::Shape> compositeCircle = std::make_shared<khilchenko::Circle>(circle);
    std::shared_ptr<khilchenko::Shape> compositeRectangle = std::make_shared<khilchenko::Rectangle>(rectangle);
    khilchenko::CompositeShape compositeShape(2);
    compositeShape.addShape(compositeCircle);
    compositeShape.addShape(compositeRectangle);
    compositeShape.scale(2.0);
    std::cout << "Area of the first element of compositeShape: " << compositeShape[0]->getArea() << "\n"
        << "Area of the second element of compositeShape: " << compositeShape[1]->getArea()
        <<"\nTotal area of all shapes(area of composite shape): " << compositeShape.getArea()
        << "\nCenter of the frame rectangle\nx: " << compositeShape.getCenter().x
        << "\ny: " << compositeShape.getCenter().y << "\nWidth of frame rectangle: " << compositeShape.getFrameRect().width
        << "\nHeight of frame rectangle: " << compositeShape.getFrameRect().height
        << "\nArray size: " << compositeShape.getSize()
        << "\nAmount of shapes: " << compositeShape.getAmount() << "\n";
  }
  catch (const std::exception &ex)
  {
    std::cout << ex.what() << std::endl;
    return 2;
  }
  return 0;
}

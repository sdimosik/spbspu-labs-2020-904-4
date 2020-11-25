#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  try
  {
    std::cout << "Circle test:" << std::endl;
    starikevich::point_t point1{ 3.0, 4.0 };
    starikevich::Circle circle(point1, 6.4);
    std::cout << "Circle coordinates = (" << circle.getPosition().x
      << ", " << circle.getPosition().y << ")" << std::endl 
      << "Circle radius = " << circle.getRadius() << std::endl
      << "Circle area = " << circle.getArea() << std::endl;
    circle.move(13.7, -21.9);
    std::cout << "The coordinates of the circle after moving 13.7 along the x axis and -21.9 along the y axis = ("
      << circle.getPosition().x << ", " << circle.getPosition().y << ")" << std::endl;
    starikevich::point_t point2{ -25.4, 63.1 };
    circle.move(point2);
    std::cout << "The coordinates of the circle after moving to the point (-25.4, 63.1) = ("
      << circle.getPosition().x << ", " << circle.getPosition().y << ")" << std::endl
      << "Rectangle test:";
    starikevich::Rectangle rect(point1, 12.9, 7.7);
    std::cout << "Rectangle coordinates = (" << rect.getPosition().x
      << ", " << rect.getPosition().y << ")" << std::endl 
      << "Rectangle width = " << rect.getWidth() << std::endl
      << "Rectangle height = " << rect.getHeight() << std::endl
      << "Rectangle area = " << rect.getArea() << std::endl;
    rect.move(25.5, 46.6);
    std::cout << "The coordinates of the rectangle after moving 25.5 along the x axis and 46.6 along the y axis = ("
      << rect.getPosition().x << ", " << rect.getPosition().y << ")" << std::endl;
    rect.move(point2);
    std::cout << "The coordinates of the rectangle after moving to the point (-25.4, 63.1) = ("
      << rect.getPosition().x << ", " << rect.getPosition().y << ")" << std::endl
      << "Triangle test: " << std::endl;
    starikevich::point_t peak1{ 3.0, 4.0 };
    starikevich::point_t peak2{ 0.0, 4.0 };
    starikevich::point_t peak3{ 3.0, 0.0 };
    starikevich::Triangle triangle(peak1, peak2, peak3);
    std::cout << "Triangle coordinates = (" << triangle.getPosition().x
      << ", " << triangle.getPosition().y << ")" << std::endl
      << "Triangle 1 side = " << triangle.getSide1() << std::endl
      << "Triangle 2 side = " << triangle.getSide2() << std::endl
      << "Triangle 3 side = " << triangle.getSide3() << std::endl
      << "Triangle area = " << triangle.getArea() << std::endl;
    triangle.move(25.5, 46.6);
    std::cout << "The coordinates of the triangle after moving 25.5 along the x axis and 46.6 along the y axis = ("
      << triangle.getPosition().x << ", " << triangle.getPosition().y << ")" << std::endl;
    triangle.move(point2);
    std::cout << "The coordinates of the triangle after moving to the point (-25.4, 63.1) = ("
      << triangle.getPosition().x << ", " << triangle.getPosition().y << ")" << std::endl
      << "Polymorphism test: " << std::endl;
    starikevich::Shape* shape = &circle;
    std::cout << "The shape pointer now refers to the circle" << std::endl
      << "Circle area = " << shape->getArea() << std::endl;
    shape = &rect;
    std::cout << "The shape pointer now refers to the rectangle" << std::endl
      << "Rectangle area = " << shape->getArea() << std::endl;
    shape = &triangle;
    std::cout << "The shape pointer now refers to the triangle" << std::endl
      << "Triangle area = " << shape->getArea() << std::endl 
      << "Scale test:" << std::endl
      << "Coefficient = 12.3" << std::endl;
    circle.scale(12.3);
    std::cout << "Circle coordinates = (" << circle.getPosition().x
      << ", " << circle.getPosition().y << ")" << std::endl
      << "Circle radius = " << circle.getRadius() << std::endl
      << "Circle area = " << circle.getArea() << std::endl;
    rect.scale(12.3);
    std::cout << "Rectangle coordinates = (" << rect.getPosition().x
      << ", " << rect.getPosition().y << ")" << std::endl
      << "Rectangle width = " << rect.getWidth() << std::endl
      << "Rectangle height = " << rect.getHeight() << std::endl
      << "Rectangle area = " << rect.getArea() << std::endl;
    triangle.scale(12.3);
    std::cout << "Triangle coordinates = (" << triangle.getPosition().x
      << ", " << triangle.getPosition().y << ")" << std::endl
      << "Triangle 1 side = " << triangle.getSide1() << std::endl
      << "Triangle 2 side = " << triangle.getSide2() << std::endl
      << "Triangle 3 side = " << triangle.getSide3() << std::endl
      << "Triangle area = " << triangle.getArea() << std::endl;

  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << "Error: " << error.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown problem" << std::endl;
    return 2;
  }
  return 0;
}

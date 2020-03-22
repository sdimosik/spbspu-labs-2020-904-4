#include<iostream>
#include"circle.hpp"
#include"rectangle.hpp"

int main()
{
  try
  {
    meynik::point_t point1{ 2.0, 3.0 };
    meynik::point_t point2{ 1.2, 2.1 };
    meynik::point_t mover{ 1.5, 2.9 };
    double scale1 = 2.0;
    double scale2 = 3.0;
    meynik::Shape* shape1 = new meynik::Rectangle(point1, 4.0, 9.0);
    std::cout << "Shape pointer initialised by rectangle object:" << std::endl
      << "Rectangle before moving:" << std::endl;
    shape1->printInfo(std::cout);
    shape1->move(mover);
    std::cout << "Rectangle after moving:" << std::endl;
    shape1->printInfo(std::cout);
    std::cout << "Rectangle area: " << shape1->getArea() << std::endl;
    shape1->move(-mover.x, -mover.y);
    std::cout << "Rectangle moved to center of coordinates plane:"<< std::endl; 
    shape1->printInfo(std::cout);
    std::cout << "Rectangle area: " << shape1->getArea() << std::endl;
    shape1->scale(scale1);
    std::cout << "Rectangle after scaling by " << scale1 << ":" << std::endl;
    shape1->printInfo(std::cout);
    std::cout << "Rectangle area: " << shape1->getArea() << std::endl<<std::endl;
    delete shape1;
    meynik::Rectangle rect(point1, 4.0, 9.0);
    std::cout << "Object of rectangle class:" << std::endl
      << "Rectangle before moving:" << std::endl;
    rect.printInfo(std::cout);
    rect.move(mover);
    std::cout << "Rectangle after moving:" << std::endl;
    rect.printInfo(std::cout);
    std::cout << "Rectangle area: " << rect.getArea() << std::endl;
    rect.move(-mover.x, -mover.y);
    std::cout << "Rectangle moved to center of coordinates plane:" << std::endl;
    std::cout << "Rectangle area: " << rect.getArea() << std::endl;
    rect.printInfo(std::cout);
    rect.scale(scale1);
    std::cout << "Rectangle after scaling by " << scale1 << ":" << std::endl;
    rect.printInfo(std::cout);
    std::cout << "Rectangle area: " << rect.getArea() << std::endl << std::endl;
    meynik::Shape* shape2 = new meynik::Circle(point2, 2.281336);
    std::cout << "Shape pointer initialised by circle object:" << std::endl
      << "Circle before moving:" << std::endl;
    shape2->printInfo(std::cout);
    shape2->move(mover);
    std::cout << "Circle after moving:" << std::endl;
    shape2->printInfo(std::cout);
    std::cout << "Circle area: " << shape2->getArea() << std::endl;
    shape2->move(-mover.x, -mover.y);
    std::cout << "Circle moved to center of coordinates plane:" << std::endl;
    shape2->printInfo(std::cout);
    std::cout << "Circle area: " << shape2->getArea() << std::endl;
    shape2->scale(scale2);
    std::cout << "Circle after scaling by " << scale2 << ":" << std::endl;
    shape2->printInfo(std::cout);
    std::cout << "Circle area: " << shape2->getArea() << std::endl << std::endl;
    delete shape2;
    meynik::Circle circ(point2, 2.281336);
    std::cout << "Object of circle class:" << std::endl
      << "Circle before moving:" << std::endl;
    circ.printInfo(std::cout);
    circ.move(mover);
    std::cout << "Circle after moving:" << std::endl;
    circ.printInfo(std::cout);
    std::cout << "Circle area: " << circ.getArea() << std::endl;
    circ.move(-mover.x, -mover.y);
    std::cout << "Circle moved to center of coordinates plane:" << std::endl;
    circ.printInfo(std::cout);
    std::cout << "Circle area: " << circ.getArea() << std::endl;
    circ.scale(scale2);
    std::cout << "Circle after scaling by " << scale2 << ":" << std::endl;
    circ.printInfo(std::cout);
    std::cout << "Circle area: " << circ.getArea() << std::endl << std::endl;
  }
  catch (const std::invalid_argument & exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error:Unknown problem" << std::endl;
    return -1;
  }
  return 0;
}

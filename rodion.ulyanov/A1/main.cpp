#include <iostream>
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
int main()
{
 try
  {
    point_t defaultPos;
    point_t newPos;
    point_t point_A,point_B,point_C;
    defaultPos.x = 2;
    defaultPos.y = 2;
    newPos.x = 4;
    newPos.y = 5;
    point_A.x = 10;
    point_A.y = -10;
    point_B.x = 14;
    point_B.y = 28;
    point_C.x = 2;
    point_C.y = -2;
    rectangle_t defaultRectangle {10,10,defaultPos};
    Rectangle rectangle (defaultRectangle);
    Shape *shape = &rectangle;
    std::cout << "Rectangle's area is: " << shape->getArea() << std::endl;
    shape->move(newPos);
    shape->show();
    std::cout << shape->getFrameRect().height << " " << shape->getFrameRect().width << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y <<std::endl;
    shape->move(12, -2);
    shape->show();
    Circle circle (14, defaultPos);
    shape = &circle;
    std::cout << "Circle's area is: " << shape->getArea() << std::endl;
    shape->show();
    shape->move(newPos);
    std::cout << shape->getFrameRect().height << " " << shape->getFrameRect().width << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y << std::endl;
    shape->move(20, -20);
    shape->show();
    Triangle triangle(point_A,point_B,point_C);
    shape = &triangle;
    std::cout << "Triangle's area is: " << shape->getArea() << std::endl;
    shape->show();
    shape->move(newPos);
    std::cout << shape->getFrameRect().height << " " << shape->getFrameRect().width << " " << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y << std::endl;
    shape->move (40, 10);
    shape->show();
    std::cout << std::endl;
  }
    
  catch (const std::invalid_argument & exc)
  {
    std::cerr << exc.what() << std::endl;
    return 1;
  }
  catch (...)
  {
        std::cerr << "Unknown exception" << '\n';
  }
  return 0;
}

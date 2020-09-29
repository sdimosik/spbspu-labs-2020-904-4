#include <iostream>
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
int main()
{
 try
 {
   rodion::point_t defaultPos;
   rodion::point_t newPos;
   rodion::point_t point_A,point_B,point_C;
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
   rodion::rectangle_t defaultRectangle {10,10,defaultPos};
   rodion::Rectangle rectangle (defaultRectangle);
   rodion::Shape *shape = &rectangle;
   std::cout << "Rectangle testing" << std::endl;
   std::cout << "Rectangle's area is: " << shape->getArea() << std::endl;
   shape->move(newPos);
   shape->show();
   std::cout << shape->getFrameRect().height << " " << shape->getFrameRect().width << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y <<std::endl;
   shape->move(12, -2);
   shape->show();
   shape->scale(2.0);
   std::cout << "Rectangle's area after scale: " << shape->getArea();
   std::cout << "Rectangle's frame after scale: " << shape->getFrameRect().height << " " << shape->getFrameRect().width << " " << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y << std::endl;


   rodion::Circle circle (14, defaultPos);
   shape = &circle;
   std::cout << "Circle test" << std::endl;
   std::cout << "Circle's area is: " << shape->getArea() << std::endl;
   shape->show();
   shape->move(newPos);
   std::cout << shape->getFrameRect().height << " " << shape->getFrameRect().width << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y << std::endl;
   shape->move(20, -20);
   shape->show();
   shape->scale(1.5);
   std::cout << "Circle's area after scale is: " << shape->getArea() << std::endl;
   rodion::Triangle triangle(point_A,point_B,point_C);
   shape = &triangle;
   std::cout << "Triangle test" << std::endl;
   std::cout << "Triangle's area is: " << shape->getArea() << std::endl;
   shape->show();
   shape->move(newPos);
   std::cout << shape->getFrameRect().height << " " << shape->getFrameRect().width << " " << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y << std::endl;
   shape->move (40, 10);
   shape->show();
   shape->scale(0.8);
   std::cout << "Triangle's area after scale: " << shape->getArea() << std::endl;
   std::cout << "Triangle's frame after scale: " << shape->getFrameRect().height << " " << shape->getFrameRect().width << " " << shape->getFrameRect().pos.x << " " << shape->getFrameRect().pos.y << std::endl;
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


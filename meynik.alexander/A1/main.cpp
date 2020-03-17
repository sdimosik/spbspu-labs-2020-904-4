#include<iostream>
#include"circle.hpp"
#include"rectangle.hpp"

int main()
{
    try
    {
        point_t mover{ 1.5,2.9 };
        Shape* shape1 = new Rectangle(point_t{ 2.0, 3.0 }, 4.0, 9.0);
        std::cout << "Shape pointer initialised by rectangle object:" << std::endl;
                  << "Rectangle before moving:" << std::endl;
        shape1->printInfo(std::cout);
        shape1->move(mover);
        std::cout << "Rectangle after moving:" << std::endl;
        shape1->printInfo(std::cout);
        shape1->move(-mover.x, -mover.y);
        std::cout << "Rectangle returned to it's initial position:" << std::endl;
        shape1->printInfo(std::cout);
        std::cout << "Rectangle area: " << shape1->getArea() << std::endl << std::endl;
        delete shape1;
        Rectangle rect(point_t{ 2.0, 3.0 }, 4.0, 9.0);
        std::cout << "Object of rectangle class:" << std::endl;
                  << "Rectangle before moving:" << std::endl;
        rect.printInfo(std::cout);
        rect.move(mover);
        std::cout << "Rectangle after moving:" << std::endl;
        rect.printInfo(std::cout);
        rect.move(-mover.x, -mover.y);
        std::cout << "Rectangle returned to it's initial position:" << std::endl;
        rect.printInfo(std::cout);
        std::cout << "Rectangle area: " << rect.getArea() << std::endl << std::endl;
        Shape* shape2 = new Circle(point_t{ 1.2, 2.1 }, 2.281336);
        std::cout << "Shape pointer initialised by circle object" << std::endl;
                  << "Circle before moving:" << std::endl;
        shape2->printInfo(std::cout);
        shape2->move(mover);
        std::cout << "Circle after moving:" << std::endl;
        shape2->printInfo(std::cout);
        shape2->move(-mover.x, -mover.y);
        std::cout << "Circle returned to it's initial position:"  std::endl;
        shape2->printInfo(std::cout);
        std::cout << "Circle area: " << shape2->getArea() << std::endl << std::endl;
        delete shape2;
        Circle circ(point_t{ 1.2, 2.1 }, 2.281336);
        std::cout << "Object of circle class:" << std::endl;
                  << "Circle before moving:" << std::endl;
        circ.printInfo(std::cout);
        circ.move(mover);
        std::cout << "Circle after moving:" << std::endl;
        circ.printInfo(std::cout);
        circ.move(-mover.x, -mover.y);
        std::cout << "Circle returned to it's initial position:" << std::endl;
        circ.printInfo(std::cout);
        std::cout << "Circle area: " << circ.getArea() << std::endl;
    }
    catch (const std::invalid_argument&arg)
    {
        std::cerr << arg.what << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Error:Unknown problem" << std::endl;
        return -1;
    }
    return 0;
}

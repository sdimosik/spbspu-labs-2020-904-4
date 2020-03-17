#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main() {
	try
	{
		point_t mover{ 1.5,2.9 };
		Shape* shape1 = new Rectangle(point_t{ 2.0, 3.0 }, 4.0, 9.0);
		std::cout << "Shape pointer initialised by rectangle object:\n";
		std::cout << "Rectangle before moving:\n";
		shape1->printInfo(std::cout);
		shape1->move(mover);
		std::cout << "Rectangle after moving:\n";
		shape1->printInfo(std::cout);
		shape1->move(-mover.x, -mover.y);
		std::cout << "Rectangle returned to it's initial position:\n";
		shape1->printInfo(std::cout);
		std::cout << "Rectangle area: " << shape1->getArea() << std::endl << std::endl;
		delete shape1;
		Rectangle rect(point_t{ 2.0, 3.0 }, 4.0, 9.0);
		std::cout << "Object of rectangle class:\n";
		std::cout << "Rectangle before moving:\n";
		rect.printInfo(std::cout);
		rect.move(mover);
		std::cout << "Rectangle after moving:\n";
		rect.printInfo(std::cout);
		rect.move(-mover.x, -mover.y);
		std::cout << "Rectangle returned to it's initial position:\n";
		rect.printInfo(std::cout);
		std::cout << "Rectangle area: " << rect.getArea() << std::endl << std::endl;
		Shape* shape2 = new Circle(point_t{ 1.2, 2.1 }, 2.281336);
		std::cout << "Shape pointer initialised by circle object\n";
		std::cout << "Circle before moving:\n";
		shape2->printInfo(std::cout);
		shape2->move(mover);
		std::cout << "Circle after moving:\n";
		shape2->printInfo(std::cout);
		shape2->move(-mover.x, -mover.y);
		std::cout << "Circle returned to it's initial position:\n";
		shape2->printInfo(std::cout);
		std::cout << "Circle area: " << shape2->getArea() << std::endl << std::endl;
		delete shape2;
		Circle circ(point_t{ 1.2, 2.1 }, 2.281336);
		std::cout << "Object of circle class:\n";
		std::cout << "Circle before moving:\n";
		circ.printInfo(std::cout);
		circ.move(mover);
		std::cout << "Circle after moving:\n";
		circ.printInfo(std::cout);
		circ.move(-mover.x, -mover.y);
		std::cout << "Circle returned to it's initial position:\n";
		circ.printInfo(std::cout);
		std::cout << "Circle area: " << circ.getArea() << std::endl;
	}
	catch (std::invalid_argument & invarg)
	{
		std::cerr << invarg.what() << '\n';
		return -1;
	}
	catch (...)
	{
		std::cerr << "Undefined error\n";
		return -1;
	}
	return 0;
}
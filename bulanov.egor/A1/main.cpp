#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main() {
  try {
    std::cout << "1 circle test" << std::endl;

    Circle circle1(5.11, point_t{1.1, 2.1});
    Shape *shape1 = &circle1;

    std::cout << "First position:  " << '(' << shape1->getCenter().x << ", "
        << shape1->getCenter().y << ')' << std::endl;
    shape1->move(11.2, 12.3);
    std::cout << "Second position:  " << '(' << shape1->getCenter().x << ", "
        << shape1->getCenter().y << ')' << std::endl;
    shape1->move(-10.2, -9.3);
    shape1->printInform();
    shape1->move(point_t{7.2, 1.3});
    shape1->printInform();
    std::cout << shape1->getArea() << std::endl;
    shape1->printFrameInform();

    std::cout << "2 rectangle test" << std::endl;

    Rectangle rectangle(point_t{3.2, 2.1}, 3, 7);
    Shape *shape2 = &rectangle;

    std::cout << "First position:  " << '(' << shape2->getCenter().x << ", "
        << shape2->getCenter().y << ')' << std::endl;
    shape2->move(2.2, 10.3);
    std::cout << "Second position:  " << '(' << shape2->getCenter().x << ", "
        << shape2->getCenter().y << ')' << std::endl;
    shape2->move(-5.2, -3.3);
    shape2->printInform();
    shape2->move(point_t{2.2, 3.3});
    shape2->printInform();
    std::cout << shape2->getArea() << std::endl;
    shape2->printFrameInform();
  }
  catch (const std::invalid_argument &message){
    std::cerr << "Attention: " << message.what() << std::endl;
    return -1;
  }
  catch (...) {
    std::cerr << "Unknown error";
    return -1;
  }
  return 0;
}

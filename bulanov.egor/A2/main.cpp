#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main() {
  try {
    std::cout << "1 circle test \n" ;

    bulanov::Circle circle1(5.11, bulanov::point_t{1.1, 2.1});
    bulanov::Shape *shape1 = &circle1;

    std::cout << "First position:  " << '(' << shape1->getCenter().x << ", "
        << shape1->getCenter().y << ") \n";
    shape1->move(11.2, 12.3);
    std::cout << "Second position:  " << '(' << shape1->getCenter().x << ", "
        << shape1->getCenter().y << ") \n";
    shape1->move(-10.2, -9.3);
    shape1->printInform();
    shape1->move(bulanov::point_t{7.2, 1.3});
    shape1->printInform();
    std::cout << "Circle area: " << shape1->getArea() << '\n';
    shape1->printFrameInform();
    std::cout << "After scaling with rate 5.2:  \n" ;
    shape1->scale(5.2);
    shape1->printInform();
    std::cout << "Circle area: " << shape1->getArea() << '\n';


    std::cout << "2  rectangle test \n" ;

    bulanov::Rectangle rectangle(bulanov::point_t{3.2, 2.1}, 3, 7);
    bulanov::Shape *shape2 = &rectangle;

    std::cout << "First position:  " << '(' << shape2->getCenter().x << ", "
        << shape2->getCenter().y << ") \n";
    shape2->move(2.2, 10.3);
    std::cout << "Second position:  " << '(' << shape2->getCenter().x << ", "
        << shape2->getCenter().y << ") \n";
    shape2->move(-5.2, -3.3);
    shape2->printInform();
    shape2->move(bulanov::point_t{2.2, 3.3});
    shape2->printInform();
    std::cout << "Rectangle area: " << shape2->getArea() << '\n';
    shape2->printFrameInform();
    std::cout << "After scaling with rate 1.7:  \n";
    shape2->scale(1.7);
    shape2->printInform();
    std::cout << "Rectangle area: " << shape2->getArea() << '\n';
  }
  catch (const std::invalid_argument &message){
    std::cerr << "Attention: " << message.what() << '\n';
    return 1;
  }
  catch (...) {
    std::cerr << "Unknown error";
    return 2;
  }
  return 0;
}

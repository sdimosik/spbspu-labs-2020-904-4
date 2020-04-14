#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try {
    Rectangle rec(2, 3, {1, 1});
    Rectangle rec0(13, 53, {2, 3});
    Circle circ(3, {6, 6});
    Shape *rec1 = &rec;
    std::cout << "Info about Rectangle1:\n";
    rec1->getFrameRect().print();
    std::cout << "Area = " << rec1->getArea() << "\n\n";
    Shape *rec2 = &rec0;
    point_t position = {15, 15};
    std::cout << "Info about Rectangle2:\n";
    rec2->move(position);
    rec2->move(1, 0);
    rec2->print();
    std::cout << "Area = " << rec2->getArea() << "\n\n";
    Shape *circ1 = &circ;
    std::cout << "Info about Circle1:\n";
    circ1->print();
    point_t position0 = {25, 13};
    circ1->move(position0);
    circ1->move(1, 2);
    std::cout << "\nAfter the shift\n";
    circ1->print();
    std::cout << "Area = " << circ1->getArea() << "\n";
  }
  catch(const std::exception &exc)
  {
    std::cerr <<  exc.what() << '\n';
    return 1;
  }
  return 0;
}

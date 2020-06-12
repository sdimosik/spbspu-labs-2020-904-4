#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    maksimova::Rectangle rec(2, 3, {1, 1});
    maksimova::Rectangle rec0(13, 53, {2, 3});
    maksimova::Circle circ(3, {6, 6});
    maksimova::Shape *rec1 = &rec;
    std::cout << "Info about Rectangle1:\n";
    rec1->getFrameRect().print();
    std::cout << "Area = " << rec1->getArea() << "\n\n";
    maksimova::Shape *rec2 = &rec0;
    maksimova::point_t position{15, 15};
    std::cout << "Info about Rectangle2:\n";
    rec2->move(position);
    rec2->move(1, 0);
    rec2->print();
    std::cout << "Area = " << rec2->getArea() << "\n\n";
    maksimova::Shape *circ1 = &circ;
    std::cout << "Info about Circle1:\n";
    circ1->print();
    maksimova::point_t position0{25, 13};
    circ1->move(position0);
    circ1->move(1, 2);
    std::cout << "\nAfter the shift\n";
    circ1->print();
    std::cout << "Area = " << circ1->getArea() << "\n";
    std::shared_ptr<maksimova::Shape> shape1 = std::make_shared<maksimova::Rectangle>(rec);
    std::shared_ptr<maksimova::Shape> shape2 = std::make_shared<maksimova::Circle>(circ);
    std::shared_ptr<maksimova::Shape> shape3 = std::make_shared<maksimova::Rectangle>(rec0);
    maksimova::CompositeShape shapes(3);
    shapes.addShape(shape1);
    shapes.addShape(shape2);
    shapes.addShape(shape3);
    std::cout << "Composite shape after adding three shapes: ";
    shapes.print();
    shapes.scale(2);
    std::cout << "Composite shape after amplification in two times: ";
    shapes.print();
    std::cout << "Composite shape after moving: ";
    shapes.move({2.5, 12.4});
    shapes.print();
    maksimova::CompositeShape shapes2 = shapes;
    std::cout << "Second composite shape equal to the first: ";
    shapes2.print();
  }
  catch(const std::exception &exc)
  {
    std::cerr <<  exc.what() << '\n';
    return 1;
  }
  return 0;
}

#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"

int main()
{
  try
  {
    std::cout << "-------Rectangle test-------\n";
    shabinsky::Rectangle rectangle(shabinsky::point_t{228, 1337}, 6, 9);
    std::cout << "width: " << rectangle.getWidth() << "\nheight: " << rectangle.getHeight() << "\nposition: ( "
       << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << "\narea: " << rectangle.getArea() << "\n";
    double x1 = 123, y1 = 321;
    std::cout << "-------moving to ( " << x1 << " ; " << y1 << " )-------\ncurrent: ( " << rectangle.getPosition().x
        << " ; " << rectangle.getPosition().y << " )    destination: ( " << x1 << " ; " << y1 << " )\nmoving...\n";
    rectangle.move({x1, y1});
    std::cout << "current: ( " << rectangle.getPosition().x
        << " ; " << rectangle.getPosition().y << " )    destination: ( " << x1 << " ; " << y1 << "\n"
        << "-------moving " << x1 << " by x and" << y1 << " by y-------\n" << "current: ( "
        << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )    " << "destination: ( "
        << rectangle.getPosition().x + x1 << " ; " << rectangle.getPosition().y + y1 << " )\n" << "mooving...\n";
    rectangle.move(rectangle.getPosition().x + x1, rectangle.getPosition().y + y1);
    std::cout << "current: ( " << rectangle.getPosition().x << " ; " << rectangle.getPosition().y << " )    "
        << "destination: ( " << rectangle.getPosition().x + x1 << " ; " << rectangle.getPosition().y + y1
        << " )\n" << "-------Circle test-------\n";
    shabinsky::Circle circle(6, {3, 4});
    std::cout << "radius: " << circle.getRadius() << '\n' << "position: ( " << circle.getPosition().x << " ; "
        << circle.getPosition().y << " )\n" << "area: " << circle.getArea() << '\n';
    x1 = 111;
    y1 = 222;
    std::cout << "-------moving to ( " << x1 << " ; " << y1 << " )-------\n" << "current: ( "
        << circle.getPosition().x << " ; " << circle.getPosition().y << " )    " << "destination: ( " << x1
        << " ; " << y1 << " )\n" << "mooving...\n";
    circle.move({x1, y1});
    std::cout << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )    "
        << "destination: ( " << x1 << " ; " << y1 << " )\n" << "-------moving " << x1 << " by x and" << y1
        << " by y-------\n" << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y
        << " )    " << "destination: ( " << circle.getPosition().x + x1 << " ; "
        << circle.getPosition().y + y1 << " )\n" << "mooving...\n";
    circle.move(circle.getPosition().x + x1, circle.getPosition().y + y1);
    std::cout << "current: ( " << circle.getPosition().x << " ; " << circle.getPosition().y << " )    "
        << "destination: ( " << circle.getPosition().x + x1 << " ; " << circle.getPosition().y + y1 << " )\n"
        << "-------Polymorphism test-------\n";
    shabinsky::Shape *shape = new shabinsky::Circle(6, {3, 4});
    shape->show(std::cout);
    delete shape;
    shape = new shabinsky::Rectangle(shabinsky::point_t{228, 1337}, 6, 9);
    shape->show(std::cout);
    delete shape;
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << "Error: invalid data\n" << err.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error:Unknown problem" << std::endl;
    return 2;
  }
  
  return 0;
}

#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "composite-shape.hpp"

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

    shabinsky::Circle circle10(2, shabinsky::point_t{10, 10});
    shabinsky::Circle circle20(2, shabinsky::point_t{-10, -10});
    shabinsky::Rectangle rectangle10(shabinsky::point_t{10, -10}, 2, 2);
    shabinsky::Rectangle rectangle20(shabinsky::point_t{-10, 10}, 2, 2);
    
    shabinsky::CompositeShape array(4);
    std::shared_ptr<shabinsky::Shape> shape1 = std::make_shared<shabinsky::Circle>(circle10);
    std::shared_ptr<shabinsky::Shape> shape2 = std::make_shared<shabinsky::Circle>(circle20);
    std::shared_ptr<shabinsky::Shape> shape3 = std::make_shared<shabinsky::Rectangle>(rectangle10);
    std::shared_ptr<shabinsky::Shape> shape4 = std::make_shared<shabinsky::Rectangle>(rectangle20);
    array.addShape(shape1);
    array.addShape(shape2);
    array.addShape(shape3);
    array.addShape(shape4);
    std::cout << "\nStarting position of shapes:\n";
    array.show(std::cout);
    std::cout << "\nThe frame rectangle of shapes:\n";
    std::cout << array.getFrameRect();
    array.move(shabinsky::point_t{0, 0});
    array.scale(2.0);
    std::cout << "\nNew position of shapes:\n";
    array.show(std::cout);
    array.deleteShape(2);
    std::cout << "\nPosition of shapes after removing shape 2:\n";
    array.show(std::cout);
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


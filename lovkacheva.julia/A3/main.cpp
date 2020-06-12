#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  lovkacheva::Shape *shapes[] = {new lovkacheva::Circle(25.5, lovkacheva::point_t{1.05, 23.7}),
      new lovkacheva::Rectangle(lovkacheva::rectangle_t{30.0, 10.67, lovkacheva::point_t{12.3, 10.0}})};
  for (lovkacheva::Shape *shape : shapes)
  {
    std::cout << "The shape: ";
    shape->print(std::cout);
    const lovkacheva::rectangle_t frameRectangle = shape->getFrameRect();
    std::cout << "\nIts frame rectangle:  width = " << frameRectangle.width << "; height = "
        << frameRectangle.height << "; pos(" << frameRectangle.pos.x << ", " << frameRectangle.pos.y << ")\n";
    std::cout << "Its area: " << shape->getArea() << '\n';
    const double dx = 10.0;
    const double dy = -34.3;
    shape->move(dx, dy);
    std::cout << "The shape, moved along the vector {" << dx << ", " << dy << "}: ";
    shape->print(std::cout);
    std::cout << '\n';
    const lovkacheva::point_t destination = {-4.0, 17.5};
    shape->move(destination);
    std::cout << "The shape, moved to the point (" << destination.x << ", " << destination.y << "): ";
    shape->print(std::cout);
    std::cout << "\nThe shape, scaled using the coefficient 2.5: ";
    shape->scale(2.5);
    shape->print(std::cout);
    std::cout << "\nIts area: " << shape->getArea();
    std::cout << "\n\n";
    delete shape;
  }
  lovkacheva::CompositeShape compositeShape1;
  std::cout << "The composite shape: \n";
  compositeShape1.print(std::cout);
  std::cout << "\n\n";
  std::shared_ptr<lovkacheva::Shape> circleComponent
      = std::make_shared<lovkacheva::Circle>(3.1, lovkacheva::point_t{1, 2});
  std::shared_ptr<lovkacheva::Shape> rectangleComponent
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{12.6, 6.2, {23, 1}});
  compositeShape1.addShape(circleComponent);
  compositeShape1.addShape(rectangleComponent);
  std::cout << "The composite shape after adding components: \n";
  compositeShape1.print(std::cout);
  std::cout << "\n\n";
  const lovkacheva::rectangle_t frameRectangle = compositeShape1.getFrameRect();
  std::cout << "\nIts frame rectangle:  width = " << frameRectangle.width << "; height = "
      << frameRectangle.height << "; pos(" << frameRectangle.pos.x << ", " << frameRectangle.pos.y << ")\n\n";
  std::cout << "The components' areas: \n[0]: " << circleComponent->getArea()
      << "\n[1]: " << rectangleComponent->getArea() << '\n';
  std::cout << "The composite shape's area: " << compositeShape1.getArea() << "\n\n";
  const double dx = 10.0;
  const double dy = -34.3;
  compositeShape1.move(dx, dy);
  std::cout << "The composite shape, moved along the vector {" << dx << ", " << dy << "}: \n";
  compositeShape1.print(std::cout);
  std::cout << "\n\n";
  const lovkacheva::point_t destination = {-4.0, 17.5};
  compositeShape1.move(destination);
  std::cout << "The composite shape, moved to the point (" << destination.x << ", " << destination.y << "): \n";
  compositeShape1.print(std::cout);
  std::cout << "\n\n";
  std::cout << "The composite shape, scaled using the coefficient 2.5: \n";
  compositeShape1.scale(2.5);
  compositeShape1.print(std::cout);
  std::cout << "\n\n";
  lovkacheva::CompositeShape compositeShape2 = compositeShape1;
  std::cout << "A copy of the composite shape:\n";
  compositeShape2.print(std::cout);
  std::cout << "\n\n";
  return 0;
}

#include <memory>
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    std::cout << "Circle: \n";
    meshcheryakov::point_t point = { 6.0, 6.0 };
    meshcheryakov::Circle circle(5.0, point);
    meshcheryakov::Shape* shape = &circle;
    std::cout << "Circle area: " << shape->getArea() << '\n';

    meshcheryakov::rectangle_t frame_cir = shape->getFrameRect();
    std::cout << "bounding box: \n" << frame_cir.height << " " << frame_cir.width << " " << frame_cir.pos.x << " "
        << frame_cir.pos.y << '\n';

    shape->move({ 5.0, 5.0 });
    frame_cir = shape->getFrameRect();
    std::cout << "Circle center: " << frame_cir.pos.x << " " << frame_cir.pos.y << '\n';
    shape->move(2.0, 1.0);

    frame_cir = shape->getFrameRect();
    std::cout << "Circle center: " << frame_cir.pos.x << " " << frame_cir.pos.y << '\n';

    shape->scale(5.0);
    std::cout << "Circle after scaling: \n" << "Radius: " << circle.getRadius() << '\n' << "Center: "
        << circle.getPosition().x << " " << circle.getPosition().y << '\n';


    std::cout << "Rectangle: \n";
    point = { 5.0, 5.0 };
    meshcheryakov::Rectangle rectangle({ 5.0, 5.0, point });
    shape = &rectangle;
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    meshcheryakov::rectangle_t frame_rec = shape->getFrameRect();
    std::cout << "bounding box: \n" << frame_rec.height << " " << frame_rec.width << " " << frame_rec.pos.x << " "
        << frame_rec.pos.y << '\n';

    shape->move({ 1.0, 1.0 });
    frame_rec = shape->getFrameRect();
    std::cout << "Rectangle center: " << frame_rec.pos.x << " " << frame_rec.pos.y << '\n';

    shape->move(2.0, 1.0);
    frame_rec = shape->getFrameRect();
    std::cout << "Rectangle center: " << frame_rec.pos.x << " " << frame_rec.pos.y << '\n';

    shape->scale(5.0);
    std::cout << "Rectangle after scaling: \n" << "Width: " << rectangle.getWidth() << '\n' << "Height: "
        << rectangle.getHeight() << '\n' << "Center: " << rectangle.getPosition().x << " " << rectangle.getPosition().y << '\n';

    std::cout << "Composite shape: \n";
    meshcheryakov::Circle circle2 (5.0, {5.0, 5.0});
    meshcheryakov::Rectangle rectangle2 ({6.0, 5.0, {5.0, 5.0}});
    meshcheryakov::CompositeShape compositeShape(2);
    std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Rectangle>(rectangle2);
    std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Circle>(circle2);
    compositeShape.addShape(shape1);
    compositeShape.addShape(shape2);
    std::cout << "Area of compositeShape: \n" << compositeShape.getArea() << '\n';
    compositeShape.scale(3.0);
    std::cout << "Area of compositeShape: \n" << compositeShape.getArea() << '\n' << "Width of frame: \n"
        << compositeShape.getFrameRect().width << '\n' << "Height of frame: \n" << compositeShape.getFrameRect().height << '\n'
        << "X center coordinate: \n" << compositeShape.getPosition().x << '\n' << "Y center coordinate: \n"
        << compositeShape.getPosition().y << '\n';
  }
  catch (const std::invalid_argument & exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem \n";
    return 2;
  }
  return 0;
}

#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

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
        << rectangle.getHeight() << '\n' << "Center: " << rectangle.getPosition().x << " " << rectangle.getPosition().y
        << '\n';
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

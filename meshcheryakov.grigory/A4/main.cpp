#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    std::cout << "Circle: \n";
    meshcheryakov::point_t point = {6.0, 6.0};
    meshcheryakov::Circle circle(5.0, point);
    meshcheryakov::Shape *shape = &circle;
    std::cout << "Circle area: " << shape->getArea() << '\n';

    meshcheryakov::rectangle_t frame_cir = shape->getFrameRect();
    std::cout << "bounding box: \n" << frame_cir.height << " " << frame_cir.width << " " << frame_cir.pos.x << " "
              << frame_cir.pos.y << '\n';

    shape->move({5.0, 5.0});
    frame_cir = shape->getFrameRect();
    std::cout << "Circle center: " << frame_cir.pos.x << " " << frame_cir.pos.y << '\n';
    shape->move(2.0, 1.0);

    frame_cir = shape->getFrameRect();
    std::cout << "Circle center: " << frame_cir.pos.x << " " << frame_cir.pos.y << '\n';

    shape->scale(5.0);
    std::cout << "Circle after scaling: \n" << "Radius: " << circle.getRadius() << '\n' << "Center: "
              << circle.getPosition().x << " " << circle.getPosition().y << '\n';


    std::cout << "Rectangle: \n";
    point = {5.0, 5.0};
    meshcheryakov::Rectangle rectangle({5.0, 5.0, point});
    shape = &rectangle;
    std::cout << "Rectangle area: " << shape->getArea() << '\n';

    meshcheryakov::rectangle_t frame_rec = shape->getFrameRect();
    std::cout << "bounding box: \n" << frame_rec.height << " " << frame_rec.width << " " << frame_rec.pos.x << " "
              << frame_rec.pos.y << '\n';

    shape->move({1.0, 1.0});
    frame_rec = shape->getFrameRect();
    std::cout << "Rectangle center: " << frame_rec.pos.x << " " << frame_rec.pos.y << '\n';

    shape->move(2.0, 1.0);
    frame_rec = shape->getFrameRect();
    std::cout << "Rectangle center: " << frame_rec.pos.x << " " << frame_rec.pos.y << '\n';

    shape->scale(5.0);
    std::cout << "Rectangle after scaling: \n" << "Width: " << rectangle.getWidth() << '\n' << "Height: "
              << rectangle.getHeight() << '\n' << "Center: " << rectangle.getPosition().x << " "
              << rectangle.getPosition().y << '\n';

    std::cout << "Composite shape: \n";
    meshcheryakov::Circle circle2(5.0, {5.0, 5.0});
    meshcheryakov::Rectangle rectangle2({6.0, 5.0, {5.0, 5.0}});
    meshcheryakov::CompositeShape compositeShape(2);
    std::shared_ptr<meshcheryakov::Shape> shape1 = std::make_shared<meshcheryakov::Rectangle>(rectangle2);
    std::shared_ptr<meshcheryakov::Shape> shape2 = std::make_shared<meshcheryakov::Circle>(circle2);
    compositeShape.addShape(shape1);
    compositeShape.addShape(shape2);
    std::cout << "Area of compositeShape: \n" << compositeShape.getArea() << '\n';
    compositeShape.scale(3.0);
    std::cout << "Area of compositeShape: \n" << compositeShape.getArea() << '\n' << "Width of frame: \n"
              << compositeShape.getFrameRect().width << '\n' << "Height of frame: \n"
              << compositeShape.getFrameRect().height << '\n'
              << "X center coordinate: \n" << compositeShape.getPosition().x << '\n' << "Y center coordinate: \n"
              << compositeShape.getPosition().y << '\n';

    std::cout << "Matrix:\n";
    meshcheryakov::Matrix matrix;
    meshcheryakov::Circle circle3(3.0, {5.0, 5.0});
    std::shared_ptr<meshcheryakov::Shape> shape3 = std::make_shared<meshcheryakov::Circle>(circle3);
    matrix.addShape(shape3);

    meshcheryakov::Rectangle rectangle3({5.0, 5.0, {15.0, 15.0}});
    std::shared_ptr<meshcheryakov::Shape> shape4 = std::make_shared<meshcheryakov::Rectangle>(rectangle3);
    matrix.addShape(shape4);

    std::shared_ptr<meshcheryakov::Shape> shape5 = std::make_shared<meshcheryakov::CompositeShape>(compositeShape);
    matrix.addShape(shape5);

    meshcheryakov::Circle circle4(1.0, {20.0,2.0});
    std::shared_ptr<meshcheryakov::Shape> shape6 = std::make_shared<meshcheryakov::Circle>(circle4);
    matrix.addShape(shape6);

    meshcheryakov::Rectangle rectangle4({6.0, 6.0, {0.0, 0.0}});
    std::shared_ptr<meshcheryakov::Shape> shape7 = std::make_shared<meshcheryakov::Rectangle>(rectangle4);
    matrix.addShape(shape7);

    std::cout << "Areas of shape [0][0]:\n" << (matrix[0][0])->getArea() << "\nAreas of shape [0][1]:\n" << (matrix[0][1])->getArea()
        << "\nAreas of shape [0][2]:\n" << (matrix[0][2])->getArea() << "\nAreas of shape [1][0]:\n" << (matrix[1][0])->getArea()
        << "\nAreas of shape [2][0]:\n" << (matrix[2][0])->getArea() << '\n';

  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return -1;
  }
  return 0;
}

#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main() {
  try {
    vorotnikov::Shape *shape;
    std::cout << "Circle test: \n";
    vorotnikov::point_t point = { 5.0, 5.0 };
    vorotnikov::Circle circle(5.0, point);
    shape = &circle;
    std::cout << "Circle area: " << shape->getArea() << '\n';
    vorotnikov::rectangle_t circle_frame = shape->getFrameRect();
    std::cout << "Circle frame: \n" << "height: " << circle_frame.height << " width: "
        << circle_frame.width << " center (X,Y): " << circle_frame.pos.x << ", " << circle_frame.pos.y << '\n';
    shape->scale(2.0);
    std::cout << "Circle area after scale: " << shape->getArea() << '\n';
    circle_frame = shape->getFrameRect();
    std::cout << "Circle frame after scale: \n" << "height: " << circle_frame.height << " width: "
        << circle_frame.width << " center (X,Y): " << circle_frame.pos.x << ", " << circle_frame.pos.y << '\n';
    vorotnikov::point_t move_point = { 5.6, 10.0};
    shape->move(move_point);
    circle_frame = shape->getFrameRect();
    std::cout << "Circle center after point movement (X,Y): " << circle_frame.pos.x << ", " << circle_frame.pos.y << '\n';
    shape->move(2.0, 1.0);
    circle_frame = shape->getFrameRect();
    std::cout << "Circle center after vector movement (X,Y): " << circle_frame.pos.x << ", " << circle_frame.pos.y << '\n';
    std::cout << "\nRectangle test: \n";
    point = { 20.0, 20.0 };
    vorotnikov::Rectangle rectangle(10.0, 10.0, point);
    shape = &rectangle;
    std::cout << "Rectangle area: " << shape->getArea() << '\n';
    vorotnikov::rectangle_t rectangle_frame = shape->getFrameRect();
    std::cout << "Rectangle frame: \n" << "height: " << rectangle_frame.height << " width: "
        << rectangle_frame.width << " center (X,Y): " << rectangle_frame.pos.x << ", " << rectangle_frame.pos.y << '\n';
    shape->scale(2.0);
    std::cout << "Rectangle area after move: " << shape->getArea() << '\n';
    rectangle_frame = shape->getFrameRect();
    std::cout << "Rectangle frame after move: \n" << "height: " << rectangle_frame.height << " width: "
              << rectangle_frame.width << " center (X,Y): " << rectangle_frame.pos.x << ", " << rectangle_frame.pos.y << '\n';
    shape->move({ 1.0, 1.0 });
    rectangle_frame = shape->getFrameRect();
    std::cout << "Rectangle center after point movement (X,Y): " << rectangle_frame.pos.x << ", " << rectangle_frame.pos.y << '\n';
    shape->move(2.0, 1.0);
    rectangle_frame = shape->getFrameRect();
    std::cout << "Rectangle center after vector movement (X,Y): " << rectangle_frame.pos.x << ", " << rectangle_frame.pos.y << '\n';
    std::cout << "\nTriangle test: \n";
    vorotnikov::point_t point1 = { 5.0, 3.0 };
    vorotnikov::point_t point2 = { 13.0, 3.0 };
    vorotnikov::point_t point3 = { 9.0, 9.0 };
    vorotnikov::Triangle triangle (point1, point2, point3);
    shape = &triangle;
    std::cout << "Triangle area: " << shape->getArea() << '\n';
    vorotnikov::rectangle_t triangle_frame = shape->getFrameRect();
    std::cout << "Triangle frame: \n" << "height: " << triangle_frame.height << " width: "
        << triangle_frame.width << " center (X,Y): " << triangle_frame.pos.x << ", " << triangle_frame.pos.y << '\n';
    std::cout << "Triangle center (X,Y): " << triangle.getCenterX() << ", " << triangle.getCenterY() << '\n';
    shape->scale(2.0);
    std::cout << "Triangle area after scale: " << shape->getArea() << '\n';
    triangle_frame = shape->getFrameRect();
    std::cout << "Triangle frame after scale: \n" << "height: " << triangle_frame.height << " width: "
        << triangle_frame.width << " center (X,Y): " << triangle_frame.pos.x << ", " << triangle_frame.pos.y << '\n';
    std::cout << "Triangle center after scale (before movement) (X,Y): " << triangle.getCenterX() << ", " << triangle.getCenterY() << '\n';
    shape->move(2.0, 1.0);
    std::cout << "Triangle center after vector movement (X,Y): " << triangle.getCenterX() << ", " << triangle.getCenterY() << '\n';
    triangle_frame = shape->getFrameRect();
    std::cout << "Triangle frame after vector movement: \n" << "height: " << triangle_frame.height << " width: "
        << triangle_frame.width << " center (X,Y): " << triangle_frame.pos.x << ", " << triangle_frame.pos.y << '\n';
    shape->move({ 1.0, 1.0 });
    std::cout << "Triangle center after point movement (X,Y): " << triangle.getCenterX() << ", " << triangle.getCenterY() << '\n';
    triangle_frame = shape->getFrameRect();
    std::cout << "Triangle frame after point movement: \n" << "height: " << triangle_frame.height << " width: "
        << triangle_frame.width << " center (X,Y): " << triangle_frame.pos.x << ", " << triangle_frame.pos.y << '\n';
  }
  catch (const std::invalid_argument& exception) {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (...) {
    std::cerr << "Unknown problem \n";
    return 2;
  }
  return 0;
}

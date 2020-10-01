#include <iostream>
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main() {
  try {
    std::cout<< "Composite shape test:\n";
    vorotnikov::Rectangle rectangle(2, 4, {0, 0});
    vorotnikov::Circle circle(5, {0, 0});
    vorotnikov::Triangle triangle({0, 5}, {-5, 0}, {5, 0});
    vorotnikov::CompositeShape compositeShape(3);
    std::shared_ptr<vorotnikov::Shape> shape1 = std::make_shared<vorotnikov::Rectangle>(rectangle);
    compositeShape.addShape(shape1);
    std::shared_ptr<vorotnikov::Shape> shape2 = std::make_shared<vorotnikov::Circle>(circle);
    compositeShape.addShape(shape2);
    std::shared_ptr<vorotnikov::Shape> shape3 = std::make_shared<vorotnikov::Triangle>(triangle);
    compositeShape.addShape(shape3);
    std::cout << "Composite Shape area before scale: " << compositeShape.getArea() << "\n";
    compositeShape.scale(2);
    std::cout << "Composite Shape area after scale (scale factor = 2): "<< compositeShape.getArea() << "\n";
  }
  catch (const std::invalid_argument &exception) {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (const std::out_of_range &exception) {
    std::cerr << exception.what() << '\n';
    return 2;
  }
  catch (...) {
    std::cerr << "Unknown problem \n";
    return 3;
  }
  return 0;
}

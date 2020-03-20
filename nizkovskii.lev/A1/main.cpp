#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

void print_shape_info(Shape & shape)
{
  std::cout << shape;
  std::cout << "Area=" << shape.getArea() << std::endl;
  rectangle_t frame = shape.getFrameRect();
  std::cout << "Frame: (" << frame.pos.x << "," << frame.pos.y << "), width=" << frame.width 
    << " height=" << frame.height << std::endl;
  shape.move({3.0,3.0});
  std::cout << "move to point" << std::endl << shape;
  shape.move(1.0,6.0);
  std::cout << "move dx, dy" << std::endl << shape << std::endl;
}

int main()
{
  try
  {
    Rectangle rectangle{ {2.0,3.0}, 4.0, 4.0 };
    Circle circle{ {1.0,1.0}, 3.0 };
    Triangle triangle{ {5.0,3.0}, {4.0,3.0}, {3.0,8.0} };
    print_shape_info(rectangle);
    print_shape_info(circle);
    print_shape_info(triangle);
  }
  catch(const std::invalid_argument & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
};

#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try
  {
    stolyarov::Circle crcl(5, stolyarov::point_t{ 4.5, 1.3 });
    stolyarov::Shape* shape1 = &crcl;
    shape1->printInf();
    shape1->move(14.5, -2.1);
    shape1->printInf();
    shape1->move(stolyarov::point_t{ 3, 3 });
    shape1->printInf();
    shape1->printFrameInf();
    shape1->scale(2.4);
    shape1->printInf();
    stolyarov::Rectangle rctngl(5, 2, stolyarov::point_t{ 3.2, 1.5 });
    stolyarov::Shape* shape2 = &rctngl;
    shape2->printInf();
    shape2->move(5.3, -4.1);
    shape2->printInf();
    shape2->move(stolyarov::point_t{ 2, 2 });
    shape2->printInf();
    shape2->printFrameInf();
    shape2->scale(0.7);
    shape2->printInf();
  }
  catch (const std::invalid_argument & message)
  {
    std::cerr << "ERROR: " << message.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown error";
    return 2;
  }
}

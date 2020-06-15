#include <iostream>
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/composite-shape.hpp"

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

    stolyarov::Circle crcl2(4, stolyarov::point_t{ 5.1, 3.1 });
    stolyarov::Rectangle rctngl2(2, 5, stolyarov::point_t{ 2.3, 5.1 });

    stolyarov::CompositeShape::shapePtr compShape1 = std::make_shared<stolyarov::Rectangle>(rctngl);
    stolyarov::CompositeShape::shapePtr compShape2 = std::make_shared<stolyarov::Circle>(crcl);
    stolyarov::CompositeShape::shapePtr compShape3 = std::make_shared<stolyarov::Rectangle>(rctngl2);
    stolyarov::CompositeShape::shapePtr compShape4 = std::make_shared<stolyarov::Circle>(crcl2);
    stolyarov::CompositeShape compositeShape;
    compositeShape.addElement(compShape1);
    compositeShape.addElement(compShape2);
    compositeShape.addElement(compShape3);
    compositeShape.addElement(compShape4);

    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.move(2.4, 13.2);
    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.scale(4.1);
    compositeShape.printInf();
    compositeShape.printFrameInf();
    compositeShape.removeElement(0);
    compositeShape.printInf();
    compositeShape.printFrameInf();
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
  return 0;
}




#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  lovkacheva::Shape *shapes[] = {new lovkacheva::Circle(25.5, lovkacheva::point_t{1.05, 23.7}),
      new lovkacheva::Rectangle(lovkacheva::rectangle_t{30.0, 10.67, lovkacheva::point_t{12.3, 10.0}})};
  for (lovkacheva::Shape *shape : shapes)
  {
    std::cout << "The shape: ";
    shape->print(std::cout);

    std::cout << "\nIts frame rectangle:  width = " << shape->getFrameRect().width << "; height = "
        << shape->getFrameRect().height << "; pos(" << shape->getFrameRect().pos.x << ", "
        << shape->getFrameRect().pos.y << ")\n";

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

    std::cout << "\nThe shape after -420.5 degree rotation: ";
    shape->rotate(-420.5);
    std::cout << "\nIts frame rectangle:  width = " << shape->getFrameRect().width << "; height = "
        << shape->getFrameRect().height << "; pos(" << shape->getFrameRect().pos.x << ", "
        << shape->getFrameRect().pos.y << ")\n";
    shape->print(std::cout);
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

  std::cout << "\nIts frame rectangle:  width = " << compositeShape1.getFrameRect().width << "; height = "
      << compositeShape1.getFrameRect().height << "; pos(" << compositeShape1.getFrameRect().pos.x << ", "
      << compositeShape1.getFrameRect().pos.y << ")\n\n";

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

  std::cout << "\nThe composite shape after -420.5 degree rotation: ";
  compositeShape1.rotate(-420.5);
  compositeShape1.print(std::cout);
  std::cout << "\nIts frame rectangle:  width = " << compositeShape1.getFrameRect().width << "; height = "
      << compositeShape1.getFrameRect().height << "; pos(" << compositeShape1.getFrameRect().pos.x << ", "
      << compositeShape1.getFrameRect().pos.y << ")\n";
  std::cout << "\n\n";

  lovkacheva::CompositeShape compositeShape2 = compositeShape1;
  std::cout << "A copy of the composite shape:\n";
  compositeShape2.print(std::cout);
  std::cout << "\n\n\n";


  std::shared_ptr<lovkacheva::CompositeShape> compositeShapeMatrixComponent
      = std::make_shared<lovkacheva::CompositeShape>(compositeShape2);
  std::shared_ptr<lovkacheva::Rectangle> rectangleMatrixComponent
      = std::make_shared<lovkacheva::Rectangle>(lovkacheva::rectangle_t{40, 40, {-40, -40}});
  std::shared_ptr<lovkacheva::Circle> circleMatrixComponent1
      = std::make_shared<lovkacheva::Circle>(0.5, lovkacheva::point_t{200, 200});
  std::shared_ptr<lovkacheva::Circle> circleMatrixComponent2
      = std::make_shared<lovkacheva::Circle>(5, lovkacheva::point_t{-3, 56});

  lovkacheva::Matrix matrix1;
  matrix1.addShape(compositeShapeMatrixComponent);
  matrix1.addShape(circleMatrixComponent1);
  matrix1.addShape(rectangleMatrixComponent);
  matrix1.addShape(compositeShapeMatrixComponent);
  matrix1.addShape(circleMatrixComponent2);
  matrix1.addShape(rectangleMatrixComponent);
  matrix1.addShape(compositeShapeMatrixComponent);
  matrix1.addShape(circleMatrixComponent1);
  matrix1.addShape(rectangleMatrixComponent);
  std::cout << "\n\n\nThe matrix:\n";
  for (size_t i = 0; i < matrix1.getRows(); ++i)
  {
    std::cout << "Layer " << i << ":\n";
    for (size_t j = 0; j < matrix1.getLayerSize(i); ++j)
    {
      std::cout << '-';
      matrix1[i][j]->print(std::cout);
      std::cout << "\n\n";
    }
    std::cout << "\n";
  }
  lovkacheva::Matrix matrix2 = matrix1;
  std::cout << "\n\n\nA second matrix created with the copy constructor:\n";
  for (size_t i = 0; i < matrix2.getRows(); ++i)
  {
    std::cout << "Layer " << i << ":\n";
    for (size_t j = 0; j < matrix2.getLayerSize(i); ++j)
    {
      std::cout << '-';
      matrix2[i][j]->print(std::cout);
      std::cout << "\n\n";
    }
    std::cout << "\n";
  }
  lovkacheva::Matrix matrix3;
  matrix3 = matrix2;
  std::cout << "\n\n\nA third matrix after the second matrix is assigned to it:\n";
  for (size_t i = 0; i < matrix3.getRows(); ++i)
  {
    std::cout << "Layer " << i << ":\n";
    for (size_t j = 0; j < matrix3.getLayerSize(i); ++j)
    {
      std::cout << '-';
      matrix3[i][j]->print(std::cout);
      std::cout << "\n\n";
    }
    std::cout << "\n";
  }
  lovkacheva::CompositeShape compositeShape;
  compositeShape.addShape(compositeShapeMatrixComponent);
  compositeShape.addShape(circleMatrixComponent1);
  compositeShape.addShape(rectangleMatrixComponent);
  compositeShape.addShape(compositeShapeMatrixComponent);
  compositeShape.addShape(circleMatrixComponent2);
  compositeShape.addShape(rectangleMatrixComponent);
  compositeShape.addShape(compositeShapeMatrixComponent);
  compositeShape.addShape(circleMatrixComponent1);
  compositeShape.addShape(rectangleMatrixComponent);
  std::cout << "\n\n\nA matrix created by splitting a composite shape:\n";
  lovkacheva::Matrix splitResult = compositeShape.split();
  for (size_t i = 0; i < splitResult.getRows(); ++i)
  {
    std::cout << "Layer " << i << ":\n";
    for (size_t j = 0; j < splitResult.getLayerSize(i); ++j)
    {
      std::cout << '-';
      splitResult[i][j]->print(std::cout);
      std::cout << "\n\n";
    }
    std::cout << "\n";
  }
  return 0;
}

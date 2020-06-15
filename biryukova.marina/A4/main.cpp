#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    biryukova::Circle circle1(biryukova::point_t{ 1.8,4.2 }, 8.1);
    biryukova::Circle circle2(biryukova::point_t{ 3.8,7.0 }, 1.4);
    biryukova::Shape* shapes[2] = { &circle1, &circle2 };
    for (int i = 0; i < 2; i++)
    {
      std::cout << "Starting position of shape " << i + 1 << ":\n";
      shapes[i]->print();
      std::cout << "Area of shape " << i + 1 << ": ";
      std::cout << shapes[i]->getArea() << '\n';
      biryukova::Rectangle rec(shapes[i]->getFrameRect());
      std::cout << "The frame rectangle of shape " << i + 1 << ":\n";
      rec.print();
      shapes[i]->move(biryukova::point_t{ 1,0 });
      std::cout << "New position of shape " << i + 1 << ":\n";
      shapes[i]->print();
      shapes[i]->scale(2.3);
      std::cout << "Position after scaling with coefficient 3.1 of shape " << i + 1 << ":\n";
      shapes[i]->print();
    }
    biryukova::Rectangle rectangle1(biryukova::point_t{ 3.0, 7.1 }, 9.4, 2.4);
    biryukova::Rectangle rectangle2(biryukova::point_t{ 6.9, 5.2 }, 9.0, 10.5);
    shapes[0] = &rectangle1;
    shapes[1] = &rectangle2;
    for (int i = 0; i < 2; i++)
    {
      std::cout << "Starting position of shape " << i + 1 << ":\n";
      shapes[i]->print();
      std::cout << "Area of shape " << i + 1 << ": ";
      std::cout << shapes[i]->getArea() << '\n';
      biryukova::Rectangle rec(shapes[i]->getFrameRect());
      std::cout << "The frame rectangle of shape " << i + 1 << ":\n";
      rec.print();
      shapes[i]->move(0.7, 3.6);
      std::cout << "New position of shape " << i + 1 << ":\n";
      shapes[i]->print();
      shapes[i]->scale(0.9);
      std::cout << "Position after scaling with coefficient 1.9 of shape " << i + 1 << ":\n";
      shapes[i]->print();
    }
    biryukova::CompositeShape array(4);
    biryukova::CompositeShape::shapePtr shape1 = std::make_shared<biryukova::Circle>(circle1);
    biryukova::CompositeShape::shapePtr shape2 = std::make_shared<biryukova::Circle>(circle2);
    biryukova::CompositeShape::shapePtr shape3 = std::make_shared<biryukova::Rectangle>(rectangle1);
    biryukova::CompositeShape::shapePtr shape4 = std::make_shared<biryukova::Rectangle>(rectangle2);
    array.insert(shape1);
    array.insert(shape2);
    array.insert(shape3);
    array.insert(shape4);
    std::cout << "Starting position of shapes:\n";
    array.print();
    biryukova::Rectangle rec(array.getFrameRect());
    std::cout << "The frame rectangle of shapes:\n";
    rec.print();
    array.move(biryukova::point_t{ 3.4, 1.2 });
    array.scale(2.0);
    array.rotate(90);
    std::cout << "New position of shapes:\n";
    array.print();
    array.remove(2);
    std::cout << "Position of shapes after removing shape 2:\n";
    array.print();
    biryukova::Matrix matrix = array.partition();
    for (size_t i = 0; i < matrix.getRows(); i++)
    {
      std::cout << i << " row:\n";
      for (size_t j = 0; j < matrix.getColumns(); j++)
      {
        if (matrix[i][j] != nullptr)
        {
          matrix[i][j]->print();
        }
      }
    }
  }
  catch (std::logic_error& error)
  {
    std::cerr << error.what() << '\n';
    return -1;
  }
  return 0;
}



#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
namespace rodion
{
  class Rectangle : public Shape {
  public:
      Rectangle(const rectangle_t &rectangle);

      double getArea() const override;

      rectangle_t getFrameRect() const override;

      void show() const override;

      void move(const point_t &x) override;

      void move(const double x, const double y) override;

      void scale(double value) override;


  private:
      rectangle_t rectangle;
  };
};



#endif /* rectangle_hpp */

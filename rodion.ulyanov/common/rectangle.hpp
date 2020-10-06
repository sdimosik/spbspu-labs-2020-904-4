

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
    
      void rotate(double angle) noexcept override;


  private:
      rectangle_t rectangle;
      double angle_ = 0.0;
  };
};



#endif /* rectangle_hpp */

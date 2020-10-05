
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace pashnin
{
  
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &dot);
    
    double getArea() const override;
    
    rectangle_t getFrameRect() const override;
    
    void move(const point_t &dot) override;
    
    void move(double xAxis, double yAxis) override;
  
    void scale(double factor) override;
  
    void rotate(double angle) noexcept override;

  private:
    double width_, height_, angle_ = 0.0;
    point_t position_;
  };
  
}

#endif

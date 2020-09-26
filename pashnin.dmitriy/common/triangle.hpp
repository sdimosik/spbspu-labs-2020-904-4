
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace pashnin
{
  
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t &dot1, const point_t &dot2, const point_t &dot3);
    
    double getArea() const override;
    
    rectangle_t getFrameRect() const override;
    
    void move(const point_t &dot) override;
    
    void move(double xAxis, double yAxis) override;
    
    void scale(double factor) override;

  private:
    point_t top1_, top2_, top3_;
    
  };
  
}

#endif

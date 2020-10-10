
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
  
    double getCenterX() const;
  
    double getCenterY() const;
  
    point_t getTop1() const;
  
    point_t getTop2() const;
  
    point_t getTop3() const;
  
    void move(const point_t &dot) override;
    
    void move(double xAxis, double yAxis) override;
    
    void scale(double factor) override;

    void rotate(double angle) noexcept override;
    
    
    
  private:
    point_t top1_, top2_, top3_;
    double angle_;
    
  };
  
}

#endif


#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <memory>
#include <initializer_list>
#include "shape.hpp"

namespace pashnin {
  class Polygon : public Shape {
  public:
    Polygon(const std::initializer_list<point_t>&);
    
    double getArea() const noexcept override;
    
    rectangle_t getFrameRect() const noexcept override;
    
    void move(const point_t &) noexcept override;
    
    void move(double xChange, double yChange) noexcept override;
    
    void scale(double factor) override;
    
    void rotate(double angle) noexcept override;
    
    point_t getPosition() noexcept;
  
  private:
    bool isConvex() const;
    double angle_ = 0.0;
    size_t count_;
    std::unique_ptr<point_t[]> points_;
  };
}

#endif

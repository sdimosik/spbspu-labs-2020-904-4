#ifndef circle_hpp
#define circle_hpp

#include "base-types.hpp"
#include "shape.hpp"

namespace kundik {
  class Circle : public Shape
  {
  public:
    Circle(const point_t& pos, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& end_pos) override;
    void move(double change_x, double change_y) override;
    double getRadius() const;
    double getCenterX() const;
    double getCenterY() const;
    void scale(double coefficent);
  private:
    double radius_;
    point_t pos_;
  };
}
#endif

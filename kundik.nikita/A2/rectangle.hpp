#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"
#include "base-types.hpp"

namespace kundik {
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& pos, double height, double width);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& end_pos) override;
    void move(double change_x, double change_y) override;
    double getHeight() const;
    double getWidth() const;
    double getCenterX() const;
    double getCenterY() const;
    void scale(double coefficent);
  private:
    double height_;
    double width_;
    point_t pos_;
  };
}
#endif

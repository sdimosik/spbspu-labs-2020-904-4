#ifndef RECTANGLE
#define RECTANGLE

#include "shape.hpp"

namespace kichigin
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double high, const point_t& pos);
    double getWidth() const noexcept;
    double getHeight() const noexcept;
    point_t getPosition() const noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void setWidth(double width);
    void setHeight(double high);
    void move(const point_t& position) noexcept override;
    void move(double x, double y) noexcept override;
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;
  private:
    rectangle_t figure_;
    double angle_;
  };
}

#endif //!RECTANGLE

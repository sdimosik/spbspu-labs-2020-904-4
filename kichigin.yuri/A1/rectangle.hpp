#ifndef RECTANGLE
#define RECTANGLE

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double width, double high, const point_t& pos);
  double getWidth() const;
  double getHeight() const;
  point_t getPosition() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void setWidth(double width);
  void setHeight(double high);
  void move(const point_t& position) override;
  void move(double x, double y) override;
private:
  rectangle_t figure_;
};

#endif //!RECTANGLE

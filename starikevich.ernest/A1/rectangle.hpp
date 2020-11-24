#ifndef RECTANGLE
#define RECTANGLE

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t& pos, double width, double height);
  void move(const point_t& pos) override;
  void move(double x, double y) override;
  rectangle_t getFrameRect() const override;
  double getWidth() const;
  double getHeight() const;
  void setWidth(double width);
  void setHeight(double height);
  point_t getPosition() const;
  double getArea() const override;
private:
  rectangle_t rectangle_;
};

#endif

#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
namespace sviridov
{
  class Circle : public Shape
  {
  public:
    double getArea() const override;
    rectangle_t getFrameRect() const;
    Circle(const point_t&, double);
    friend std::ostream& operator<<(std::ostream&, const Circle&);
    void scale(double);
    void move(const point_t&) override;
    void move(double, double) override;
  private:
    point_t pos_;
    double rad_;
    void printInform(std::ostream&) const override;
  };
  std::ostream& operator<<(std::ostream&, const Circle&);
}
#endif

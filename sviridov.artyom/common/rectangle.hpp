#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
namespace sviridov
{
  class Rectangle :public Shape
  {
  public:
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    Rectangle(const point_t&, double, double);
    friend std::ostream& operator<<(std::ostream&, const Rectangle&);
    void move(const point_t&) override;
    void move(double, double) override;
    void scale(double) override;
    friend bool operator==(const Rectangle&, const Rectangle&);
  private:
    point_t vertex_[3];
    void printInform(std::ostream& out) const override;
  };
  std::ostream& operator<<(std::ostream&, const Rectangle&);
  bool operator==(const Rectangle&, const Rectangle&);
}
#endif

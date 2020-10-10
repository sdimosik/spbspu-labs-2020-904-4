
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
namespace rodion
{
  class Circle : public Shape
  {
  public:
    Circle (const double &radius, const point_t &centre);
    void move (const point_t &x) override;
    void move (const double x, const double y) override;
    void show () const override;
    rectangle_t getFrameRect() const override;
    double getArea () const override;
    void scale (double value) override;
    void rotate(double angle) noexcept override;

  private:
    double radius;
    point_t centre;
  };
};

#endif /* circle_hpp */

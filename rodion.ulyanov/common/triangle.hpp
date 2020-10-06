#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace rodion
{
  class Triangle : public Shape
  {
  public:
    ~Triangle() = default;
    Triangle (const point_t &point_A, const point_t &point_B , const point_t &point_C);
    point_t getPointA() const;
    point_t getPointB() const;
    point_t getPointC() const;
    double getArea () const override;
    point_t getCentre () const;
    void move (const double x, const double y) override ;
    void move (const point_t &point) override;
    rectangle_t getFrameRect() const override;
    void show () const override;
    void scale(double value) override;
    void rotate(double angle) noexcept override;
  
  private:
    point_t point_A, point_B, point_C;
    point_t centre;
    point_t calculateCentre();
    double angle_ = 0.0;
  };
};
#endif /* Triangle_hpp */

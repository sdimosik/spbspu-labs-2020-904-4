#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace meshcheryakov
{
    class Circle : public Shape
    {
    public:
      Circle(double radius, const point_t& point);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(double dx, double dy) override;
      void move(const point_t& point) override;
      void scale(const double coefficient) override;
      point_t getPosition() const noexcept override;
      double getRadius() const;

    private:
      double radius_;
      point_t point_;
    };
}

#endif

#ifndef SPBSPU_LABS_2020_904_4_POLYGON_HPP
#define SPBSPU_LABS_2020_904_4_POLYGON_HPP
#include <memory>
#include <initializer_list>
#include "shape.hpp"

namespace rodion {
  class Polygon : public Shape {
  public:
    Polygon(const std::initializer_list<point_t>&);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &) noexcept override;

    void move(const double, const double) noexcept override;

    void scale(const double) override;

    void rotate(double) noexcept override;

    point_t getPosition() noexcept;
    
    void show() const override;

  private:
    bool isConvex() const;

    double angle_ = 0.0;

    unsigned int count_;

    std::unique_ptr<point_t[]> points_;
  };
}

#endif


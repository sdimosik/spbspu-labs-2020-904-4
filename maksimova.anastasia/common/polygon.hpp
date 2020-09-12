#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <memory>
#include "shape.hpp"

namespace maksimova
{
  class Polygon : public Shape
  {
  public:
    using pointArray = std::unique_ptr<point_t[]>;

    Polygon(const point_t* points, size_t size);

    Polygon(const Polygon& other);

    Polygon(Polygon&& other);

    ~Polygon() = default;

    Polygon &operator= (const Polygon& other);

    Polygon &operator= (Polygon&& other);

    point_t &operator[] (size_t index);

    void move(const point_t &pos) noexcept override;

    void move(const double dx, const double dy) noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    double getArea() const noexcept override;

    void scale(const double coefficient) override;

    void rotate(const double angle) noexcept override;

    void print() const override ;

  private:
    size_t size_;
    pointArray points_;

    bool is_convex() const noexcept ;
    point_t get_center() const noexcept;
  };
}


#endif

#ifndef POLYGON_HPP
#define POLUGON_HPP

#include <memory>
#include "base-types.hpp"
#include "shape.hpp"

namespace stolyarov
{
  class Polygon : public Shape
  {
  public:
    Polygon() = delete;

    Polygon(const point_t* points, size_t pointsNum);

    Polygon(const Polygon& otherPoligon);

    Polygon(Polygon&& otherPoligon) = default;

    ~Polygon() = default;

    Polygon& operator= (const Polygon& otherPoligon);

    Polygon& operator= (Polygon&& otherPoligon) = default;

    point_t getCenter() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t& pos) noexcept override;

    double getArea() const noexcept override;

    size_t getPointsNum() const;

    void printInf() override;

    void printFrameInf() override;

    rectangle_t getFrameRect() const noexcept override;

    void scale(double rate) override;

    void rotate(const double angle) noexcept override;

  private:
    size_t pointsNum_;
    std::unique_ptr<point_t[]> points_;
    bool isConvex(const point_t* points);
    void calculateCenter();
  };
}
#endif

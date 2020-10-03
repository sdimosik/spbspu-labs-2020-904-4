#ifndef POLYGON
#define POLYGON

#include <ctime>
#include <memory>
#include "shape.hpp"

namespace brezho
{
  class Polygon : public Shape
  {
  public:
    Polygon(const point_t array[], size_t size);
    Polygon(const Polygon& otherPolygon);
    Polygon(Polygon&& otherPolygon) noexcept;
    ~Polygon() = default;
    Polygon& operator=(const Polygon& otherPolygon);
    Polygon& operator=(Polygon&& otherPolygon) noexcept;
    void move(const point_t& pos) noexcept override;
    void move(const double x, const double y) noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    size_t getPeaksCount() const noexcept;
    point_t getPeakCoordinates(size_t index);
    double getSide(size_t index);
    point_t getPosition() const noexcept override;
    double getArea() const noexcept override;
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;
  private:
    using arrayPtr = std::unique_ptr<point_t[]>;
    arrayPtr peaks_;
    size_t size_;
  };
}

#endif

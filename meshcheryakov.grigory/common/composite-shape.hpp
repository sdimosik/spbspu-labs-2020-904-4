#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include <memory>
#include "shape.hpp"

namespace meshcheryakov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(size_t space);
    CompositeShape(const CompositeShape &other);
    CompositeShape(CompositeShape &&other) noexcept;
    ~CompositeShape() = default;
    CompositeShape &operator=(const CompositeShape &other);
    CompositeShape &operator=(CompositeShape &&other) noexcept;
    std::shared_ptr<Shape> &operator[](size_t index);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t& point) noexcept override;
    void scale(const double coefficient) override;
    point_t getPosition() const noexcept override;
    int getSize() const noexcept;
    void addShape(const std::shared_ptr<Shape>& shape);
    void removeShape(size_t index);

  private:
    using shapeArray = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t size_;
    size_t space_;
    shapeArray shapes_;
  };
}

#endif

#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP
#include <memory>
#include "shape.hpp"

namespace  maksimova
{
  class CompositeShape : Shape
  {
  public:
    CompositeShape();

    CompositeShape(const CompositeShape &other);

    CompositeShape(CompositeShape &&other) noexcept;

    explicit CompositeShape(const size_t count);

    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &other);

    CompositeShape &operator=(CompositeShape &&other) noexcept;

    std::shared_ptr<Shape> &operator[](const size_t index);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &pos) noexcept override;

    void move(const double dx, const double dy) noexcept override;

    void scale(const double coefficient) override;

    void addShape(const std::shared_ptr<Shape>& shape);

    void deleteShape(const size_t index);

    void print() const override;

  private:
    using shapePtr = std::shared_ptr<Shape>;
    using shapeArray = std::unique_ptr<shapePtr[]>;
    size_t size_;
    size_t count_;
    shapeArray shapes_;
  };
}

#endif

#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace dmitriev
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();

    explicit CompositeShape(size_t capacity);

    CompositeShape(const CompositeShape &other);

    CompositeShape(CompositeShape &&other) noexcept;

    CompositeShape &operator=(const CompositeShape &other);

    CompositeShape &operator=(CompositeShape &&other) noexcept;

    std::shared_ptr<Shape> &operator[](size_t index) const;

    size_t getSize() const;

    void addShape(const std::shared_ptr<Shape> &shape);

    void removeShape(size_t index);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &position) noexcept override;

    void move(double x, double y) noexcept override;

    void scale(double factor) override;

    void rotate(double angle) noexcept override;

    Matrix toMatrix() const noexcept;

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
    size_t capacity_;
  };
}

#endif

#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"


namespace bakaeva
{
  class CompositeShape : public Shape
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;

    CompositeShape();

    explicit CompositeShape(const size_t volume);

    CompositeShape(const CompositeShape &other);

    CompositeShape(CompositeShape &&other) noexcept;

    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &other);

    CompositeShape &operator=(CompositeShape &&other) noexcept;

    shapePtr &operator[](const size_t index);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &center) noexcept override;

    void move(const double x, const double y) noexcept override;

    void scale(const double coefficient) override;

    void addShape(const shapePtr &shape);

    void removeShape(const size_t index);

    size_t getSize() const noexcept;

    point_t getCenter() const noexcept override;

    void printFrameRect() const override;

    void printData() const override;

    void rotate(const double angle) noexcept override;

    Matrix layering() const;

  private:
    using shapeArray = std::unique_ptr<shapePtr[]>;
    size_t volume_;
    size_t size_;
    shapeArray shapes_;
  };
}
#endif

#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace lovkacheva
{
  class CompositeShape : public Shape
  {
  public:
    using ShapePtr = std::shared_ptr<Shape>;

    CompositeShape();

    CompositeShape(size_t capacity);

    CompositeShape(const CompositeShape& other);

    CompositeShape(CompositeShape&& other) noexcept;

    CompositeShape& operator=(const CompositeShape& other);

    CompositeShape& operator=(CompositeShape&& other) noexcept;

    ShapePtr operator[](size_t index) const;

    void print(std::ostream& out) const override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& newPosition) noexcept override;

    void move(double dx, double dy) noexcept override;

    void scale(double coefficient) override;

    void addShape(const CompositeShape::ShapePtr& newShape);

    void removeShape(size_t index);

    size_t getSize() const noexcept;

  private:
    using ShapeArray = std::unique_ptr<ShapePtr[]>;
    size_t size_;
    size_t capacity_;
    ShapeArray componentShapes_;

  };
}
#endif

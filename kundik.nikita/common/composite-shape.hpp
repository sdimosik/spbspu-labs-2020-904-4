#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace kundik {
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() = default;
    explicit CompositeShape(size_t capacity);
    CompositeShape(const CompositeShape& other);
    CompositeShape(CompositeShape&& other) noexcept;
    CompositeShape& operator=(const CompositeShape& other);
    CompositeShape& operator=(CompositeShape&& other) noexcept;
    ~CompositeShape() = default;
    std::shared_ptr<Shape>& operator[](size_t index);
    void addShape(const std::shared_ptr<Shape>& otherShape);
    size_t getSize() const noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& endPos) noexcept override;
    void move(double changeX, double changeY) noexcept override;
    void scale(double coefficient) override;
    void removeShape(size_t index);
    void rotate(double angle) noexcept;
    point_t getCentrer() const noexcept;
  private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<std::shared_ptr<Shape>[]> arrayShapes_;
  };
}
#endif

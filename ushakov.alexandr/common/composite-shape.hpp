#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace ushakov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();

    explicit CompositeShape(size_t capacity);

    ~CompositeShape() override = default;

    CompositeShape(const CompositeShape& compositeShape);

    CompositeShape(CompositeShape&& compositeShape) noexcept;

    CompositeShape& operator=(const CompositeShape& compositeShape);

    CompositeShape& operator=(CompositeShape&& compositeShape) noexcept;

    std::shared_ptr<Shape>& operator[](size_t index);

    size_t getSize() const;

    void addShape(const std::shared_ptr<Shape>& shape);

    void removeShape(size_t index);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& position) noexcept override;

    void move(double x, double y) noexcept override;

    void print() const override;

    void printFrameRectangle() const override;

    void scale(double coefficient) override;

    point_t getPosition() const override;

  private:
    using shapePtr = std::shared_ptr<Shape>;

    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
    size_t capacity_;
  };
}

#endif //A3_COMPOSITE_SHAPE_HPP

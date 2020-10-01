#ifndef USHAKOV_A_COMPOSITE_SHAPE_HPP
#define USHAKOV_A_COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"
#include "matrix.hpp"

namespace ushakov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();

    explicit CompositeShape(size_t capacity);

    ~CompositeShape() override = default;

    CompositeShape(const CompositeShape& compositeShape) noexcept;

    CompositeShape(CompositeShape&& compositeShape) noexcept;

    CompositeShape& operator=(const CompositeShape& compositeShape);

    CompositeShape& operator=(CompositeShape&& compositeShape) noexcept;

    std::shared_ptr<Shape> operator[](size_t index) const;

    void addShape(const std::shared_ptr<Shape>& shape);

    void removeShape(size_t index);

    void move(const point_t& newPosition) noexcept override;

    void move(double xAxis, double yAxis) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override;

    Matrix divide() const;

    size_t getSize() const noexcept;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getPosition() const noexcept override;

    void print() const noexcept override;

    void printFrameRectangle() const noexcept override;

  private:
    using shapePtr = std::shared_ptr<Shape>;
    using compositeShapePtr = std::unique_ptr<std::shared_ptr<Shape>[]>;

    compositeShapePtr shapes_;
    size_t size_;
    size_t capacity_;
  };
}

#endif //USHAKOV_A_COMPOSITE_SHAPE_HPP

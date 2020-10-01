#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace khilchenko
{
  class CompositeShape :public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(size_t size);
    CompositeShape(const CompositeShape &shapes);
    CompositeShape(CompositeShape &&shapes) noexcept;
    std::shared_ptr<Shape>& operator[](size_t index) const;
    CompositeShape& operator=(const CompositeShape &shapes);
    CompositeShape& operator=(CompositeShape &&shapes) noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newPos) noexcept override;
    void move(double x, double y) noexcept override;
    point_t getCenter() const noexcept override;
    void scale(double coefficient) override;
    void addShape(const std::shared_ptr<Shape>& shape);
    void removeShape(size_t index);
    int getSize() const noexcept;
    int getAmount() const noexcept;
    void rotate(double angle) noexcept override;
    Matrix getLayerMatrix();
  private:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t size_;
    size_t amount_;
    arrayPtr shapes_;
  };
}
#endif

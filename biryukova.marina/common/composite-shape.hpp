#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace biryukova
{
  class CompositeShape : public Shape
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;
    CompositeShape();
    CompositeShape(size_t space);
    CompositeShape(const CompositeShape& cs);
    CompositeShape(CompositeShape&& cs) noexcept;
    CompositeShape& operator=(const CompositeShape& cs);
    CompositeShape& operator=(CompositeShape&& cs) noexcept;
    void insert(const shapePtr& shape);
    void remove(size_t index);
    int getSize() const noexcept;
    shapePtr& operator[](size_t index) const;
    double getArea() const noexcept override;
    biryukova::rectangle_t getFrameRect() const noexcept override;
    void move(const biryukova::point_t& point) noexcept override;
    void move(double x, double y) noexcept override;
    void print() const override;
    void scale(double coefficient) override;
    point_t getCentre() const noexcept override;
    void rotate(double angle) override;
    Matrix partition() const;
  private:
    using shapesArray = std::unique_ptr<shapePtr[]>;
    size_t size_;
    size_t space_;
    shapesArray shapes_;
  };
}

#endif

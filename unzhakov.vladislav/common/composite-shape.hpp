#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace unzhakov
{

  struct point_t;
  struct rectangle_t;

  class CompositeShape: public Shape
  {
  public:
    CompositeShape();

    CompositeShape(const CompositeShape &otherCompositeShape);

    CompositeShape(CompositeShape &&otherCompositeShape) noexcept;

    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &otherCompositeShape);

    CompositeShape &operator=(CompositeShape &&otherCompositeShape) noexcept;

    SharedPtr operator[](size_t index);

    void add(const SharedPtr &figure);

    void remove(size_t index);

    double getArea() const override;

    size_t getSize() const;

    point_t getCenter() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &pos) override;

    void printData() const override;

    void printFrameRectangle() const override;

    void printArea() const override;

    void move(double x, double y) override;

    void scale(double coefficient) override;

  private:
    std::unique_ptr<SharedPtr[]> array_;
    size_t size_;
  };
}

#endif

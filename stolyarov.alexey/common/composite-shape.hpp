#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace stolyarov
{
  class CompositeShape : public Shape
  {
  public:

    using shapePtr = std::shared_ptr<Shape>;

    CompositeShape();

    CompositeShape(const CompositeShape& element);

    CompositeShape(CompositeShape&& element) noexcept;

    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape& element);

    CompositeShape& operator=(CompositeShape&& element) noexcept;
    
    shapePtr& operator[](const size_t index);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getCenter() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t& center) noexcept override;

    void scale(double rate) override;

    void addElement(const shapePtr& element);

    void removeElement(size_t index);

    void printInf() override;

    void printFrameInf() override;

  private:
    using shapeArray = std::unique_ptr<shapePtr[]>;
    size_t size_;
    size_t place_;
    shapeArray shapes_;
  };
}
#endif

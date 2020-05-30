#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include "shape.hpp"
#include <memory>

namespace spasoevich
{
  class CompositeShape : public Shape
  {
  public:
    using shape_ptr=std::shared_ptr<Shape>;
    CompositeShape();
    CompositeShape(const CompositeShape& copyShape);
    CompositeShape(CompositeShape&& moveShape) noexcept;
    CompositeShape& operator=(const CompositeShape& copy);
    CompositeShape& operator=(CompositeShape&& move) noexcept;
    shape_ptr operator[](size_t index) const;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t& p) noexcept override;
    void scale(const double coefficient) override;
    void addShape(shape_ptr& shape);
    void removeShape(size_t index);
    size_t getSize() const noexcept;
    void printCompositeShapeData() noexcept;
  private:
    using shape_array=std::unique_ptr<shape_ptr[]>;
    size_t shapeCount_;
    size_t size_;
    shape_array arrayOfShapes_;
  };
}
#endif

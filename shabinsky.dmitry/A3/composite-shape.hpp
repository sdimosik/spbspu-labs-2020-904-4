#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace shabinsky
{
  class CompositeShape : Shape
  {
  public:
    CompositeShape() noexcept;
    
    explicit CompositeShape(size_t length);
    
    CompositeShape(const CompositeShape &compositeShape);
    
    CompositeShape(CompositeShape &&compositeShape) noexcept;
    
    void addShape(const std::shared_ptr<Shape> &shape);
    
    void deleteShape(size_t index);
    
    double getArea() const noexcept override;
    
    rectangle_t getFrameRect() const noexcept override;
    
    void move(const point_t &point) noexcept override;
    
    void move(double x, double y) noexcept override;
    
    void show(std::ostream &out) noexcept override;
    
    void scale(double coefficient) noexcept override;
    
    std::shared_ptr<Shape> &operator[](size_t index) const;
    
    size_t getSize() const noexcept;
    
    size_t getLength() const noexcept;
  
  private:
    using compositionPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t size_;
    size_t length_;
    compositionPtr composition_;
  };
}

#endif //COMPOSITE_SHAPE_HPP

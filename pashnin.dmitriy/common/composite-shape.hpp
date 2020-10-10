
#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace pashnin
{
  class CompositeShape : public Shape
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;
  
    CompositeShape();
  
    explicit CompositeShape(size_t capacity);
  
    CompositeShape(const CompositeShape &other);
  
    CompositeShape(CompositeShape &&other) noexcept;
    
    CompositeShape &operator=(const CompositeShape &other);
  
    CompositeShape &operator=(CompositeShape &&other) noexcept;
    
    ~CompositeShape() override = default;
  
    shapePtr &operator[](size_t index);
  
    size_t getSize() const;
  
    void addShape(const shapePtr &shape);
  
    void removeShape(size_t index);
  
    double getArea() const noexcept override;
  
    pashnin::rectangle_t getFrameRect() const noexcept override;
  
    void move(const point_t &position) noexcept override;
  
    void move(double x, double y) noexcept override;
  
    void scale(double factor) override;
    
    void rotate(double angle) noexcept override;
  
    Matrix toMatrix() const noexcept;
    
  private:
    using arrShape = std::unique_ptr<shapePtr[]>;
    arrShape shapes_;
    size_t capacity_;
    size_t size_;
  };
}

#endif


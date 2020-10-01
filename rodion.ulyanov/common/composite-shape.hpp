#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include <memory>
#include "shape.hpp"

namespace rodion
{
  class CompositeShape : public Shape
  {
  public:
    ~CompositeShape() = default;
    
    CompositeShape() ;

    explicit CompositeShape(size_t capacity);

    CompositeShape(const CompositeShape &other);

    CompositeShape(CompositeShape &&other) noexcept;

    CompositeShape &operator=(const CompositeShape &other);

    CompositeShape &operator=(CompositeShape &&other) noexcept;

    std::shared_ptr<Shape> &operator[](size_t index) ;

    size_t getSize() const;

    void addShape(const std::shared_ptr<Shape> &shape);

    void removeShape(size_t index);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &position) noexcept override;

    void move(double x, double y) noexcept override;

    void scale(double factor) override;
    
    void show () const override;

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
    size_t capacity_;
  };
}
#endif

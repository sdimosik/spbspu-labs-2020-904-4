#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace anastasiev
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape&);
    CompositeShape(CompositeShape&&) noexcept;
    ~CompositeShape() override = default;
    
    CompositeShape& operator=(const CompositeShape&);
    CompositeShape& operator=(CompositeShape&&) noexcept;
    std::shared_ptr<Shape> operator[](const unsigned int) const;

    void add(const std::shared_ptr<Shape>&);
    void remove(const unsigned int);
    double getArea() const noexcept override;
    unsigned int getSize() noexcept;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &) noexcept override;
    void move(const double, const double) noexcept override;
    void scale(const double) override;
    void rotate(double) noexcept override;
    void rotateAroundPoint(double, const point_t&) noexcept override;
    Matrix getLayered() const;
  private:
    unsigned int size_;
    unsigned int capacity_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapeArray_;
  };
} // namespace anastasiev
#endif

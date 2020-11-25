#ifndef LABS_COMPOSITE_SHAPE_HPP
#define LABS_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace vasilevskaya
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape();
    explicit CompositeShape(size_t capacity);
    CompositeShape(const CompositeShape& copiedShape);
    CompositeShape(CompositeShape&& portableShape) noexcept;
    ~CompositeShape() override;
    CompositeShape& operator=(const CompositeShape& copiedShape);
    CompositeShape& operator=(CompositeShape&& portableShape) noexcept;
    PointToShape operator[](size_t index) const;
    double getArea() const override;
    point_t getPosition() const override;
    rectangle_t getFrameRect() const override;
    void move(double onTheAbscissa, double onTheOrdinate) override;
    void move(const point_t& newPoint) override;
    void printFigure() const override;
    void printFrameRect() const override;
    void scale(double quotient) override;
    void pushBack(const PointToShape& newShape);
    void remove(size_t index);
    size_t getCount() const;
    size_t getCapacity() const;

  private:
    std::allocator<PointToShape> allocatorForArray_;
    size_t countShape_;
    size_t capacity_;
    PointToShape* arrayShape_;
    const static size_t PRIMORDIAL_CAPACITY = 8;
    const static size_t EXPANSION_FACTOR = 2;
    void allocateMemory();
  };
}

#endif

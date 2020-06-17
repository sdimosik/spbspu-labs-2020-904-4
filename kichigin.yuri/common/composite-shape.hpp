#ifndef COMPOSITE_SHAPE
#define COMPOSITE_SHAPE
#include "shape.hpp"
#include <memory>

namespace kichigin
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const unsigned int fullSize);
    CompositeShape(const CompositeShape& shape);
    CompositeShape(CompositeShape&& shape) noexcept;
    std::shared_ptr<Shape>& operator[](unsigned int index) const;
    CompositeShape& operator=(const CompositeShape& shape);
    CompositeShape& operator=(CompositeShape&& shape) noexcept;
    void addShape(const std::shared_ptr<Shape>& shape);
    void deleteShape(unsigned int index);
    unsigned int getFullSize() const noexcept;
    unsigned int getCurrentSize() const noexcept;
    double getArea() const noexcept override;
    kichigin::rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& point) noexcept override;
    void move(double x, double y) noexcept override;
    void scale(double coefficient) override;
    void rotate(double andgle) noexcept override;
  private:
    using arrayType = std::unique_ptr<std::shared_ptr<Shape>[]>;
    unsigned int fullSize_;
    unsigned int currentSize_;
    arrayType array_;
  };
}
#endif // !COMPOSITE_SHAPE

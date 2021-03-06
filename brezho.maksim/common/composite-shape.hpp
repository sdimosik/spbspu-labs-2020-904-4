#ifndef COMPOSITESHAPE
#define COMPOSITESHAPE

#include <ctime>
#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace brezho
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const size_t fullSize_);
    CompositeShape(const CompositeShape& array);
    CompositeShape(CompositeShape&& array) noexcept;
    ~CompositeShape() = default;
    const std::shared_ptr<Shape>& operator[](const size_t index) const;
    CompositeShape& operator=(const CompositeShape& array);
    CompositeShape& operator=(CompositeShape&& array) noexcept;
    void move(const double x, const double y) noexcept override;
    void move(const point_t& pos) noexcept override;
    brezho::rectangle_t getFrameRect() const noexcept override;
    void addShape(const std::shared_ptr<Shape>& shape);
    void deleteShape(size_t index);
    size_t getFullSize() const noexcept;
    size_t getUsedSize() const noexcept;
    point_t getPosition() const noexcept override;
    double getArea() const noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle = 0) noexcept override;
    Matrix makeMatrix() const;

  private:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t fullSize_;
    size_t usedSize_;
    arrayPtr array_;
  };
}

#endif

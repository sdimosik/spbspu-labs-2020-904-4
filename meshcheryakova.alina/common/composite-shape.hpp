#ifndef LABS_SPBPU_COMPOSITESHAPE_HPP
#define LABS_SPBPU_COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace meshcheryakova
{
  class CompositeShape : public Shape
  {
  public:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;

    CompositeShape() noexcept;

    CompositeShape(const CompositeShape &other);

    CompositeShape(CompositeShape &&other) noexcept;

    CompositeShape &operator=(const CompositeShape &other);

    CompositeShape &operator=(CompositeShape &&other) noexcept;

    explicit CompositeShape(const size_t spaciousness);

    std::shared_ptr<Shape> &operator[](const size_t index) const;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &spot) noexcept override;

    void move(double x, double y) noexcept override;

    void printSpot(std::ostream &out) override;

    void scale(double coefficient) override;

    void printParametersWithoutSpot(std::ostream &out) override;

    void addElement(const std::shared_ptr<Shape>& shape);

    void deleteElement(const size_t index);

    void rotate(double angle) noexcept override;

    size_t getSize() const noexcept;

    arrayPtr& getShapes();
  private:
    size_t spaciousness_;
    size_t size_;
    arrayPtr shapes_;
  };
}

#endif //LABS_SPBPU_COMPOSITESHAPE_HPP

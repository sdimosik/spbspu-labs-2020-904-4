#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace bulanov
{
  class CompositeShape : Shape
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;

    CompositeShape();

    explicit CompositeShape(size_t space);

    CompositeShape(const CompositeShape &element);

    CompositeShape(CompositeShape &&element) noexcept;

    CompositeShape &operator=(const CompositeShape &element);

    CompositeShape &operator=(CompositeShape &&element) noexcept;

    shapePtr &operator[](const size_t index) const;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t &center) noexcept override;

    void scale(double rate) override;

    point_t getCenter() const noexcept override;

    void addElement(const shapePtr &element);

    void removeElement(size_t index);

    virtual void printInform() const override ;

    void printFrameInform() const override ;


  private:
    using shapeArray = std::unique_ptr<shapePtr[]>;
    size_t size_;
    size_t place_;
    shapeArray shapes_;

  };
}


#endif //A3_COMPOSITE_SHAPE_HPP

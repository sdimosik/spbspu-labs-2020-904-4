#include <stdexcept>
#include <limits>
#include <cmath>
#include "composite-shape.hpp"
#include "utils.hpp"

namespace dmitriev
{
  CompositeShape::CompositeShape() :
    shapes_(std::make_unique<std::shared_ptr<Shape>[]>(1)),
    size_(0),
    capacity_(1)
  {}

  CompositeShape::CompositeShape(const size_t capacity) :
    shapes_(std::make_unique<std::shared_ptr<Shape>[]>(capacity)),
    size_(0),
    capacity_(capacity)
  {
    if (capacity <= 0)
    {
      throw std::out_of_range("Composite shape capacity must be positive!");
    }
  }

  CompositeShape::CompositeShape(const dmitriev::CompositeShape &other) :
    shapes_(std::make_unique<std::shared_ptr<Shape>[]>(other.capacity_)),
    size_(other.size_),
    capacity_(other.capacity_)
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = other.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape &&other) noexcept :
    shapes_(std::move(other.shapes_)),
    size_(other.size_),
    capacity_(other.capacity_)
  {
    other.shapes_.reset();
    other.size_ = 0;
    other.capacity_ = 0;
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this == &other)
    {
      return *this;
    }
    std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[other.size_]);
    for (size_t i = 0; i < other.size_; i++)
    {
      tmpShapes[i] = other.shapes_[i];
    }
    shapes_ = std::move(tmpShapes);
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    shapes_ = std::move(other.shapes_);
    other.shapes_.reset();
    size_ = other.size_;
    other.size_ = 0;
    capacity_ = other.capacity_;
    other.capacity_ = 0;
    return *this;
  }

  std::shared_ptr<Shape> &CompositeShape::operator[](const size_t index) const
  {
    if (index >= size_)
    {
      throw std::out_of_range("Composite shape index must be less than shape size!");
    }
    return shapes_[index];
  }

  size_t CompositeShape::getSize() const
  {
    return size_;
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
  {
    if (!shape)
    {
      throw std::invalid_argument("Can't perform with null shape!");
    }
    if (size_ == capacity_)
    {
      std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[size_ + capacity_]);
      for (size_t i = 0; i < size_; i++)
      {
        tmpShapes[i] = shapes_[i];
      }
      capacity_ *= 2;
      shapes_ = std::move(tmpShapes);
    }
    shapes_[size_++] = shape;
  }

  void CompositeShape::removeShape(const size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Composite shape index to remove must be less than shape size!");
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[size_--] = nullptr;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0, 0, {0, 0}};
    }

    double left = std::numeric_limits<double>::max();
    double right = std::numeric_limits<double>::min();
    double top = std::numeric_limits<double>::min();
    double bottom = std::numeric_limits<double>::max();

    for (size_t i = 0; i < size_; i++)
    {
      const rectangle_t tmpRect = shapes_[i]->getFrameRect();
      left = std::min(left, tmpRect.pos.x - tmpRect.width / 2);
      right = std::max(right, tmpRect.pos.x + tmpRect.width / 2);
      top = std::max(top, tmpRect.pos.y + tmpRect.height / 2);
      bottom = std::min(bottom, tmpRect.pos.y - tmpRect.height / 2);
    }

    return {right - left, top - bottom, left + (right - left) / 2, bottom + (top - bottom) / 2,};
  }

  void CompositeShape::move(const point_t &position) noexcept
  {
    double dX = position.x - getFrameRect().pos.x;
    double dY = position.y - getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(dX, dY);
    }
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid scale factor was given. Must be positive.");
    }
    double centerX = getFrameRect().pos.x;
    double centerY = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(factor);
      double dX = shapes_[i]->getFrameRect().pos.x - centerX;
      double dY = shapes_[i]->getFrameRect().pos.y - centerY;
      shapes_[i]->move(dX * (factor - 1), dY * (factor - 1));
    }
  }

  double CompositeShape::getArea() const noexcept
  {
    double area = 0;
    for (size_t i = 0; i < size_; i++)
    {
      area += shapes_[i]->getArea();
    }
    return area;
  }

  void CompositeShape::rotate(double angle) noexcept
  {
    angle = fmod(angle, 360);
    if (angle < 0)
    {
      angle += 360;
    }
    angle = utils::toRadians(angle);
    const double centerX = getFrameRect().pos.x;
    const double centerY = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      const double dX = shapes_[i]->getFrameRect().pos.x - centerX;
      const double dY = shapes_[i]->getFrameRect().pos.y - centerY;
      const double distanceX = fabs(dX * cos(angle)) - fabs((dY * sin(angle)));
      const double distanceY = fabs(dX * sin(angle)) + fabs((dY * cos(angle)));
      shapes_[i]->move({centerX + distanceX, centerY + distanceY});
      shapes_[i]->rotate(utils::toDegree(angle));
    }
  }

  Matrix CompositeShape::toMatrix() const noexcept
  {
    Matrix matrix;
    for (size_t i = 0; i < size_; i++)
    {
      matrix.addShape(shapes_[i]);
    }
    return matrix;
  }
}

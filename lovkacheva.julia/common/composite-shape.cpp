#include "composite-shape.hpp"
#include <cmath>


namespace lovkacheva
{
  CompositeShape::CompositeShape() :
    size_(0),
    capacity_(0),
    componentShapes_(nullptr)
  { }

  CompositeShape::CompositeShape(size_t capacity) :
    size_(0),
    capacity_(capacity),
    componentShapes_(std::make_unique<ShapePtr[]>(capacity))
  { }

  CompositeShape::CompositeShape(const CompositeShape& other) :
    size_(other.size_),
    capacity_(other.capacity_),
    componentShapes_(std::make_unique<ShapePtr[]>(other.capacity_))
  {
    for (size_t i = 0; i < size_; ++i)
    {
      componentShapes_[i] = other.componentShapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape&& other) noexcept:
    size_(other.size_),
    capacity_(other.capacity_),
    componentShapes_(std::move(other.componentShapes_))
  {
    other.size_ = 0;
    other.capacity_ = 0;
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& other)
  {
    if (this != &other)
    {
      componentShapes_ = std::make_unique<ShapePtr[]>(other.capacity_);
      size_ = other.size_;
      capacity_ = other.capacity_;
      for (size_t i = 0; i < size_; ++i)
      {
        componentShapes_[i] = other.componentShapes_[i];
      }
    }
    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& other) noexcept
  {
    if (this != &other)
    {
      size_ = other.size_;
      capacity_ = other.capacity_;
      componentShapes_ = std::move(other.componentShapes_);
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  CompositeShape::ShapePtr CompositeShape::operator[](size_t index) const
  {
    if (index >= size_)
    {
      throw std::out_of_range("The index is out of range (index = " + std::to_string(index) + ")");
    }
    return componentShapes_[index];
  }

  void CompositeShape::print(std::ostream& out) const
  {
    if (size_ != 0)
    {
      out << "Composite Shape containing:";
      for (size_t i = 0; i < size_; ++i)
      {
        out << "\n[" << i << "]:";
        componentShapes_[i]->print(out);
        out << ';';
      }
    }
    else
    {
      out << "Empty Composite Shape";
    }
  }

  double CompositeShape::getArea() const noexcept
  {
    double result = 0;
    for (size_t i = 0; i < size_; ++i)
    {
      result += componentShapes_[i]->getArea();
    }
    return result;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return rectangle_t{0, 0, {0, 0}};
    }
    rectangle_t componentFrameRect = componentShapes_[0]->getFrameRect();
    double minLeft = componentFrameRect.pos.x - componentFrameRect.width / 2;
    double minLower = componentFrameRect.pos.y - componentFrameRect.height / 2;
    double maxRight = componentFrameRect.pos.x + componentFrameRect.width / 2;
    double maxUpper = componentFrameRect.pos.y + componentFrameRect.height / 2;
    for (size_t i = 1; i < size_; ++i)
    {
      componentFrameRect = componentShapes_[i]->getFrameRect();
      minLeft = std::min(componentFrameRect.pos.x - componentFrameRect.width / 2, minLeft);
      minLower = std::min(componentFrameRect.pos.y - componentFrameRect.height / 2, minLower);
      maxRight = std::max(componentFrameRect.pos.x + componentFrameRect.width / 2, maxRight);
      maxUpper = std::max(componentFrameRect.pos.y + componentFrameRect.height / 2, maxUpper);
    }
    double width = maxRight - minLeft;
    double height = maxUpper - minLower;
    return rectangle_t{width, height, point_t{minLeft + width / 2, minLower + height / 2}};
  }

  void CompositeShape::move(const point_t& newCompositePosition) noexcept
  {
    point_t currentCompositePosition = getFrameRect().pos;
    double dx = newCompositePosition.x - currentCompositePosition.x;
    double dy = newCompositePosition.y - currentCompositePosition.y;
    move(dx, dy);
  }

  void CompositeShape::move(double dx, double dy) noexcept
  {
    for (size_t i = 0; i < size_; ++i)
    {
      componentShapes_[i]->move(dx, dy);
    }
  }

  void CompositeShape::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(
        "The coefficient must be positive (coefficient = " + std::to_string(coefficient) + ")");
    }
    point_t compositePosition = getFrameRect().pos;
    for (size_t i = 0; i < size_; ++i)
    {
      componentShapes_[i]->scale(coefficient);
      point_t componentPosition = componentShapes_[i]->getFrameRect().pos;
      double dx = componentPosition.x - compositePosition.x;
      double dy = componentPosition.y - compositePosition.y;
      dx = coefficient * dx - dx;
      dy = coefficient * dy - dy;
      componentShapes_[i]->move(dx, dy);
    }
  }

  void CompositeShape::addShape(const CompositeShape::ShapePtr& newShape)
  {
    if (!newShape)
    {
      throw std::invalid_argument("The shape is a null pointer");
    }
    if (capacity_ == 0)
    {
      componentShapes_ = std::make_unique<ShapePtr[]>(1);
      capacity_ = 1;
    }
    else if (size_ == capacity_)
    {
      ShapeArray temp = std::make_unique<ShapePtr[]>(capacity_ * 2);
      capacity_ *= 2;
      for (size_t i = 0; i < size_; ++i)
      {
        temp[i] = componentShapes_[i];
      }
      componentShapes_ = std::move(temp);
    }
    componentShapes_[size_] = newShape;
    ++size_;
  }

  void CompositeShape::removeShape(size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("The index is out of range (index = " + std::to_string(index) + ")");
    }
    for (size_t i = index + 1; i < size_; ++i)
    {
      componentShapes_[i - 1] = componentShapes_[i];
    }
    componentShapes_[size_ - 1].reset();
    --size_;
  }

  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  void CompositeShape::rotate(double angle) noexcept
  {
    double angleInRadians = (angle / 180) * M_PI;
    point_t compositePosition = getFrameRect().pos;
    for (size_t i = 0; i < size_; ++i)
    {
      componentShapes_[i]->rotate(angle);
      point_t componentPosition = componentShapes_[i]->getFrameRect().pos;
      double distanceFromCentreX = componentPosition.x - compositePosition.x;
      double distanceFromCentreY = componentPosition.y - compositePosition.y;
      double newDistanceFromCentreX =
          distanceFromCentreX * std::cos(angleInRadians) - distanceFromCentreY * std::sin(angleInRadians);
      double dx = newDistanceFromCentreX - distanceFromCentreX;
      double newDistanceFromCentreY =
          distanceFromCentreX * std::sin(angleInRadians) + distanceFromCentreY * std::cos(angleInRadians);
      double dy = newDistanceFromCentreY - distanceFromCentreY;
      componentShapes_[i]->move(dx, dy);
    }
  }

  Matrix CompositeShape::split() const
  {
    Matrix matrix;
    for (size_t i = 0; i < size_; ++i)
    {
      matrix.addShape(componentShapes_[i]);
    }
    return matrix;
  }
}

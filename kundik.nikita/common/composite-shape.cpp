#include "composite-shape.hpp"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <limits>

namespace kundik 
{
  CompositeShape::CompositeShape(const size_t capacity) :
    size_(0),
    capacity_(capacity),
    arrayShapes_(std::make_unique<std::shared_ptr<Shape>[]>(capacity))
  {}
  CompositeShape::CompositeShape(const kundik::CompositeShape& other) :
    size_(other.size_),
    capacity_(other.capacity_),
    arrayShapes_(std::make_unique<std::shared_ptr<Shape>[]>(other.capacity_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      arrayShapes_[i] = other.arrayShapes_[i];
    }
  }
  CompositeShape::CompositeShape(CompositeShape&& other) noexcept :
    size_(other.size_),
    capacity_(other.capacity_),
    arrayShapes_(std::move(other.arrayShapes_))
  {
    other.size_ = 0;
    other.capacity_ = 0;
  }
  CompositeShape& CompositeShape::operator=(const CompositeShape& other)
  {
    if (this == &other)
    {
      return *this;
    }
    std::unique_ptr<std::shared_ptr<Shape>[]> tempShapes(new std::shared_ptr<Shape>[other.capacity_]);
    for (size_t i = 0; i < other.size_; i++)
    {
      tempShapes[i] = other.arrayShapes_[i];
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    arrayShapes_ = std::move(tempShapes);
    return *this;
  }
  CompositeShape& CompositeShape::operator=(CompositeShape&& other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    arrayShapes_ = std::move(other.arrayShapes_);
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
  }
  std::shared_ptr<Shape>& CompositeShape::operator[](const size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Composite shape index must be less than shape size!");
    }
    return arrayShapes_[index];
  }
  size_t CompositeShape::getSize() const noexcept 
  {
    return size_;
  }
  void CompositeShape::addShape(const std::shared_ptr<Shape>& otherShape)
  {
    if (!otherShape)
    {
      throw std::invalid_argument("This shape is a null");
    }
    if (size_ == capacity_)
    {
      std::unique_ptr<std::shared_ptr<Shape>[]> tempShapes(new std::shared_ptr<Shape>[size_ * 2]);
      for (size_t i = 0; i < size_; i++)
      {
        tempShapes[i] = arrayShapes_[i];
      }
      capacity_ *= 2;
      arrayShapes_ = std::move(tempShapes);
    }
    arrayShapes_[size_++] = otherShape;
  }
  void CompositeShape::removeShape(const size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Shape index to remove must be less then shape size");
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      arrayShapes_[i] = arrayShapes_[i + 1];
    }
    arrayShapes_[size_] = nullptr;
    --size_;
  }
  double CompositeShape::getArea() const noexcept
  {
    double resultArea = 0;
    for (size_t i = 0; i < size_; ++i)
    {
      resultArea += arrayShapes_[i]->getArea();
    }
    return resultArea;
  }
  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return rectangle_t{ 0, 0, {0, 0} };
    }
    rectangle_t shape = arrayShapes_[0]->getFrameRect();
    double left = shape.pos.x - shape.width / 2;
    double right = shape.pos.x + shape.width / 2;
    double bottom = shape.pos.y - shape.height / 2;
    double up = shape.pos.y + shape.height / 2;
    for (size_t i = 1; i < size_; ++i)
    {
      shape = arrayShapes_[i]->getFrameRect();
      left = std::min(left, shape.pos.x - shape.width / 2);
      right = std::min(right, shape.pos.x + shape.width / 2);
      bottom = std::min(bottom, shape.pos.y - shape.height / 2);
      up = std::min(up, shape.pos.y + shape.height / 2);
    }
    double width = right - left;
    double height = up - bottom;
    return rectangle_t{ width, height, point_t{left + width / 2, bottom + height / 2} };
  }
  void CompositeShape::move(const point_t& position) noexcept
  {
    double changeX = position.x - getFrameRect().pos.x;
    double changeY = position.y - getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      arrayShapes_[i]->move(changeX, changeY);
    }
  }
  void CompositeShape::move(double changeX, double changeY) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      arrayShapes_[i]->move(changeX, changeY);
    }
  }
  void CompositeShape::scale(const double coefficent)
  {
    if (coefficent <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid coefficent scaling value in rectangle = ") += std::to_string(coefficent));
    }
    double centerX = getFrameRect().pos.x;
    double centerY = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      arrayShapes_[i]->scale(coefficent);
      double changeX = arrayShapes_[i]->getFrameRect().pos.x - centerX;
      double changeY = arrayShapes_[i]->getFrameRect().pos.y - centerY;
      arrayShapes_[i]->move(changeX * (coefficent - 1), changeY * (coefficent - 1));
    }
  }
  kundik::point_t CompositeShape::getCentrer() const noexcept
  {
    return getFrameRect().pos;
  }
}

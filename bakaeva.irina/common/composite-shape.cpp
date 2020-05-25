#include "composite-shape.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <limits>

namespace bakaeva
{
  CompositeShape::CompositeShape() :
    volume_(10),
    size_(0),
    shapes_(std::make_unique<shapePtr[]>(10))
  {}

  CompositeShape::CompositeShape(const size_t volume) :
    volume_(volume),
    size_(0),
    shapes_(std::make_unique<shapePtr[]>(volume))
  {}

  CompositeShape::CompositeShape(const bakaeva::CompositeShape &other) :
    volume_(other.volume_),
    size_(other.size_),
    shapes_(std::make_unique<shapePtr[]>(other.volume_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = other.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(bakaeva::CompositeShape &&other) noexcept :
    volume_(other.volume_),
    size_(other.size_),
    shapes_(std::move(other.shapes_))
  {
    other.volume_ = 0;
    other.size_ = 0;
    other.shapes_.reset();
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this == &other)
    {
      return *this;
    }
    shapeArray temp = std::make_unique<shapePtr[]>(other.volume_);
    for (size_t i = 0; i < other.size_; i++)
    {
      temp[i] = other.shapes_[i];
    }
    volume_ = other.volume_;
    size_ = other.size_;
    shapes_ = std::move(temp);
    return *this;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }

    volume_ = other.volume_;
    size_ = other.size_;
    shapes_ = std::move(other.shapes_);
    other.size_ = 0;
    other.volume_ = 0;
    other.shapes_.reset();
    return *this;
  }

  CompositeShape::shapePtr &CompositeShape::operator[](const size_t index) const
  {
    if (index >= size_ || size_ == 0)
    {
      throw std::out_of_range(std::string("Index of shape is out of range = ") += std::to_string(index));
    }
    return shapes_[index];
  }

  double CompositeShape::getArea() const noexcept
  {
    double totalArea = 0;
    for (size_t i = 0; i < size_; i++)
    {
      totalArea += shapes_[i]->getArea();
    }
    return totalArea;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0.0, 0.0, {0.0, 0.0}};
    }

    double left = std::numeric_limits<double>::max();
    double right = std::numeric_limits<double>::lowest();
    double top = std::numeric_limits<double>::lowest();
    double bottom = std::numeric_limits<double>::max();

    for (size_t i = 0; i < size_; i++)
    {
      const rectangle_t tempRect = shapes_[i]->getFrameRect();
      left = std::min(left, tempRect.pos.x - (tempRect.width / 2));
      right = std::max(right, tempRect.pos.x + (tempRect.width / 2));
      top = std::max(top, tempRect.pos.y + (tempRect.height / 2));
      bottom = std::min(bottom, tempRect.pos.y - (tempRect.height / 2));
    }

    double width = right - left;
    double height = top - bottom;
    return {width, height, {left + (width / 2), bottom + (height / 2)}};
  }

  void CompositeShape::move(const point_t &center) noexcept
  {
    this->move(center.x - this->getFrameRect().pos.x, center.y - this->getFrameRect().pos.y);
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::scale(const double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid coefficient value in composite shape = ")
          += std::to_string(coefficient));
    }

    const point_t centre = getFrameRect().pos;
    for (size_t i = 0; i < size_; i++)
    {
      const double deltaX = shapes_[i]->getFrameRect().pos.x - centre.x;
      const double deltaY = shapes_[i]->getFrameRect().pos.y - centre.y;
      shapes_[i]->move({centre.x + coefficient * deltaX, centre.y + coefficient * deltaY});
      shapes_[i]->scale(coefficient);
    }
  }

  void CompositeShape::addShape(const CompositeShape::shapePtr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Added shape pointer must not be null!");
    }

    if (volume_ == size_)
    {
      shapeArray tempArray(std::make_unique<shapePtr[]>(volume_ + 10));
      for (size_t i = 0; i < size_; i++)
      {
        tempArray[i] = shapes_[i];
      }
      volume_ += 10;
      shapes_ = std::move(tempArray);
    }
    shapes_[size_++] = shape;
  }

  void CompositeShape::removeShape(const size_t index)
  {
    if (index >= size_ || size_ == 0)
    {
      throw std::out_of_range(std::string("Index of shape is out of range = ") += std::to_string(index));
    }

    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[size_ - 1] = nullptr;
    size_--;
  }

  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  point_t CompositeShape::getCenter() const noexcept
  {
    return getFrameRect().pos;
  }

  void CompositeShape::printFrameRect() const
  {
    rectangle_t tempFrameRect = getFrameRect();
    std::cout << "Frame rectangle of composite shape: height = " << tempFrameRect.height
              << ", width = " << tempFrameRect.width << ", center = (" << tempFrameRect.pos.x
              << ", " << tempFrameRect.pos.y << ")\n";
  }

  void CompositeShape::printData() const
  {
    rectangle_t tempFrameRect = getFrameRect();
    std::cout << "Number of figures is " << size_ << '\n' << "Total area is " << getArea() << '\n'
              << "Composite shape's centre is (" << tempFrameRect.pos.x << ", " << tempFrameRect.pos.y << ")\n"
              << "Frame rectangle have width = " << tempFrameRect.width << " height = " << tempFrameRect.height << '\n';
  }
}

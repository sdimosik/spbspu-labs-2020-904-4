#include "composite-shape.hpp"
#include <string>
#include <stdexcept>
#include <cmath>
#include <algorithm>  

namespace starikevich
{
  CompositeShape::CompositeShape() noexcept :
    fullSize_(0),
    usedSize_(0),
    array_(nullptr)
  {}

  CompositeShape::CompositeShape(const size_t fullSize_) :
    fullSize_(fullSize_),
    usedSize_(0),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(fullSize_))
  {}

  CompositeShape::CompositeShape(const CompositeShape& array) :
    fullSize_(array.fullSize_),
    usedSize_(array.usedSize_),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(array.fullSize_))
  {
    for (size_t i = 0; i < usedSize_; i++)
    {
      array_[i] = array.array_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape&& array) noexcept :
    fullSize_(array.fullSize_),
    usedSize_(array.usedSize_),
    array_(std::move(array.array_))
  {
    array.fullSize_ = 0;
    array.usedSize_ = 0;
  }

  const std::shared_ptr<Shape>& CompositeShape::operator[](const size_t index) const
  {
    if (usedSize_ == 0 || index >= usedSize_)
    {
      throw std::out_of_range("The index of CompositeShape is outside of acceptable values. Index = " + std::to_string(index));
    }
    return array_[index];
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& array)
  {
    if (&array == this)
    {
      return *this;
    }
    arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(array.fullSize_);
    for (size_t i = 0; i < array.usedSize_; i++)
    {
      temp[i] = array.array_[i];
    }
    fullSize_ = array.fullSize_;
    usedSize_ = array.usedSize_;
    array_ = std::move(temp);
    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& array) noexcept
  {
    if (&array == this)
    {
      return *this;
    }
    fullSize_ = array.fullSize_;
    usedSize_ = array.usedSize_;
    array_ = std::move(array.array_);
    array.fullSize_ = 0;
    array.usedSize_ = 0;
    return *this;
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < usedSize_; i++)
    {
      array_[i]->move(x, y);
    }

  }

  void CompositeShape::move(const point_t& pos) noexcept
  {
    double shapesX = getPosition().x,
      shapesY = getPosition().y;
    for (size_t i = 0; i < usedSize_; i++)
    {
      array_[i]->move({ pos.x + (array_[i]->getPosition().x - shapesX), pos.y + (array_[i]->getPosition().y - shapesY) });
    }
  }

  starikevich::rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (usedSize_ == 0)
    {
      return { 0, 0, {0, 0} };
    }
    rectangle_t box = array_[0]->getFrameRect();
    double top = box.pos.y + box.height / 2;
    double bottom = box.pos.y - box.height / 2;
    double right = box.pos.x + box.width / 2;
    double left = box.pos.x - box.width / 2;
    for (size_t i = 0; i < usedSize_; i++)
    {
      box = array_[i]->getFrameRect();
      top = std::max(box.pos.y + box.height / 2, top);
      bottom = std::min(box.pos.y - box.height / 2, bottom);
      right = std::max(box.pos.x + box.width / 2, right);
      left = std::min(box.pos.x - box.width / 2, left);
    }
    return { (right - left), (top - bottom), {(left + (right - left) / 2), (bottom + (top - bottom) / 2)} };
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape>& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape of CompositeShape is nullptr.");
    }
    if (fullSize_ == 0)
    {
      arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(1);
      fullSize_ = 1;
      array_ = std::move(temp);
    }

    if (fullSize_ == usedSize_)
    {
      int newFullSize = fullSize_ * 2;
      arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(newFullSize);
      for (size_t i = 0; i < usedSize_; i++)
      {
        temp[i] = array_[i];
      }
      fullSize_ = newFullSize;
      array_ = std::move(temp);
    }
    array_[usedSize_] = shape;
    usedSize_++;
  }

  void CompositeShape::deleteShape(size_t index)
  {
    if (usedSize_ == 0 || index > (usedSize_ - 1))
    {
      throw std::out_of_range("The index of CompositeShape is outside of acceptable values. Index = " + std::to_string(index));
    }
    for (size_t i = index; i < usedSize_ - 1; i++)
    {
      array_[i] = array_[i + 1];
    }
    array_[usedSize_ - 1] = nullptr;
    usedSize_--;
  }

  size_t CompositeShape::getFullSize() const noexcept
  {
    return fullSize_;
  }

  size_t CompositeShape::getUsedSize() const noexcept
  {
    return usedSize_;
  }

  point_t CompositeShape::getPosition() const noexcept
  {
    return getFrameRect().pos;
  }

  double CompositeShape::getArea() const noexcept
  {
    double area = 0;
    for (size_t i = 0; i < usedSize_; i++)
    {
      area += array_[i]->getArea();
    }
    return area;
  }

  void CompositeShape::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient must be positive number. Coefficient = " + std::to_string(coefficient));
    }
    point_t pos1 = getPosition();
    double movingX = 0, movingY = 0;
    for (size_t i = 0; i < usedSize_; i++)
    {
      array_[i]->scale(coefficient);
      point_t posShape = array_[i]->getPosition();
      movingX = (posShape.x - pos1.x) * (coefficient - 1);
      movingY = (posShape.y - pos1.y) * (coefficient - 1);
      array_[i]->move(movingX, movingY);
    }
  }

  void CompositeShape::rotate(double angle) noexcept
  {
    double angle_radian = (angle * M_PI) / 180;
    point_t center = getPosition();
    for (size_t i = 0; i < usedSize_; i++)
    {
      point_t currentCenter = array_[i]->getPosition();
      double distanceX = currentCenter.x - center.x;
      double distanceY = currentCenter.y - center.y;
      const double dX = (distanceX * abs(cos(angle_radian))) - (distanceY * abs(sin(angle_radian)));
      const double dY = (distanceX * abs(sin(angle_radian))) + (distanceY * abs(cos(angle_radian)));
      array_[i]->move({ center.x + dX,center.y + dY });
      array_[i]->rotate(angle);
    }
  }
}

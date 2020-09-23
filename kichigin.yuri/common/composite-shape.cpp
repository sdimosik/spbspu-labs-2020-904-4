#include "composite-shape.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

kichigin::CompositeShape::CompositeShape() noexcept:
  fullSize_(0),
  currentSize_(0),
  array_(nullptr)
{}

kichigin::CompositeShape::CompositeShape(const unsigned int fullSize):
  fullSize_(fullSize),
  currentSize_(0),
  array_(new std::shared_ptr<kichigin::Shape>[fullSize_])
{}

kichigin::CompositeShape::CompositeShape(const CompositeShape & shape):
  fullSize_(shape.fullSize_),
  currentSize_(shape.currentSize_),
  array_(new std::shared_ptr<kichigin::Shape>[fullSize_])
{
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    array_[i] = shape.array_[i];
  }
}

kichigin::CompositeShape::CompositeShape(CompositeShape&& shape) noexcept:
  fullSize_(shape.fullSize_),
  currentSize_(shape.currentSize_),
  array_(std::move(shape.array_))
{
  shape.fullSize_ = 0;
  shape.currentSize_ = 0;
  shape.array_.reset();
}

std::shared_ptr<kichigin::Shape>& kichigin::CompositeShape::operator[](unsigned int index) const
{
  if (index > currentSize_ || currentSize_ == 0)
  {
    throw std::out_of_range(std::string("Out of range in CompositeShape, index = " + std::to_string(index)));
  }
  return array_[index];
}

kichigin::CompositeShape& kichigin::CompositeShape::operator=(const CompositeShape& shape)
{
  if (&shape == this)
  {
    return *this;
  }
  arrayType temp(nullptr);
  temp.reset(new std::shared_ptr<kichigin::Shape>[shape.fullSize_]);
  for (unsigned int i = 0; i < shape.currentSize_; i++)
  {
    temp[i] = shape.array_[i];
  }
  currentSize_ = shape.currentSize_;
  fullSize_ = shape.fullSize_;
  array_ = std::move(temp);
  return *this;
}

kichigin::CompositeShape& kichigin::CompositeShape::operator=(CompositeShape&& shape) noexcept
{
  if (&shape == this)
  {
    return *this;
  }
  fullSize_ = shape.fullSize_;
  currentSize_ = shape.currentSize_;
  array_ = std::move(shape.array_);
  shape.fullSize_ = 0;
  shape.currentSize_ = 0;
  shape.array_.reset();
  return *this;
}

void kichigin::CompositeShape::addShape(const std::shared_ptr<kichigin::Shape>& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Shape is nullptr");
  }
  if (fullSize_ == 0)
  {
    fullSize_ = 1;
    array_.reset(new std::shared_ptr<kichigin::Shape>[fullSize_]);
  }
  if (fullSize_ == currentSize_)
  {
    const int coefficient = 2;
    arrayType temp(new std::shared_ptr<kichigin::Shape>[fullSize_ * coefficient]);
    for (unsigned int i = 0; i < currentSize_; i++)
    {
      temp[i] = array_[i];
    }
    fullSize_ *= coefficient;
    array_ = std::move(temp);
  }
  array_[currentSize_] = shape;
  ++currentSize_;
}

void kichigin::CompositeShape::deleteShape(unsigned int index)
{
  if (index > currentSize_ || currentSize_ == 0)
  {
    throw std::out_of_range(std::string("Out of range in CompositeShape, index = " + std::to_string(index)));
  }
  for (unsigned int i = index + 1; i < currentSize_; i++)
  {
    array_[i - 1] = array_[i];
  }
  array_[currentSize_ - 1] = nullptr;
  --currentSize_;
}

unsigned int kichigin::CompositeShape::getFullSize() const noexcept
{
  return fullSize_;
}

unsigned int kichigin::CompositeShape::getCurrentSize() const noexcept
{
  return currentSize_;
}

double kichigin::CompositeShape::getArea() const noexcept
{
  double totalArea = 0.0;
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    totalArea += array_[i]->getArea();
  }
  return totalArea;
}

kichigin::rectangle_t kichigin::CompositeShape::getFrameRect() const noexcept
{
  if (currentSize_ == 0)
  {
    return rectangle_t{ 0, 0, {0, 0} };
  }
  rectangle_t currentRect = array_[0]->getFrameRect();
  double left = currentRect.pos.x - currentRect.width / 2;
  double right = currentRect.pos.x + currentRect.width / 2;
  double top = currentRect.pos.y + currentRect.height / 2;
  double bottom = currentRect.pos.y - currentRect.height / 2;
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    currentRect = array_[i]->getFrameRect();
    if ((currentRect.pos.x - currentRect.width / 2) < left)
    {
      left = currentRect.pos.x - currentRect.width / 2;
    }
    if ((currentRect.pos.x + currentRect.width / 2) > right)
    {
      right = currentRect.pos.x + currentRect.width / 2;
    }
    if ((currentRect.pos.y + currentRect.height / 2) > top)
    {
      top = currentRect.pos.y + currentRect.height / 2;
    }
    if ((currentRect.pos.y - currentRect.height / 2) < bottom)
    {
      bottom = currentRect.pos.y - currentRect.height / 2;
    }
  }
  return { (right - left), (top - bottom), {(left + (right - left) / 2), (bottom + (top - bottom) / 2)} };
}

void kichigin::CompositeShape::move(const point_t& point) noexcept
{
  kichigin::point_t prevPosition = this->getFrameRect().pos;
  double deltaX = point.x - prevPosition.x, deltaY = point.y - prevPosition.y;
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    array_[i]->move(deltaX, deltaY);
  }
}

void kichigin::CompositeShape::move(double x, double y) noexcept
{
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    array_[i]->move(x, y);
  }
}

void kichigin::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument(std::string("Coefficient of scale" + std::to_string(coefficient) + " must be positive"));
  }
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    array_[i]->scale(coefficient);
  }
}

void kichigin::CompositeShape::rotate(double angle) noexcept
{
  point_t centerPosition = getFrameRect().pos;
  for (unsigned int i = 0; i < currentSize_; i++)
  {
    array_[i]->rotate(angle);
    point_t currentPositoin = array_[i]->getFrameRect().pos;
    double y = (currentPositoin.x - centerPosition.x) * std::cos(angle * M_PI / 180)
        - (currentPositoin.y - centerPosition.y) * std::sin(angle * M_PI / 180) + centerPosition.x;
    double x = (currentPositoin.x - centerPosition.x) * std::sin(angle * M_PI / 180)
        - (currentPositoin.y - centerPosition.y) * std::cos(angle * M_PI / 180) + centerPosition.y;
    array_[i]->move(point_t{ x, y });
  }
}

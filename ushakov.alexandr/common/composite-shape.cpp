#include "composite-shape.hpp"

#include <limits>
#include <cmath>
#include <iostream>

const int FULL_CIRCLE = 180;

ushakov::CompositeShape::CompositeShape() :
  shapes_(nullptr),
  size_(0),
  capacity_(0)
{}

ushakov::CompositeShape::CompositeShape(size_t capacity) :
  shapes_(std::make_unique<std::shared_ptr<Shape>[]>(capacity)),
  size_(0),
  capacity_(capacity)
{}

ushakov::CompositeShape::CompositeShape(const ushakov::CompositeShape& compositeShape) noexcept:
  shapes_(std::make_unique<std::shared_ptr<Shape>[]>(compositeShape.capacity_)),
  size_(compositeShape.size_),
  capacity_(compositeShape.capacity_)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] = compositeShape.shapes_[i];
  }
}

ushakov::CompositeShape::CompositeShape(CompositeShape&& compositeShape) noexcept:
  shapes_(std::move(compositeShape.shapes_)),
  size_(compositeShape.size_),
  capacity_(compositeShape.capacity_)
{
  compositeShape.shapes_.reset();
  compositeShape.size_ = 0;
  compositeShape.capacity_ = 0;
}

ushakov::CompositeShape& ushakov::CompositeShape::operator=(const CompositeShape& compositeShape)
{
  if (this == &compositeShape)
  {
    return *this;
  }

  shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(compositeShape.size_);

  for (size_t i = 0; i < compositeShape.size_; i++)
  {
    shapes_[i] = compositeShape.shapes_[i];
  }

  size_ = compositeShape.size_;
  capacity_ = compositeShape.capacity_;

  return *this;
}

ushakov::CompositeShape& ushakov::CompositeShape::operator=(CompositeShape&& compositeShape) noexcept
{
  if (this == &compositeShape)
  {
    return *this;
  }

  shapes_ = std::move(compositeShape.shapes_);
  compositeShape.shapes_.reset();

  size_ = compositeShape.size_;
  compositeShape.size_ = 0;

  capacity_ = compositeShape.capacity_;
  compositeShape.capacity_ = 0;

  return *this;
}

std::shared_ptr<ushakov::Shape> ushakov::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape operator[] error: Index is out of range (" + std::to_string(index) + ')');
  }

  if (!shapes_[index])
  {
    throw std::invalid_argument("CompositeShape operator[] error: null pointer to shape at index " + std::to_string(index));
  }

  return shapes_[index];
}

void ushakov::CompositeShape::addShape(const std::shared_ptr<Shape>& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("CompositeShape addShape error: Invalid shape");
  }

  if (shape->getFrameRect().width == 0 || shape->getFrameRect().height == 0)
  {
    throw std::invalid_argument("CompositeShape addShape error: Empty shape");
  }

  if (capacity_ == 0)
  {
    capacity_ = 1;

    shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(capacity_);
  }
  else if (size_ == capacity_)
  {
    size_t incrementCapacity = capacity_ / 8;

    if (incrementCapacity == 0)
    {
      incrementCapacity++;
    }

    compositeShapePtr tmpShapes = std::make_unique<std::shared_ptr<Shape>[]>(capacity_ + incrementCapacity);

    for (size_t i = 0; i < size_; i++)
    {
      tmpShapes[i] = shapes_[i];
    }

    capacity_ = capacity_ + incrementCapacity;
    shapes_ = std::move(tmpShapes);
  }

  shapes_[size_++] = shape;
}

void ushakov::CompositeShape::removeShape(size_t index)
{
  if (index >= size_)
  {
    throw std::invalid_argument("CompositeShape removeShape error: Index is out of range("
          + std::to_string(index) + ')');
  }

  if (size_ < 1)
  {
    return;
  }

  for (size_t i = index; i < size_ - 1; i++)
  {
    shapes_[i] = shapes_[i + 1];
  }

  shapes_[--size_] = nullptr;
}

void ushakov::CompositeShape::move(const point_t& newPosition) noexcept
{
  double xAxis = newPosition.x - getFrameRect().pos.x;
  double yAxis = newPosition.y - getFrameRect().pos.y;

  for (size_t i = 0; i < size_; i++)
  {
    if (!shapes_[i])
    {
      continue;
    }

    shapes_[i]->move(xAxis, yAxis);
  }
}

void ushakov::CompositeShape::move(double xAxis, double yAxis) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    if (!shapes_[i])
    {
      continue;
    }

    shapes_[i]->move(xAxis, yAxis);
  }
}

void ushakov::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("CompositeShape scale error: Invalid coefficient of scale, it must be positive("
          + std::to_string(coefficient) + ')');
  }

  const point_t position = getPosition();

  for (size_t i = 0; i < size_; i++)
  {
    if (!shapes_[i])
    {
      continue;
    }

    shapes_[i]->scale(coefficient);

    double xAxis = shapes_[i]->getFrameRect().pos.x - position.x;
    double yAxis = shapes_[i]->getFrameRect().pos.y - position.y;

    shapes_[i]->move(xAxis * (coefficient - 1), yAxis * (coefficient - 1));
  }
}

void ushakov::CompositeShape::rotate(double angle) noexcept
{
  const double angleInRadians = angle * M_PI / FULL_CIRCLE;
  const point_t position = getPosition();

  for (size_t i = 0; i < size_; i++)
  {
    if (!shapes_[i])
    {
      continue;
    }

    const point_t currentPosition = shapes_[i]->getPosition();

    double distanceX = currentPosition.x - position.x;
    double distanceY = currentPosition.y - position.y;

    const double xAxis = (distanceX * std::abs(std::cos(angleInRadians)))
        - (distanceY * std::abs(std::sin(angleInRadians)));
    const double yAxis = (distanceX * std::abs(std::sin(angleInRadians)))
        + (distanceY * std::abs(std::cos(angleInRadians)));

    shapes_[i]->move({position.x + xAxis, position.y + yAxis});
    shapes_[i]->rotate(angle);
  }
}

ushakov::Matrix ushakov::CompositeShape::divide() const
{
  Matrix matrix;

  for (size_t i = 0; i < size_; ++i)
  {
    if (!shapes_[i])
    {
      continue;
    }

    matrix.addShape(shapes_[i]);
  }

  return matrix;
}

size_t ushakov::CompositeShape::getSize() const noexcept
{
  return size_;
}

double ushakov::CompositeShape::getArea() const noexcept
{
  double area = 0;

  for (size_t i = 0; i < size_; i++)
  {
    if (!shapes_[i])
    {
      continue;
    }

    area += shapes_[i]->getArea();
  }

  return area;
}

ushakov::rectangle_t ushakov::CompositeShape::getFrameRect() const noexcept
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
    if (!shapes_[i])
    {
      continue;
    }

    const rectangle_t tmpRectangle = shapes_[i]->getFrameRect();

    left = std::min(left, tmpRectangle.pos.x - tmpRectangle.width / 2);
    right = std::max(right, tmpRectangle.pos.x + tmpRectangle.width / 2);
    top = std::max(top, tmpRectangle.pos.y + tmpRectangle.height / 2);
    bottom = std::min(bottom, tmpRectangle.pos.y - tmpRectangle.height / 2);
  }

  return rectangle_t{right - left, top - bottom,left + (right - left) / 2, bottom + (top - bottom) / 2};
}

ushakov::point_t ushakov::CompositeShape::getPosition() const noexcept
{
  return getFrameRect().pos;
}

void ushakov::CompositeShape::print() const noexcept
{
  std::cout << "Composite shape" << std::endl;

  for (size_t i = 0; i < size_; i++)
  {
    if (!shapes_[i])
    {
      continue;
    }

    std::cout << "  Shape " << i << " is: ";

    shapes_[i]->print();

    std::cout << std::endl;
  }

  std::cout << "  total composite shape area: " << getArea() << std::endl;
  std::cout << "  composite shape position: x = " << getPosition().x << ", y = " << getPosition().y << std::endl;
}

void ushakov::CompositeShape::printFrameRectangle() const noexcept
{
  rectangle_t rectangle = getFrameRect();

  std::cout << "Frame rectangle for this shape:" << std::endl;
  std::cout << "  height = " << rectangle.height << ",  width = " << rectangle.width << std::endl;
  std::cout << "  position: x = " << rectangle.pos.x << ", y = " << rectangle.pos.y << std::endl;
}

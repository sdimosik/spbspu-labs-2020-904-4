#include "composite-shape.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <limits>
#include <cmath>

namespace meshcheryakov
{
  const double HALF_CIRCLE = 180;

  CompositeShape::CompositeShape() :
      size_(0),
      space_(0),
      shapes_(nullptr)
  {}

  CompositeShape::CompositeShape(size_t space) :
      size_(0),
      space_(space),
      shapes_(std::make_unique<std::shared_ptr<Shape>[]>(space))
  {}

  CompositeShape::CompositeShape(const meshcheryakov::CompositeShape &other) :
      size_(other.size_),
      space_(other.space_),
      shapes_(std::make_unique<std::shared_ptr<Shape>[]>(other.space_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = other.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(meshcheryakov::CompositeShape &&other) noexcept :
      size_(other.size_),
      space_(other.space_),
      shapes_(std::move(other.shapes_))
  {
    other.size_ = 0;
    other.space_ = 0;
    other.shapes_.reset();
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this == &other)
    {
      return *this;
    }
    shapeArray tmp = std::make_unique<std::shared_ptr<Shape>[]>(other.space_);
    for (size_t i = 0; i < other.size_; i++)
    {
      tmp[i] = other.shapes_[i];
    }
    size_ = other.size_;
    space_ = other.space_;
    shapes_ = std::move(tmp);
    return *this;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    size_ = other.size_;
    space_ = other.space_;
    shapes_ = std::move(other.shapes_);
    other.size_ = 0;
    other.space_ = 0;
    other.shapes_.reset();
    return *this;
  }

  std::shared_ptr<Shape> &CompositeShape::operator[](size_t index)
  {
    if (index >= size_)
    {
      throw (std::out_of_range(
          "The shape index cannot be larger than the size. Invalid index = " + std::to_string(index)));
    }
    return shapes_[index];
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

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0.0, 0.0, {0.0, 0.0}};
    }

    double rightX = std::numeric_limits<double>::lowest();
    double leftX = std::numeric_limits<double>::max();
    double topY = std::numeric_limits<double>::lowest();
    double bottomY = std::numeric_limits<double>::max();

    for (size_t i = 0; i < size_; i++)
    {
      const rectangle_t rect = shapes_[i]->getFrameRect();

      rightX = std::max(rightX, rect.pos.x + (rect.width / 2));
      leftX = std::min(leftX, rect.pos.x - (rect.width / 2));
      topY = std::max(topY, rect.pos.y + (rect.height / 2));
      bottomY = std::min(bottomY, rect.pos.y - (rect.height / 2));
    }

    return {rightX - leftX, topY - bottomY, {((rightX + leftX) / 2), ((topY + bottomY) / 2)}};
  }

  void CompositeShape::move(double dx, double dy) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(dx, dy);
    }
  }

  void CompositeShape::move(const meshcheryakov::point_t &point) noexcept
  {
    rectangle_t frameRect = getFrameRect();
    move(point.x - frameRect.pos.x, point.y - frameRect.pos.y);
  }

  void CompositeShape::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument(
          "Coefficient should not be negative. Invalid coefficient = " + std::to_string(coefficient));
    }
    double centreX = getFrameRect().pos.x;
    double centreY = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(coefficient);
      double distanceX = shapes_[i]->getFrameRect().pos.x - centreX;
      double distanceY = shapes_[i]->getFrameRect().pos.y - centreY;
      shapes_[i]->move(distanceX * coefficient, distanceY * coefficient);
    }
  }

  point_t CompositeShape::getPosition() const noexcept
  {
    return getFrameRect().pos;
  }

  int CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Error. Shape must not be empty");
    }
    if (space_ == 0)
    {
      shapes_.reset(new std::shared_ptr<Shape>[1]);
      space_++;
    }
    if (size_ == space_)
    {
      shapeArray tmp(std::make_unique<std::shared_ptr<Shape>[]>(space_ = std::max(space_ * 2, std::size_t(1))));
      for (size_t i = 0; i < size_; i++)
      {
        tmp[i] = shapes_[i];
      }
      shapes_ = std::move(tmp);
    }
    shapes_[size_++] = shape;
  }

  void CompositeShape::removeShape(size_t index)
  {
    if (size_ <= index || size_ == 0)
    {
      throw std::out_of_range(
          "The shape index cannot be larger than the size. Invalid index = " + std::to_string(index));
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[size_ - 1] = nullptr;
    size_--;
  }

  void CompositeShape::rotate(const double angle) noexcept
  {
    double angleRad = angle * M_PI / HALF_CIRCLE;
    point_t position = getPosition();
    for (size_t i = 0; i < size_; i++)
    {
      double distanceX = shapes_[i]->getPosition().x - position.x;
      double distanceY = shapes_[i]->getPosition().y - position.y;
      shapes_[i]->move(position.x + (distanceX * std::abs(cos(angleRad))) - (distanceY * std::abs(sin(angleRad))),
                       position.y + (distanceX * std::abs(sin(angleRad))) + (distanceY * std::abs(cos(angleRad))));
      shapes_[i]->rotate(angle);
    }
  }

  Matrix CompositeShape::matrixLayering() const
  {
    Matrix matrix;
    for (size_t i = 0; i < size_; i++)
    {
      matrix.addShape(shapes_[i]);
    }
    return matrix;
  }

}

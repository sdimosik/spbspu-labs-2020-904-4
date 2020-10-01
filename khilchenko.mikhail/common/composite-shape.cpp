#include "composite-shape.hpp"

#define _USE_MATH_DEFINES

#include <exception>
#include <string>
#include <cmath>

namespace khilchenko
{
  const double halfCircle = 180;

  CompositeShape::CompositeShape() noexcept:
    size_(0),
    amount_(0),
    shapes_(nullptr)
  {}

  CompositeShape::CompositeShape(size_t size):
    size_(size),
    amount_(0),
    shapes_(new std::shared_ptr<Shape>[size])
  {}

  CompositeShape::CompositeShape(const CompositeShape& shapes):
    size_(shapes.size_),
    amount_(shapes.amount_),
    shapes_(new std::shared_ptr<Shape>[shapes.size_])
  {
    for (size_t i = 0; i < amount_; i++)
    {
      shapes_[i] = shapes.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape &&shapes) noexcept:
    size_(shapes.size_),
    amount_(shapes.amount_),
    shapes_(std::move(shapes.shapes_))
  {
    shapes.size_ = 0;
    shapes.shapes_.reset();
    shapes.amount_ = 0;
  }

  std::shared_ptr<Shape>& CompositeShape::operator[](size_t index) const
  {
    if(index >= amount_)
    {
      throw std::out_of_range("Index out of bound. Invalid index: " + std::to_string(index));
    }
    return shapes_[index];
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& shapes)
  {
    if (&shapes == this)
    {
      return *this;
    } 
    arrayPtr temp(std::make_unique<std::shared_ptr<Shape>[]>(shapes.size_));
    for (size_t i = 0; i < shapes.amount_; i++)
    {
      temp[i] = shapes.shapes_[i];
    }
    size_ = shapes.size_;
    amount_ = shapes.amount_;
    shapes_ = std::move(temp);
    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& shapes) noexcept
  {
    if(&shapes == this)
    {
      return *this;
    }
    size_ = shapes.size_;
    amount_ = shapes.amount_;
    shapes_.reset();
    shapes_ = std::move(shapes.shapes_);
    shapes.size_ = 0;
    shapes.amount_ = 0;
    shapes.shapes_ = nullptr;
    return *this;
  }

  double CompositeShape::getArea() const noexcept
  {
    double result = 0;
    for(size_t i = 0; i < amount_; i++)
    {
      result += shapes_[i]->getArea();
    }
    return result;
  }

  rectangle_t CompositeShape::getFrameRect() const
  {
    if(amount_ == 0)
    {
      throw std::logic_error("CompositeShape object is not initialized.");
    }
    double upperLimit = shapes_[0]->getCenter().y + (shapes_[0]->getFrameRect().height)/2;
    double lowerLimit = shapes_[0]->getCenter().y - (shapes_[0]->getFrameRect().height)/2;
    double rightLimit = shapes_[0]->getCenter().x + (shapes_[0]->getFrameRect().width)/2;
    double leftLimit = shapes_[0]->getCenter().x - (shapes_[0]->getFrameRect().width)/2;

    for(size_t i = 1; i < amount_; i++)
    {
      double currentUpperLimit = shapes_[i]->getCenter().y + (shapes_[i]->getFrameRect().height)/2;
      double currentLowerLimit = shapes_[i]->getCenter().y - (shapes_[i]->getFrameRect().height)/2;
      double currentRightLimit = shapes_[i]->getCenter().x + (shapes_[i]->getFrameRect().width)/2;
      double currentLeftLimit = shapes_[i]->getCenter().x - (shapes_[i]->getFrameRect().width)/2;
      if(currentUpperLimit > upperLimit)
      {
        upperLimit = currentUpperLimit;
      }
      if(currentLowerLimit < lowerLimit)
      {
        lowerLimit = currentLowerLimit;
      }
      if(currentRightLimit > rightLimit)
      {
        rightLimit = currentRightLimit;
      }
      if(currentLeftLimit < leftLimit)
      {
        leftLimit = currentLeftLimit;
      }
    }
    return rectangle_t{{(leftLimit + rightLimit) / 2, (upperLimit + lowerLimit) / 2}, (rightLimit - leftLimit), (upperLimit - lowerLimit)};
  }

  void CompositeShape::move(const point_t &newPos) noexcept
  {
    double currentX = getFrameRect().pos.x;
    double currentY = getFrameRect().pos.y;
    double deltaX = newPos.x - currentX;
    double deltaY = newPos.y - currentY;
    move(deltaX, deltaY);
  }

  void CompositeShape::move(double x, double y) noexcept
  {
    for(size_t i = 0; i < amount_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }

  point_t CompositeShape::getCenter() const noexcept
  {
    return getFrameRect().pos;
  }

  void CompositeShape::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient must be a positive number. Invalid coefficient: " + std::to_string(coefficient));
    }
    double centerX = getFrameRect().pos.x;
    double centerY = getFrameRect().pos.y;
    for(size_t i = 0; i < amount_; i++)
    {
      shapes_[i]->scale(coefficient);
      double deltaX = shapes_[i]->getCenter().x - centerX;
      double deltaY = shapes_[i]->getCenter().y - centerY;
      shapes_[i]->move(deltaX * coefficient, deltaY * coefficient);
    }
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape>& shape)
  {
    if(shape == nullptr)
    {
      throw std::invalid_argument("Shape is nullptr");
    }
    if(size_ == 0)
    {
      shapes_.reset(new std::shared_ptr<Shape>[1]);
      size_ = 1;
      amount_ = 0;
    }
    else if(amount_ == size_)
    {
      arrayPtr temp(std::make_unique<std::shared_ptr<Shape>[]>(size_ * 2));
      for(size_t i = 0; i < amount_; i++)
      {
        temp[i] = shapes_[i];
      }
      shapes_ = std::move(temp);
      size_ *= 2;
    }
    shapes_[amount_] = shape;
    amount_++;
  }

  void CompositeShape::removeShape(size_t index)
  {
    if(index >= amount_)
    {
      throw std::out_of_range("Index out of bound. Invalid index: " + std::to_string(index));
    }
    for(size_t i =  index; i < amount_ - 1; i++)
    {
      shapes_[i] = shapes_[i+1];
    }
    amount_--;
    shapes_[amount_] = nullptr;
  }

  int CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  int CompositeShape::getAmount() const noexcept
  {
    return amount_;
  }

  void CompositeShape::rotate(double angle) noexcept
  {
    double angleInRad = angle * M_PI / halfCircle;
    for(size_t i = 0; i < amount_; i++)
    {
      shapes_[i]->rotate(angle);
      shapes_[i]->move((getCenter().x - shapes_[i]->getCenter().x) * cos(angleInRad),
          (getCenter().y - shapes_[i]->getCenter().y) * sin(angleInRad));
    }
  }

  Matrix CompositeShape::getLayerMatrix()
  {
    Matrix result;
    for(size_t i = 0; i < amount_; i++)
    {
      result.addShape(shapes_[i]);
    }
    return result;
  }
}

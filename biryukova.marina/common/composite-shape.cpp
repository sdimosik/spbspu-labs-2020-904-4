#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

namespace biryukova
{
  CompositeShape::CompositeShape() :
    size_(0),
    space_(0),
    shapes_(nullptr)
  {}

  CompositeShape::CompositeShape(size_t space) :
    size_(0),
    space_(space),
    shapes_(std::make_unique<shapePtr[]>(space))
  {}

  CompositeShape::CompositeShape(const CompositeShape& cs) :
    size_(cs.size_),
    space_(cs.space_),
    shapes_(std::make_unique<shapePtr[]>(cs.size_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = cs.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape&& cs) noexcept:
    size_(cs.size_),
    space_(cs.space_),
    shapes_(std::move(cs.shapes_))
  {
    cs.space_ = 0;
    cs.size_ = 0;
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& cs)
  {
    if (this != &cs)
    {
      shapes_.reset(new shapePtr[cs.space_]);
      size_ = cs.size_;
      space_ = cs.space_;
      for (size_t i = 0; i < size_; i++)
      {
        shapes_[i] = cs.shapes_[i];
      }
    }
    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& cs) noexcept
  {
    if (this != &cs)
    {
      space_ = cs.space_;
      size_ = cs.size_;
      shapes_ = std::move(cs.shapes_);
      cs.space_ = 0;
      cs.size_ = 0;
    }
    return *this;
  }

  void CompositeShape::insert(const shapePtr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Transmitting shape is nullptr");
    }
    if (space_ == 0)
    {
      shapes_.reset(new shapePtr[1]);
      space_++;
    }
    if (size_ == space_)
    {
      shapesArray temp(std::make_unique<shapePtr[]>(space_ * 2));
      for (size_t i = 0; i < size_; i++)
      {
        temp[i] = shapes_[i];
      }
      space_ *= 2;
      shapes_ = std::move(temp);
    }
    shapes_[size_] = shape;
    size_++;
  }

  void CompositeShape::remove(size_t index)
  {
    if (index > size_ - 1 || size_ == 0)
    {
      throw std::out_of_range("Index of deleted element is invalid. Invalid index: "
          + std::to_string(index));
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[size_ - 1] = nullptr;
    size_--;
  }

  int CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  CompositeShape::shapePtr& CompositeShape::operator[](size_t index) const
  {
    if (index > size_ - 1 || size_ == 0)
    {
      throw std::out_of_range("Index is invalid. Invalid index: "
          + std::to_string(index));
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

  biryukova::rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0, 0, {0, 0}};
    }
    biryukova::rectangle_t rect = shapes_[0]->getFrameRect();
    double leftX = rect.pos.x - rect.width / 2;
    double rightX = rect.pos.x + rect.width / 2;
    double bottomY = rect.pos.y - rect.height / 2;
    double topY = rect.pos.y + rect.height / 2;
    for (size_t i = 1; i < size_; i++)
    {
      rect = shapes_[i]->getFrameRect();
      if ((rect.pos.x - rect.width / 2) < leftX)
      {
        leftX = rect.pos.x - rect.width / 2;
      }
      if ((rect.pos.x + rect.width / 2) > rightX)
      {
        rightX = rect.pos.x + rect.width / 2;
      }
      if ((rect.pos.y - rect.height / 2) < bottomY)
      {
        bottomY = rect.pos.y - rect.height / 2;
      }
      if ((rect.pos.y + rect.height / 2) > topY)
      {
        topY = rect.pos.y + rect.height / 2;
      }
    }
    return {rightX - leftX, topY - bottomY, {(rightX + leftX) / 2, (topY + bottomY) / 2}};
  }

  void CompositeShape::move(const biryukova::point_t& point) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(point);
    }
  }

  void CompositeShape::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::print() const
  {
    for (size_t i = 0; i < size_; i++)
    {
      std::cout << "Shape " << i << " is: ";
      shapes_[i]->print();
    }
  }

  void CompositeShape::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive. Invalid coefficient: "
          + std::to_string(coefficient));
    }
    point_t centreOfShapes = getCentre();
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(coefficient);
      double distanceToCentreX = shapes_[i]->getFrameRect().pos.x - centreOfShapes.x;
      double distanceToCentreY = shapes_[i]->getFrameRect().pos.y - centreOfShapes.y;
      shapes_[i]->move(distanceToCentreX * (coefficient - 1), distanceToCentreY * (coefficient - 1));
    }
  }

  point_t CompositeShape::getCentre() const noexcept
  {
    return getFrameRect().pos;
  }
}

#include "composite-shape.hpp"
#include <iostream>
#include <exception>
#include <algorithm>

namespace spasoevich
{
  CompositeShape::CompositeShape() :
    shapeCount_(0),
    size_(0),
    arrayOfShapes_(nullptr)
  {} 

  CompositeShape::CompositeShape(const CompositeShape& copyShape) :
    shapeCount_(copyShape.shapeCount_),
    size_(copyShape.size_),
    arrayOfShapes_(std::make_unique<shape_ptr[]>(copyShape.shapeCount_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      arrayOfShapes_[i] = copyShape.arrayOfShapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape&& moveShape) noexcept :
    shapeCount_(moveShape.shapeCount_),
    size_(moveShape.size_),
    arrayOfShapes_(std::move((moveShape.arrayOfShapes_)))
  {
    moveShape.shapeCount_ = 0;
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& copy)
  {
    if (this == &copy)
    {
      return *this;
    }

    shape_array tempArray = std::make_unique<shape_ptr[]>(copy.shapeCount_);
    for (size_t i = 0; i < size_; i++)
    {
      tempArray[i] = copy.arrayOfShapes_[i];
    }
    shapeCount_ = copy.shapeCount_;
    size_ = copy.size_;
    arrayOfShapes_ = std::move(tempArray);
    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& move) noexcept
  {
    if (this != &move)
    {
      shapeCount_ = move.shapeCount_;
      size_ = move.size_;
      arrayOfShapes_ = std::move(move.arrayOfShapes_);
    }
    return *this;
  }

  CompositeShape::shape_ptr CompositeShape::operator[](size_t index) const
  {
    if (index >= size_ || size_==0)
    {
      throw std::out_of_range("Index is out of range.\n");
    }
    return arrayOfShapes_[index];
  }

  double CompositeShape::getArea() const noexcept
  {
    double fullArea = 0.0;
    for (size_t i = 0; i < size_; i++)
    {
      fullArea = fullArea + arrayOfShapes_[i]->getArea();
    }
    return fullArea;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return { { 0.0, 0.0 }, 0.0, 0.0 };
    }

    rectangle_t tempFrameRect = arrayOfShapes_[0]->getFrameRect();

    double minX = tempFrameRect.pos.x - tempFrameRect.width / 2;
    double maxX = tempFrameRect.pos.x + tempFrameRect.width / 2;
    double minY = tempFrameRect.pos.y - tempFrameRect.height / 2;
    double maxY = tempFrameRect.pos.y + tempFrameRect.height / 2;

    for (size_t i = 1; i < size_; i++)
    {
      tempFrameRect = arrayOfShapes_[i]->getFrameRect();

      double tempValue = tempFrameRect.pos.x - tempFrameRect.width / 2;
      minX = std::min(tempValue, minX);

      tempValue = tempFrameRect.pos.x + tempFrameRect.width / 2;
      maxX = std::max(tempValue, maxX);

      tempValue = tempFrameRect.pos.y - tempFrameRect.height / 2;
      minY = std::min(tempValue, minY);

      tempValue = tempFrameRect.pos.y + tempFrameRect.height / 2;
      maxY = std::max(tempValue, maxY);
    }

    return { { (minX + maxX) / 2, (minY + maxY) / 2 }, maxX - minX, maxY - minY };
  }

  void CompositeShape::move(const double dx, const double dy) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      arrayOfShapes_[i]->move(dx, dy);
    }
  }

  void CompositeShape::move(const point_t& p) noexcept
  {
    const double dX = p.x - getFrameRect().pos.x;
    const double dY = p.y - getFrameRect().pos.y;
    move(dX, dY);
  }

  void CompositeShape::scale(const double coefficient)
  {
    if (coefficient <= 0.0)
    {
      std::invalid_argument("Coefficient can't be less or equal to zero.\n");
    }

    const point_t center = getFrameRect().pos;

    for (size_t i = 0; i < size_; i++)
    {
      const double dx = arrayOfShapes_[i]->getFrameRect().pos.x - center.x;
      const double dy = arrayOfShapes_[i]->getFrameRect().pos.y - center.y;
      arrayOfShapes_[i]->move({ center.x + dx * coefficient, center.y + dy * coefficient });
      arrayOfShapes_[i]->scale(coefficient);
    }
  }

  void CompositeShape::addShape(shape_ptr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape pointer can't be null pointer.\n");
    }

    if (shapeCount_ == size_)
    {
      shape_array tempArray(std::make_unique<shape_ptr[]>(shapeCount_ + 10));
      for (size_t i = 0; i < size_; i++)
      {
        tempArray[i] = arrayOfShapes_[i];
      }
      shapeCount_+=10;
      arrayOfShapes_ = std::move(tempArray);
    }
    arrayOfShapes_[size_++] = shape;
  }

  void CompositeShape::removeShape(size_t index)
  {
    if ((index >= size_) || (size_==0))
    {
      throw std::out_of_range("Index is out of range.\n");
    }

    for (size_t i = index; i < (size_ - 1); i++)
    {
      arrayOfShapes_[i] = arrayOfShapes_[i + 1];
    }
    arrayOfShapes_[size_ - 1] = nullptr;
    size_--;
  }

  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }

  void CompositeShape::printCompositeShapeData() noexcept
  {
    spasoevich::rectangle_t shape = getFrameRect();
    std::cout << "\nComposite shape parameters:\n"
              << "Center: (" << getFrameRect().pos.x << "," << getFrameRect().pos.y << ")\n"
              << "Area: " << getArea() << "\n"
              << "Amount of shapes: " << shapeCount_ << "\n"
              << "Frame rectangle width: " << shape.width << "\n"
              << "Frame rectangle height: " << shape.height << "\n\n";
  }
}

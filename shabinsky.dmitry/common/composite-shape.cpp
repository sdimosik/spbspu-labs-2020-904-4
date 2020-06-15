#include <iostream>
#include <math.h>
#include "composite-shape.hpp"

namespace shabinsky
{
  shabinsky::CompositeShape::CompositeShape() noexcept:
    size_(0),
    length_(0),
    composition_(nullptr)
  {}
  
  CompositeShape::CompositeShape(size_t length) :
    size_(0),
    length_(length),
    composition_(new std::shared_ptr<Shape>[length])
  {}
  
  CompositeShape::CompositeShape(const CompositeShape &compositeShape) :
    size_(compositeShape.size_),
    length_(compositeShape.length_),
    composition_(new std::shared_ptr<Shape>[compositeShape.length_])
  {
    for (size_t i = 0; i < compositeShape.size_; ++i)
    {
      composition_[i] = compositeShape.composition_[i];
    }
  }
  
  CompositeShape::CompositeShape(CompositeShape &&compositeShape) noexcept:
    size_(compositeShape.size_),
    length_(compositeShape.length_),
    composition_(std::move(compositeShape.composition_))
  {
    compositeShape.size_ = 0;
    compositeShape.length_ = 0;
    compositeShape.composition_.reset();
  }
  
  void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape is nullptr");
    }
    if (size_ == length_)
    {
      compositionPtr tempComposition(new std::shared_ptr<Shape>[length_ + 1]);
      for (size_t i = 0; i < length_; ++i)
      {
        tempComposition[i] = composition_[i];
      }
      length_++;
      composition_ = std::move(tempComposition);
    }
    composition_[size_] = shape;
    size_++;
  }
  
  void CompositeShape::deleteShape(size_t index)
  {
    if (size_ == 0 || index > (size_ - 1))
    {
      throw std::out_of_range("Index is incorrect. Index = " + std::to_string(index));
    }
    size_--;
    for (size_t i = index; i < size_; ++i)
    {
      composition_[i] = composition_[i + 1];
    }
    composition_[size_] = nullptr;
    
  }
  
  double CompositeShape::getArea() const noexcept
  {
    double area = 0;
    for (size_t i = 0; i < size_; ++i)
    {
      area += composition_[i]->getArea();
    }
    return area;
  }
  
  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0, 0, {0, 0}};
    }
    rectangle_t frame = composition_[0]->getFrameRect();
    double left = frame.pos.x - frame.width / 2;
    double right = frame.pos.x + frame.width / 2;
    double top = frame.pos.y + frame.height / 2;
    double lower = frame.pos.y - frame.height / 2;
    for (size_t i = 1; i < size_; ++i)
    {
      frame = composition_[i]->getFrameRect();
      
      left = std::min(left, frame.pos.x - frame.width / 2);
      right = std::max(right, frame.pos.x + frame.width / 2);
      top = std::max(top, frame.pos.y + frame.height / 2);
      lower = std::min(lower, frame.pos.y - frame.height / 2);
    }
    return {(right - left), (top - lower), {(left + (right - left) / 2), (lower + (top - lower) / 2)}};
  }
  
  void CompositeShape::move(const point_t &point) noexcept
  {
    for (size_t i = 0; i < size_; ++i)
    {
      composition_[i]->move(point);
    }
  }
  
  void CompositeShape::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < size_; ++i)
    {
      composition_[i]->move(x, y);
    }
  }
  
  void CompositeShape::show(std::ostream &out)
  {
    try
    {
      out.exceptions(std::ostream::failbit);
      out << "Composition:\n";
      for (size_t i = 0; i < size_; ++i)
      {
        composition_[i]->show(out);
      }
    } catch (const std::ios_base::failure &f)
    {
      std::cerr << "Caught error: " << f.what() << '\n';
    }
  }
  
  void CompositeShape::scale(double coefficient)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      composition_[i]->scale(coefficient);
    }
  }
  
  std::shared_ptr<Shape> &CompositeShape::operator[](size_t index) const
  {
    if (size_ == 0 || index > size_ - 1)
    {
      throw std::out_of_range(std::string("CompositeShape out of range. Index = " + std::to_string(index)));
    }
    return composition_[index];
  }
  
  size_t CompositeShape::getSize() const noexcept
  {
    return size_;
  }
  
  size_t CompositeShape::getLength() const noexcept
  {
    return length_;
  }
  
  void CompositeShape::rotate(double angle)
  {
    double angleRadian = (angle * M_PI) / 180;
    point_t center = getFrameRect().pos;
    
    for (size_t i = 0; i < size_; ++i)
    {
      composition_[i]->rotate(angle);
      
      point_t centerShape = composition_[i]->getFrameRect().pos;
      double deltaX = centerShape.x - center.x;
      double deltaY = centerShape.y - center.y;
      double distanceX = (deltaX * abs(cos(angleRadian)) - deltaY * abs(sin(angleRadian)));
      double distanceY = (deltaX * abs(sin(angleRadian)) + deltaY * abs(cos(angleRadian)));
      composition_[i]->move({center.x + distanceX, center.y + distanceY});
    }
  }
  
  Matrix CompositeShape::makeMatrix() const
  {
    Matrix matrix;
    for(size_t i = 0; i < size_; ++i)
    {
      matrix.add(composition_[i]);
    }
    return matrix;
  }
}


#include <memory>
#include <stdexcept>
#include <cmath>
#include "composite-shape.hpp"
#include "specs.hpp"

namespace pashnin
{
  
  using arrShape = std::unique_ptr<CompositeShape::shapePtr[]>;
  
  CompositeShape::CompositeShape() :
    shapes_(std::make_unique<shapePtr[]>(1)),
    capacity_(1),
    size_(0)
  {}
  
  CompositeShape::CompositeShape(const size_t capacity) :
    shapes_(std::make_unique<CompositeShape::shapePtr[]>(capacity)),
    capacity_(capacity),
    size_(0)
  {}
  
  CompositeShape::CompositeShape(const pashnin::CompositeShape &other) :
    shapes_(std::make_unique<CompositeShape::shapePtr[]>(other.capacity_)),
    capacity_(other.capacity_),
    size_(other.size_)
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = other.shapes_[i];
    }
  }
  
  CompositeShape::CompositeShape(CompositeShape &&other) noexcept:
    shapes_(std::move(other.shapes_)),
    capacity_(other.capacity_),
    size_(other.size_)
  {
    other.shapes_.reset();
    other.size_ = 0;
    other.capacity_ = 0;
  }
  
  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this == &other)
    {
      return *this;
    }
    arrShape tmpShapes(new CompositeShape::shapePtr[other.size_]);
    for (size_t i = 0; i < other.size_; i++)
    {
      tmpShapes[i] = other.shapes_[i];
    }
    shapes_ = std::move(tmpShapes);
    capacity_ = other.capacity_;
    size_ = other.size_;
    return *this;
  }
  
  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    shapes_ = std::move(other.shapes_);
    other.shapes_.reset();
    capacity_ = other.capacity_;
    other.capacity_ = 0;
    size_ = other.size_;
    other.size_ = 0;
    return *this;
  }
  
  CompositeShape::shapePtr &CompositeShape::operator[](const size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Error! Composite shape index must be less than shape size!");
    }
    return shapes_[index];
  }
  
  size_t CompositeShape::getSize() const
  {
    return size_;
  }
  
  void CompositeShape::addShape(const CompositeShape::shapePtr &shape)
  {
    if (!shape)
    {
      throw std::invalid_argument("Error! Shape mustn't be null!");
    }
    if (size_ == capacity_)
    {
      arrShape tempShapes(new CompositeShape::shapePtr [capacity_ * 2 + 1]);
      for (size_t i = 0; i < size_; i++)
      {
        tempShapes[i] = shapes_[i];
      }
      capacity_ = capacity_ * 2 + 1;
      shapes_ = std::move(tempShapes);
    }
    shapes_[size_++] = shape;
  }
  
  void CompositeShape::removeShape(const size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Error! Composite shape index to remove must be less than shape size!");
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[--size_] = nullptr;
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
      return {0, 0, {0, 0}};
    }
    
    double left = 0.0,
        right = 0.0,
        top = 0.0,
        bottom = 0.0;
    
    rectangle_t rectangle = shapes_[0]->getFrameRect();
    left = rectangle.pos.x - rectangle.width / 2;
    right = rectangle.pos.x + rectangle.width / 2;
    bottom = rectangle.pos.y - rectangle.height / 2;
    top = rectangle.pos.y + rectangle.height / 2;
    
    for (size_t i = 1; i < size_; i++)
    {
      rectangle = shapes_[i]->getFrameRect();
      left = std::min(left, rectangle.pos.x - rectangle.width / 2);
      right = std::max(right, rectangle.pos.x + rectangle.width / 2);
      top = std::max(top, rectangle.pos.y + rectangle.height / 2);
      bottom = std::min(bottom, rectangle.pos.y - rectangle.height / 2);
    }
    
    return {right - left, top - bottom, left + (right - left) / 2, bottom + (top - bottom) / 2,};
  }
  
  void CompositeShape::move(const point_t &position) noexcept
  {
    double xChange = position.x - getFrameRect().pos.x;
    double yChange = position.y - getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(xChange, yChange);
    }
  }
  
  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }
  
  void CompositeShape::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Error! Invalid scale factor: must be positive.");
    }
    double centerX = getFrameRect().pos.x;
    double centerY = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(factor);
      double xChange = shapes_[i]->getFrameRect().pos.x - centerX;
      double yChange = shapes_[i]->getFrameRect().pos.y - centerY;
      shapes_[i]->move(xChange * (factor - 1), yChange * (factor - 1));
    }
  }
  
  void CompositeShape::rotate(double angle) noexcept
  {
    angle = specs::changeAngle(0.0, angle);
    const double xCenter = getFrameRect().pos.x;
    const double yCenter = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      const double xChange = shapes_[i]->getFrameRect().pos.x - xCenter;
      const double yChange = shapes_[i]->getFrameRect().pos.y - yCenter;
      const double distanceX = fabs(xChange * cos(angle)) - fabs((yChange * sin(angle)));
      const double distanceY = fabs(xChange * sin(angle)) + fabs((yChange * cos(angle)));
      shapes_[i]->move({xCenter + distanceX, yCenter + distanceY});
      shapes_[i]->rotate(specs::toDegree(angle));
    }
  
  }
  
  Matrix CompositeShape::toMatrix() const noexcept
  {
    Matrix matrix;
    for (size_t i = 0; i < size_; i++)
    {
      matrix.addShape(shapes_[i]);
    }
    return matrix;
  }
  
}


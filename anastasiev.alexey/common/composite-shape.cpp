#include "composite-shape.hpp"
#include <stdexcept>

namespace anastasiev
{
  CompositeShape::CompositeShape() :
    size_(0),
    capacity_(0),
    shapeArray_(nullptr)
  {}

  CompositeShape::CompositeShape(const CompositeShape &other):
    size_(other.size_),
    capacity_(other.capacity_),
    shapeArray_(std::make_unique<std::shared_ptr<Shape>[]>(other.capacity_))
  {
    for (unsigned int i = 0; i < size_; i++)
    {
      shapeArray_[i] = other.shapeArray_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape &&other) noexcept :
    size_(other.size_),
    capacity_(other.capacity_),  
    shapeArray_(std::move(other.shapeArray_))
  {
    other.size_ = 0;
    other.capacity_ = 0;
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &other)
  {
    if (this == &other)
    {
      return *this;
    }
    std::unique_ptr<std::shared_ptr<Shape>[]> tempArray = std::make_unique<std::shared_ptr<Shape>[]>(other.capacity_);
    for (unsigned int i = 0; i < size_; i++)
    {
      tempArray[i] = other.shapeArray_[i];
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    shapeArray_.reset(nullptr);
    shapeArray_.swap(tempArray);
    return *this;
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    shapeArray_.reset(nullptr);
    shapeArray_.swap(other.shapeArray_);
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
  }

  std::shared_ptr<Shape> CompositeShape::operator[](const unsigned  int index) const
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index must be less then size.");
    }
    return shapeArray_[index];
  }

  void CompositeShape::add(const std::shared_ptr<Shape> &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("No shape to add. Nullptr given.");
    }
    if(size_ == capacity_)
    {
      std::unique_ptr<std::shared_ptr<Shape>[]> tempArray = std::make_unique<std::shared_ptr<Shape>[]>(capacity_ + 1);
      capacity_++;
      for (unsigned int i = 0; i < size_; i++)
      {
        tempArray[i] = shapeArray_[i];
      }      
      shapeArray_.reset(nullptr);
      shapeArray_.swap(tempArray);
    }
    shapeArray_[size_++] = shape;
  }

  void CompositeShape::remove(const unsigned int index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index must be less then size.");
    }
    size_--;
    for (unsigned int i = index; i < size_; i++)
    {
      shapeArray_[i] = shapeArray_[i + 1];
    }
    shapeArray_[size_] = nullptr;
  }

  double CompositeShape::getArea() const noexcept
  {
    double area = 0.0;
    for (unsigned int i = 0; i < size_; i++)
    {
      area += shapeArray_[i]->getArea();
    }
    return area;
  }

  unsigned int CompositeShape::getSize() noexcept
  {
    return size_;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0.0, 0.0, {0.0, 0.0}};
    }
    rectangle_t tempFrame = shapeArray_[0]->getFrameRect();
    double left = tempFrame.pos.x - tempFrame.width / 2;
    double right = tempFrame.pos.x + tempFrame.width / 2;
    double top = tempFrame.pos.y + tempFrame.height / 2;
    double bottom = tempFrame.pos.y - tempFrame.height / 2;
    for (unsigned int i = 1; i < size_; i++)
    {
      tempFrame = shapeArray_[i]->getFrameRect();
      left = std::min(left, (tempFrame.pos.x - tempFrame.width / 2));
      right = std::max(right, (tempFrame.pos.x + tempFrame.width / 2));
      top = std::max(top, (tempFrame.pos.y + tempFrame.height / 2));
      bottom = std::min(bottom, (tempFrame.pos.x - tempFrame.width / 2));
    }
    return {(right - left), (top - bottom), {(left + (right - left) / 2), bottom + (top - bottom) / 2}};
  }

  void CompositeShape::move(const point_t &newPos) noexcept
  {
    double dx = newPos.x - this->getFrameRect().pos.x;
    double dy = newPos.y - this->getFrameRect().pos.y;
    for (unsigned int i = 0; i < size_; i++)
    {
      shapeArray_[i]->move(dx, dy);
    }
  }

  void CompositeShape::move(const double dx, const double dy) noexcept
  {
    for (unsigned int i = 0; i < size_; i++)
    {
      shapeArray_[i]->move(dx, dy);
    }
  }

  void CompositeShape::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive.");
    }
    double posX = getFrameRect().pos.x;
    double posY = getFrameRect().pos.y;
    for (unsigned int i = 0; i < size_; i++)
    {
      double dx = (shapeArray_[i]->getFrameRect().pos.x - posX);
      double dy = (shapeArray_[i]->getFrameRect().pos.y - posY);
      dx = dx * factor - dx;
      dy = dy * factor - dy;
      shapeArray_[i]->move(dx, dy);
      shapeArray_[i]->scale(factor);
    }
  }
} // namespace anastasiev

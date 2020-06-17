#include <limits>
#include "composite-shape.hpp"

namespace ushakov
{
  CompositeShape::CompositeShape() :
      shapes_(std::make_unique<std::shared_ptr<Shape>[]>(0)),
      size_(0),
      capacity_(0)
  {}

  CompositeShape::CompositeShape(const size_t capacity) :
      shapes_(std::make_unique<std::shared_ptr<Shape>[]>(capacity)),
      size_(0),
      capacity_(capacity)
  {}

  CompositeShape::CompositeShape(const ushakov::CompositeShape& compositeShape) :
      shapes_(std::make_unique<std::shared_ptr<Shape>[]>(compositeShape.capacity_)),
      size_(compositeShape.size_),
      capacity_(compositeShape.capacity_)
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = compositeShape.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(CompositeShape&& compositeShape) noexcept:
      shapes_(std::move(compositeShape.shapes_)),
      size_(compositeShape.size_),
      capacity_(compositeShape.capacity_)
  {
    compositeShape.shapes_.reset();
    compositeShape.size_ = 0;
    compositeShape.capacity_ = 0;
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& compositeShape)
  {
    if (this == &compositeShape)
    {
      return *this;
    }

    std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[compositeShape.size_]);

    for (size_t i = 0; i < compositeShape.size_; i++)
    {
      tmpShapes[i] = compositeShape.shapes_[i];
    }

    shapes_ = std::move(tmpShapes);
    size_ = compositeShape.size_;
    capacity_ = compositeShape.capacity_;

    return *this;
  }

  CompositeShape& CompositeShape::operator=(CompositeShape&& compositeShape) noexcept
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

  std::shared_ptr<Shape>& CompositeShape::operator[](const size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Index is out of range");
    }

    return shapes_[index];
  }

  size_t CompositeShape::getSize() const
  {
    return size_;
  }

  void CompositeShape::addShape(const std::shared_ptr<Shape>& shape)
  {
    if (!shape)
    {
      throw std::invalid_argument("Invalid shape");
    }

    if (!size_)
    {

      std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[1]);
      capacity_++;
      shapes_ = std::move(tmpShapes);
    }

    if (size_ == capacity_)
    {
      size_t new_capacity = capacity_ / 4;

      if(new_capacity == 0)
      {
        new_capacity++;
      }

      std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[size_ + new_capacity]);

      for (size_t i = 0; i < size_; i++)
      {
        tmpShapes[i] = shapes_[i];
      }

      capacity_ = size_ + new_capacity;
      shapes_ = std::move(tmpShapes);
    }

    shapes_[size_++] = shape;
  }

  void CompositeShape::removeShape(const size_t index)
  {
    if (index >= size_)
    {
      throw std::invalid_argument("Index is out of range");
    }

    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }

    shapes_[size_--] = nullptr;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
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
      const rectangle_t TMP_RECTANGLE = shapes_[i]->getFrameRect();

      left = std::min(left, TMP_RECTANGLE.pos.x - TMP_RECTANGLE.width / 2);
      right = std::max(right, TMP_RECTANGLE.pos.x + TMP_RECTANGLE.width / 2);
      top = std::max(top, TMP_RECTANGLE.pos.y + TMP_RECTANGLE.height / 2);
      bottom = std::min(bottom, TMP_RECTANGLE.pos.y - TMP_RECTANGLE.height / 2);
    }

    return {
        right - left, top - bottom,
        left + (right - left) / 2, bottom + (top - bottom) / 2,
    };
  }

  void CompositeShape::move(const point_t& position) noexcept
  {
    double dX = position.x - getFrameRect().pos.x;
    double dY = position.y - getFrameRect().pos.y;

    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(dX, dY);
    }
  }

  void CompositeShape::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Invalid coefficient of scale, it must be positive");
    }

    double centerX = getFrameRect().pos.x;
    double centerY = getFrameRect().pos.y;

    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(coefficient);

      double dX = shapes_[i]->getFrameRect().pos.x - centerX;
      double dY = shapes_[i]->getFrameRect().pos.y - centerY;

      shapes_[i]->move(dX * (coefficient - 1), dY * (coefficient - 1));
    }
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

  void CompositeShape::print() const
  {
    for (size_t i = 0; i < size_; i++)
    {
      std::cout << "Shape " << i << " is: ";
      shapes_[i]->print();
    }
  }

  void CompositeShape::printFrameRectangle() const
  {
    rectangle_t rect = getFrameRect();

    std::cout << "height = " << rect.height << " width = " << rect.width << " center.x = " << rect.pos.x
              << " center.y = "
              << rect.pos.y << std::endl;
  }

  point_t CompositeShape::getPosition() const
  {
    return getFrameRect().pos;
  }
}

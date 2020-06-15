#include "composite-shape.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cmath>

namespace bulanov
{
  const double  CIRCLE_ANGLE = 360.0;

  CompositeShape::CompositeShape() :
    size_(0),
    place_(1),
    shapes_(std::make_unique<shapePtr[]>(1))
  {}

  CompositeShape::CompositeShape(const size_t space) :
    size_(0),
    place_(space),
    shapes_(std::make_unique<shapePtr[]>(space))
  {}

  CompositeShape::CompositeShape(const bulanov::CompositeShape &figure) :
    size_(figure.size_),
    place_(figure.place_),
    shapes_(std::make_unique<shapePtr[]>(figure.place_))
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = figure.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(bulanov::CompositeShape &&figure) noexcept:
    size_(figure.size_),
    place_(figure.place_),
    shapes_(std::move(figure.shapes_))
  {
    figure.size_ = 0;
    figure.place_ = 0;
    figure.shapes_.reset();
  }

  CompositeShape &CompositeShape::operator=(const CompositeShape &figure)
  {
    if (this == &figure)
    {
      return *this;
    }
    else
    {
      shapeArray temp = std::make_unique<shapePtr[]>(figure.place_);
      for (size_t i = 0; i < figure.size_; i++)
      {
        temp[i] = figure.shapes_[i];
      }
      size_ = figure.size_;
      place_ = figure.place_;
      shapes_ = std::move(temp);
      return *this;
    }
  }

  CompositeShape &CompositeShape::operator=(CompositeShape &&figure) noexcept
  {
    if (this == &figure)
    {
      return *this;
    }
    size_ = figure.size_;
    place_ = figure.place_;
    shapes_ = std::move(figure.shapes_);
    figure.size_ = 0;
    figure.place_ = 0;
    figure.shapes_.reset();
    return *this;
  }

  CompositeShape::shapePtr &CompositeShape::operator[](const size_t index)
  {
    if (size_ == 0 || index >= size_)
    {
      throw std::out_of_range("Invalid index received. False index: " + std::to_string(index));
    }
    return shapes_[index];
  }

  double CompositeShape::getArea() const noexcept
  {
    double sumArea = 0;
    for (size_t i = 0; i < size_; i++)
    {
      sumArea += shapes_[i]->getArea();
    }
    return sumArea;

  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  {
    if (size_ == 0)
    {
      return {0, 0, {0, 0}};
    }

    double leftmost = std::numeric_limits<double>::max();
    double rightmost = std::numeric_limits<double>::lowest();
    double lowest = std::numeric_limits<double>::max();
    double topmost =  std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < size_; i++)
    {
      const rectangle_t rect = shapes_[i]->getFrameRect();
      double partWidth = rect.width / 2;
      double partHeight = rect.height / 2;

      leftmost = std::min(leftmost, rect.pos.x - partWidth);
      rightmost = std::max(rightmost, rect.pos.x + partWidth);
      lowest = std::min(lowest, rect.pos.y - partHeight);
      topmost = std::max(topmost, rect.pos.y + partHeight);
    }
    return {rightmost - leftmost, topmost - lowest,{(rightmost + leftmost) / 2, (topmost + lowest) / 2}};
  }

  void CompositeShape::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::move(const point_t &center) noexcept
  {
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i]->move(center);
    }
  }

  void CompositeShape::scale(double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Invalid rate of composite shape received. False rate: " + std::to_string(rate));
    }

    point_t commonCenter = getCenter();

    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(rate);
      double shiftX = shapes_[i]->getCenter().x - commonCenter.x;
      double shiftY = shapes_[i]->getCenter().y - commonCenter.y;
      shapes_[i]->move(shiftX * rate, shiftY * rate);
    }

  }

  point_t CompositeShape::getCenter() const noexcept
  {
    return getFrameRect().pos;
  }

  void CompositeShape::addElement(const CompositeShape::shapePtr &element)
  {
    if (element == nullptr)
    {
      throw std::invalid_argument("Error: the element of composite shape received is null");
    }
    if (size_ == place_)
    {
      shapeArray temp(std::make_unique<shapePtr[]>(place_ * 2));
      for (size_t i = 0; i < size_; i++)
      {
        temp[i] = shapes_[i];
      }
      place_ *= 2;
      shapes_ = std::move(temp);
    }
    shapes_[size_] = element;
    size_++;
  }

  void CompositeShape::removeElement(size_t index)
  {
    if (size_ == 0 || index >= size_)
    {
      throw std::out_of_range("Invalid index of composite shape received. False index: " + std::to_string(index));
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[size_ - 1] = nullptr;
    size_--;
  }

  void CompositeShape::printInform() const
  {
    std::cout << "Amount of elements:  " << size_ << ";\nCommon area:  " << getArea() << '\n';
    printFrameInform();
  }

  void CompositeShape::printFrameInform() const
  {
    rectangle_t commonFrame = getFrameRect();
    std::cout << "Information of Rectangle frame composite shape:   width = " << commonFrame.width
        << "; height = " << commonFrame.height << "; center = (" << commonFrame.pos.x
        << ", " << commonFrame.pos.y << ')' << std::endl;

  }

  void CompositeShape::rotate(const double angle) noexcept
  {
    double RadAngle = angle * M_PI / (CIRCLE_ANGLE / 2);
    point_t commonCenter = getCenter();

    for (size_t i = 0; i < size_; i++)
    {
      double distanceX = shapes_[i]->getCenter().x - commonCenter.x;
      double distanceY = shapes_[i]->getCenter().y - commonCenter.y;
      const double shiftX = (distanceX * fabs(cos(RadAngle))) - (distanceY * fabs(sin(RadAngle)));
      const double shiftY = (distanceX * fabs(sin(RadAngle))) + (distanceY * fabs(cos(RadAngle)));
      shapes_[i]->move({commonCenter.x + shiftX,commonCenter.y + shiftY});
      shapes_[i]->rotate(angle);

    }
  }

  Matrix CompositeShape::makeLayering() const
  {
    Matrix matrix;
    for (size_t i = 0; i < size_; i++)
    {
      matrix.addElement(shapes_[i]);
    }
    return matrix;
  }

}


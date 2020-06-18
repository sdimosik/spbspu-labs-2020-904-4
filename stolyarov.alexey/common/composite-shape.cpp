#include "composite-shape.hpp"
#include <string>
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <cmath>

namespace stolyarov
{

  const double CIRCLE_ANGLE = 360.0;

  CompositeShape::CompositeShape() :
    Shape(point_t{0.0, 0.0}),
    size_(0),
    place_(1),
    shapes_(std::make_unique<shapePtr[]>(1))
  {}

  CompositeShape::CompositeShape(const stolyarov::CompositeShape& figure) :
    Shape(point_t{0.0, 0.0}),
    size_(figure.size_),
    place_(figure.place_),
    shapes_(new std::shared_ptr<Shape>[figure.place_])
  {
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = figure.shapes_[i];
    }
  }

  CompositeShape::CompositeShape(stolyarov::CompositeShape&& figure) noexcept :
    Shape(point_t{0.0, 0.0}),
    size_(figure.size_),
    place_(figure.place_),
    shapes_(std::move(figure.shapes_))
  {
    figure.size_ = 0;
    figure.place_ = 0;
    figure.shapes_.reset();
  }

  CompositeShape& CompositeShape::operator=(const CompositeShape& figure)
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

  CompositeShape& CompositeShape::operator=(CompositeShape&& figure) noexcept
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

  CompositeShape::shapePtr& CompositeShape::operator[](const size_t index)
  {
    if (index >= size_)
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
      return { 0, 0, {0, 0} };
    }

    double leftmost = std::numeric_limits<double>::max();
    double rightmost = std::numeric_limits<double>::lowest();
    double lowest = std::numeric_limits<double>::max();
    double highest = std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < size_; i++)
    {
      const rectangle_t rect = shapes_[i]->getFrameRect();
      double partWidth = rect.width / 2;
      double partHeight = rect.height / 2;

      leftmost = std::min(leftmost, rect.pos.x - partWidth);
      rightmost = std::max(rightmost, rect.pos.x + partWidth);
      lowest = std::min(lowest, rect.pos.y - partHeight);
      highest = std::max(highest, rect.pos.y + partHeight);
    }
    return { rightmost - leftmost, highest - lowest,{(rightmost + leftmost) / 2, (highest + lowest) / 2} };
  }

  void CompositeShape::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i]->move(x, y);
    }
  }

  void CompositeShape::move(const point_t& center) noexcept
  {
    const point_t prevCenter{ this->getCenter() };
    double dx = center.x - prevCenter.x;
    double dy = center.y - prevCenter.y;
    this->move(dx, dy);
  }

  void CompositeShape::scale(double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Invalid composite shape rate received. False rate: " + std::to_string(rate));
    }

    double centerX = getFrameRect().pos.x;
    double centerY = getFrameRect().pos.y;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i]->scale(rate);
      double changeX = shapes_[i]->getFrameRect().pos.x - centerX;
      double changeY = shapes_[i]->getFrameRect().pos.y - centerY;
      shapes_[i]->move(changeX * (rate - 1), changeY * (rate - 1));
    }

  }

  void CompositeShape::addElement(const shapePtr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape is NULL");
    }
    if (size_ == place_)
    {
      const int coefficient = 2;
      shapeArray temp_shape(new std::shared_ptr<Shape>[place_ * coefficient]);
      for (size_t i = 0; i < size_; i++)
      {
        temp_shape[i] = shapes_[i];
      }
      place_ = place_ * coefficient;
      shapes_ = std::move(temp_shape);
    }
    shapes_[size_] = shape;
    size_++;

  }

  point_t CompositeShape::getCenter() const noexcept
  {
    return getFrameRect().pos;
  }

  void CompositeShape::removeElement(size_t index)
  {
    if (index >= size_)
    {
      throw std::out_of_range("Invalid composite shape index was received. False index: " + std::to_string(index));
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      shapes_[i] = shapes_[i + 1];
    }
    shapes_[size_ - 1] = nullptr;
    size_--;
  }

  void CompositeShape::printInf()
  {
    std::cout << "Amount of elements:  " << size_ << ";\nCommon area:  " << getArea() << '\n' << '\n';
  }

  void CompositeShape::printFrameInf()
  {
    std::cout << "Composite shape's frame information" << '\n'
        << "Center's location:" << '\n'
        << "x: " << getCenter().x << '\n' << "y: " << getCenter().y << '\n'
        << "Parameters of the frame:" << '\n'
        << "height: " << getFrameRect().height << '\n' << "widht: " << getFrameRect().width << '\n' << '\n';
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
      shapes_[i]->move({ commonCenter.x + shiftX, commonCenter.y + shiftY });
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

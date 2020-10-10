
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include "polygon.hpp"
#include "specs.hpp"

namespace pashnin
{
  Polygon::Polygon(const std::initializer_list<point_t> &points) :
    points_(std::make_unique<point_t[]>(points.size()))
  {
    if (points.size() < 3)
    {
      throw std::invalid_argument("Can't build polygon with less than 3 points.");
    }
    count_ = points.size();
    std::copy(points.begin(), points.end(), points_.get());
    if (!isConvex())
    {
      throw std::invalid_argument("Polygon is not convex.");
    }
    if (this->getArea() == 0.0)
    {
      throw std::invalid_argument("Area of polygon must be more than 0.");
    }
  }
  
  double Polygon::getArea() const noexcept
  {
    double area = 0;
    for (size_t i = 0; i < count_ - 1; i++)
    {
      area += points_[i].x * points_[i + 1].y - points_[i].y * points_[i + 1].x;
    }
    area += points_[count_ - 1].x * points_[0].y - points_[count_ - 1].y * points_[0].x;
    return std::abs(area / 2);
  }
  
  rectangle_t Polygon::getFrameRect() const noexcept
  {
    double minX = points_[0].x;
    double minY = points_[0].y;
    double maxX = points_[0].x;
    double maxY = points_[0].y;
    for (size_t i = 1; i < count_; i++)
    {
      minX = std::min(minX, points_[i].x);
      minY = std::min(minY, points_[i].y);
      maxX = std::max(maxX, points_[i].x);
      maxY = std::max(maxY, points_[i].y);
    }
    return {(maxX - minX), (maxY - minY), {(minX + (maxX - minX) / 2), (minY + (maxY - minY) / 2)}};
  }
  
  void Polygon::move(const point_t &newPos) noexcept
  {
    point_t pos = getPosition();
    double xChange = newPos.x - pos.x;
    double yChange = newPos.y - pos.y;
    move(xChange, yChange);
  }
  
  void Polygon::move(double xChange, double yChange) noexcept
  {
    for (size_t i = 0; i < count_; i++)
    {
      points_[i].x += xChange;
      points_[i].y += yChange;
    }
  }
  
  void Polygon::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Value must be positive.");
    }
    point_t pos = getPosition();
    for (size_t i = 0; i < count_; i++)
    {
      points_[i] = {pos.x + (pos.x - points_[i].x) * factor, pos.y + (pos.y - points_[i].y) * factor};
    }
  }
  
  void Polygon::rotate(double angle) noexcept
  {
    angle_ = specs::changeAngle(angle_, angle);
    double tempX;
    point_t pos = getPosition();
    for (size_t i = 0; i < count_; i++)
    {
      tempX = points_[i].x;
      points_[i].x = (points_[i].x - pos.x) * cos(angle_) - (points_[i].y - pos.y) * sin(angle_) + pos.x;
      points_[i].y = (tempX - pos.x) * sin(angle_) + (points_[i].y - pos.y) * cos(angle_) + pos.y;
    }
  }
  
  point_t Polygon::getPosition() noexcept
  {
    double x = 0;
    double y = 0;
    for (size_t i = 0; i < count_; i++)
    {
      x += points_[i].x;
      y += points_[i].y;
    }
    return {x / count_, y / count_};
  }
  
  bool Polygon::isConvex() const
  {
    double vector1 = (points_[0].x - points_[count_ - 1].x) * (points_[1].y - points_[0].y)
                     - (points_[1].x - points_[0].x) * (points_[0].y - points_[count_ - 1].y);
    double vector2 = 0;
    for (size_t i = 0; i < count_ - 2; i++)
    {
      vector2 = (points_[i + 1].x - points_[i].x) * (points_[i + 2].y - points_[i + 1].y)
                - (points_[i + 2].x - points_[i + 1].x) * (points_[i + 1].y - points_[i].y);
      if (vector1 * vector2 >= 0)
      {
        vector1 = vector2;
      }
      else
      {
        return false;
      }
    }
    vector2 = (points_[count_ - 1].x - points_[count_ - 2].x) * (points_[0].y - points_[count_ - 1].y)
              - (points_[0].x - points_[count_ - 1].x) * (points_[count_ - 1].y - points_[count_ - 2].y);
    return (vector1 * vector2 >= 0);
  }
}

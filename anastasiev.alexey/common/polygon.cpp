#include "polygon.hpp"
#include <cmath>
#include <algorithm>
namespace anastasiev
{
  Polygon::Polygon(const std::initializer_list<point_t>& points) :
    points_(std::make_unique<point_t[]>(points.size()))   
  {
    if(points.size() < 3)
    {
      throw std::invalid_argument("Cant build polygon with less than 3 points.");
    }
    count_ = points.size();
    std::copy(points.begin(),points.end(), points_.get());
    if (!isConvex())
    {
      throw std::invalid_argument("Polygon is unconvex.");
    }
    if (getArea() == 0)
    {
      throw std::invalid_argument("Area of polygon must be more than 0.");
    }
  }
  
  double Polygon::getArea() const noexcept
  {
    double area = 0;
    for (unsigned int i = 0; i < count_ - 1; i++ )
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
    for(unsigned int i = 1; i < count_; i++)
    {
      minX = std::min(minX, points_[i].x);
      minY = std::min(minY, points_[i].y);
      maxX = std::max(maxX, points_[i].x);
      maxY = std::max(maxY, points_[i].y);
    }
    return {(maxX - minX),(maxY - minY),{(minX + (maxX - minX) / 2), (minY + (maxY - minY) / 2)}};
  }
  
  void Polygon::move(const point_t& newPos) noexcept
  {
    point_t pos = getPosition();
    double dx = newPos.x - pos.x;
    double dy = newPos.y - pos.y;
    move(dx, dy);
  }
    
  void Polygon::move(const double dx, const double dy) noexcept
  {
    for(unsigned int i = 0; i < count_; i++)
    {
      points_[i].x += dx;
      points_[i].y += dy;
    }
  }
  
  void Polygon::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor must be pisitive.");
    }
    point_t pos = getPosition();
    for (unsigned int i = 0; i < count_; i++)
    {
      points_[i] = {pos.x + (pos.x - points_[i].x) * factor, pos.y + (pos.y - points_[i].y) * factor};
    }
  }
    
  void Polygon::rotate(double angle) noexcept
  {
    rotateAroundPoint(angle, getPosition());
  }
  
  void Polygon::rotateAroundPoint(double angle, const point_t& point) noexcept
  {
    angle = angle * M_PI / 180;
    double tempX;
    for (unsigned int i = 0; i < count_; i++)
    {
      tempX = points_[i].x;
      points_[i].x = point.x + (points_[i].x - point.x) * std::cos(angle) - (points_[i].y - point.y) * std::sin(angle);
      points_[i].y = point.y + (points_[i].y - point.y) * std::cos(angle) + (tempX - point.x) * std::sin(angle);
    }
  }

  point_t Polygon::getPosition() noexcept
  {
    double x = 0;
    double y = 0;
    for (unsigned int i = 0; i < count_; i++)
    {
      x += points_[i].x;
      y += points_[i].y;
    }
    return {x / count_, y / count_};
  }
  
  bool Polygon::isConvex() const
  {
    double vect1 = (points_[0].x - points_[count_ - 1].x) * (points_[1].y - points_[0].y)
        - (points_[1].x - points_[0].x) * (points_[0].y - points_[count_ - 1].y);
    double vect2 = 0;
    for (unsigned int i = 0; i < count_ - 2; i++)
    {
      vect2 = (points_[i + 1].x - points_[i].x) * (points_[i + 2].y - points_[i + 1].y)
          - (points_[i + 2].x - points_[i + 1].x) * (points_[i + 1].y - points_[i].y);
      if (vect1 * vect2 >= 0)
      {
        vect1 = vect2;
      }
      else
      {
        return false;
      }
    }
    vect2 = (points_[count_ - 1].x - points_[count_ - 2].x) * (points_[0].y - points_[count_ - 1].y)
        - (points_[0].x - points_[count_ - 1].x) * (points_[count_ - 1].y - points_[count_ - 2].y);
    return (vect1 * vect2 >= 0);
  }
}

#include <algorithm>
#include <cmath>
#include "polygon.hpp"

namespace maksimova
{
  Polygon::Polygon(const point_t *points, size_t size) :
    size_(size),
    points_(std::make_unique<point_t[]>(size))
  {
    if(size < 3)
      throw std::invalid_argument("There should be more then 3 points in polygon.");
    size_t min = 0;
    for(size_t i = 0; i < size; ++i)
    {
      points_[i] = points[i];
      if(points[i].x < points[min].x)
        min = i;
    }
    std::swap(points_[0], points_[min]);
    for(size_t i = 1; i < size_; ++i)
    {
      min = i;
      for(size_t j = i; j < size_; ++j)
      {
        if((points_[min].x - points_[0].x) * (points_[j].y - points_[min].y)
          - (points_[min].y - points_[0].y) * (points_[j].x - points_[min].x) < 0)
            min = j;
      }
      std::swap(points_[min], points_[i]);
    }
    if(!is_convex())
      throw std::invalid_argument("Polygon is not convex.");
  }

  Polygon::Polygon(const Polygon &other) :
    size_(other.size_),
    points_(std::make_unique<point_t[]>(other.size_))
  {
    for(size_t i = 0; i < size_; ++i)
    {
      points_[i] = other.points_[i];
    }
  }

  Polygon::Polygon(Polygon &&other) :
    size_(other.size_),
    points_(std::move(other.points_))
  {
    other.size_ = 0;
    other.points_ = nullptr;
  }

  Polygon & Polygon::operator=(const Polygon &other)
  {
    if(this == &other)
      return *this;
    size_ = other.size_;
    points_ = std::make_unique<point_t[]>(size_);
    for(size_t i = 0; i < size_; ++i)
    {
      points_[i] = other.points_[i];
    }
    return *this;
  }

  Polygon & Polygon::operator=(Polygon &&other)
  {
    if(this == &other)
    {
      return *this;
    }
    size_ = other.size_;
    points_ = std::move(other.points_);
    other.size_ = 0;
    other.points_ = nullptr;
    return *this;
  }

  point_t & Polygon::operator[](size_t index)
  {
    return points_[index];
  }

  bool Polygon::is_convex() const noexcept
  {
     point_t A, B, C;
     double direction;
     for(size_t i = 0; i < size_; ++i)
     {
       A = points_[i];
       B = points_[(i + 1) % size_];
       C = points_[(i + 2) % size_];
       direction = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
       if(direction <= 0)
         return false;
     }
     return true;
  }

  double Polygon::getArea() const noexcept
  {
    double area = 0;
    for (size_t i = 1; i < size_; ++i)
    {
      area += points_[i - 1].x * points_[i].y - points_[i - 1].y * points_[i].x;
    }
    area += points_[size_ - 1].x * points_[0].y - points_[size_ - 1].y * points_[0].x;
    area *= 0.5;
    return area;
  }

  rectangle_t Polygon::getFrameRect() const noexcept
  {
    double max_x, min_x, max_y, min_y;
    max_x = min_x = points_[0].x;
    max_y = min_y = points_[0].y;
    for(size_t i = 0; i < size_; ++i)
    {
      max_x = std::max(max_x, points_[i].x);
      min_x = std::min(min_x, points_[i].x);
      max_y = std::max(max_y, points_[i].y);
      min_y = std::min(min_y, points_[i].y);
    }
    return {max_x - min_x, max_y - min_y,
      {(min_x + max_x) / 2, (min_y + max_y) / 2}};
  }

  void Polygon::move(const double dx, const double dy) noexcept
  {
    for(size_t i = 0; i < size_; ++i)
    {
      points_[i].x += dx;
      points_[i].y += dy;
    }
  }

  void Polygon::move(const point_t &pos) noexcept
  {
    point_t previous = getFrameRect().pos;
    move(pos.x - previous.x, pos.y - previous.y);
  }

  void Polygon::scale(const double coefficient)
  {
    if(coefficient <= 0)
    {
      throw std::invalid_argument("Invalid coefficient. Coefficient: "
        + std::to_string(coefficient));
    }
    point_t center = get_center();
    for(size_t i = 0; i < size_; ++i)
    {
      points_[i].x += (points_[i].x - center.x) * (coefficient - 1);
      points_[i].y += (points_[i].y - center.y) * (coefficient - 1);
    }
  }

  void Polygon::rotate(const double angle) noexcept
  {
    double angleRad = angle * M_PI / (CIRCLE_ANGLE / 2);
    point_t center = get_center();
    for(size_t i = 0; i < size_; ++i)
    {
      double distanceX = points_[i].x - center.x;
      double distanceY = points_[i].y - center.y;
      points_[i].x = distanceX * std::cos(angleRad)
        - distanceY * std::sin(angleRad) + center.x;
      points_[i].y = distanceX * std::sin(angleRad)
        + distanceY * std::cos(angleRad) + center.y;
    }
  }

  void Polygon::print() const
  {
    std::cout << "Amount of elements:  " << size_ << "." << std::endl
        << "Whole area:  " << getArea() << std::endl
        << "Polygon center = (" << get_center().x << ", "
        << get_center().y << ")\n" << "Points:\n";
    for(size_t i = 0; i < size_; ++i)
    {
      std::cout << "{ " << points_[i].x << ", " << points_[i].y << "}\n";
    }
  }

  point_t Polygon::get_center() const noexcept
  {
    point_t center{0, 0};
    for(size_t i = 0; i < size_; ++i)
    {
      center.x += points_[i].x;
      center.y += points_[i].y;
    }
    center.x /= size_;
    center.y /= size_;
    return center;
  }
}

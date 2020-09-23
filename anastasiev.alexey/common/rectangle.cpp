#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
namespace anastasiev
{
  Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
    corners_({{(pos.x - width / 2), (pos.y - height / 2)},
        {(pos.x - width / 2), (pos.y + height / 2)},
        {(pos.x + width / 2), (pos.y + height / 2)},
        {(pos.x + width / 2), (pos.y - height / 2)}})
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Height and width must be positive.");
    }
  }

  double Rectangle::getWidth() const
  {
    return std::sqrt((corners_[3].x - corners_[0].x) * (corners_[3].x - corners_[0].x)
        + (corners_[3].y - corners_[0].y) * (corners_[3].y - corners_[0].y));
  }

  double Rectangle::getHeight() const
  {
    return std::sqrt((corners_[1].x - corners_[0].x) * (corners_[1].x - corners_[0].x)
        + (corners_[1].y - corners_[0].y) * (corners_[1].y - corners_[0].y));
  }

  point_t Rectangle::getPosition() const
  {
    return {(corners_[0].x + corners_[2].x) / 2, (corners_[0].y + corners_[2].y) / 2};
  }

  double Rectangle::getArea() const noexcept
  {
    return (getHeight() * getWidth());
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double minX = std::min({corners_[0].x, corners_[1].x, corners_[2].x, corners_[3].x});
    double maxX = std::max({corners_[0].x, corners_[1].x, corners_[2].x, corners_[3].x});
    double minY = std::min({corners_[0].y, corners_[1].y, corners_[2].y, corners_[3].y});
    double maxY = std::max({corners_[0].y, corners_[1].y, corners_[2].y, corners_[3].y});
    return rectangle_t{maxX - minX, maxY - minY, getPosition()};
  }

  void Rectangle::move(const double x, const double y) noexcept
  {
    for(point_t& corner : corners_)
    {
      corner.x += x;
      corner.y += y;
    }
  }

  void Rectangle::move(const point_t &newPos) noexcept
  {
    double dx = newPos.x - getPosition().x;
    double dy = newPos.y - getPosition().y;
    move (dx, dy);
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor of scale must be positive.");
    }
    point_t pos = getPosition();
    for(point_t& corner : corners_)
    {
      corner = {pos.x - (pos.x - corner.x) * factor,
          pos.y - (pos.y - corner.y) * factor};
    }
  }
  void Rectangle::rotate(double angle) noexcept
  {
    rotateAroundPoint(angle, getPosition());
  }
  
  void Rectangle::rotateAroundPoint(double angle, const point_t& point) noexcept
  {
    angle = angle * M_PI / 180;
    for(point_t& corner : corners_)
    {
      double x = corner.x;
      corner.x = point.x + (corner.x - point.x) * std::cos(angle) - (corner.y - point.y) * std::sin(angle);
      corner.y = point.y + (corner.y - point.y) * std::cos(angle) + (x - point.x) * std::sin(angle);
    }
  }
}//namespace anastasiev

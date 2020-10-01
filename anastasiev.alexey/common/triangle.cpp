#include "triangle.hpp"
#include <cmath>
#include <stdexcept>

namespace anastasiev
{
  Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c) :
    vertices_({a, b, c})
  {
    if (((c.x - a.x) / (b.x - a.x) == (c.y - a.y) / (b.y - a.y)))
    {
      throw std::invalid_argument("Triangle tops cannot be on straight line.");
    }
  }
  point_t Triangle::getPosition() const
  {
    return {(vertices_[0].x + vertices_[1].x + vertices_[2].x) / 3,
        (vertices_[0].y + vertices_[1].y + vertices_[2].y) / 3};
  }
  double Triangle::getArea() const noexcept
  {
    return (std::abs((vertices_[1].x - vertices_[0].x) * (vertices_[2].y - vertices_[0].y)
        - (vertices_[2].x - vertices_[0].x) * (vertices_[1].y - vertices_[0].y))) / 2;
  }
  rectangle_t Triangle::getFrameRect() const noexcept
  {
    double minX = std::min(std::min(vertices_[0].x, vertices_[1].x), vertices_[2].x);
    double maxX = std::max(std::max(vertices_[0].x, vertices_[1].x), vertices_[2].x);
    double minY = std::min(std::min(vertices_[0].y, vertices_[1].y), vertices_[2].y);
    double maxY = std::max(std::max(vertices_[0].y, vertices_[1].y), vertices_[2].y);
    return {maxX - minX, maxY - minY, point_t{maxX - (maxX - minX) / 2, maxY - (maxY - minY) / 2}};
  }
  void Triangle::move(const point_t &pos) noexcept
  {
    double dx = pos.x - getPosition().x;
    double dy = pos.y - getPosition().y;
    move(dx, dy);
  }
  void Triangle::move(const double dx, const double dy) noexcept
  {
    for (point_t &vertex : vertices_)
    {
      vertex.x += dx;
      vertex.y += dy;
    }
  }
  void Triangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor of scale must be positive.");
    }
    point_t pos = getPosition();
    for (point_t &vertex : vertices_)
    {
      vertex = {pos.x + (pos.x - vertex.x) * factor, pos.y + (pos.y - vertex.y) * factor};
    }
  }
  void Triangle::rotate(double angle) noexcept
  {
    rotateAroundPoint(angle, getPosition());
  }
  void Triangle::rotateAroundPoint(double angle, const point_t &point) noexcept
  {
    angle = angle * M_PI / 180;
    for (point_t &vertex : vertices_)
    {
      double tempX = vertex.x;
      vertex.x = point.x + (vertex.x - point.x) * std::cos(angle) - (vertex.y - point.y) * std::sin(angle);
      vertex.y = point.y + (vertex.y - point.y) * std::cos(angle) + (tempX - point.x) * std::sin(angle);
    }
  }
} // namespace anastasiev

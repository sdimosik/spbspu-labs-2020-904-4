#include "rectangle.hpp"

#include <stdexcept>
#include <algorithm>
#include <math.h>

namespace shabinsky
{
  Rectangle::Rectangle(const point_t &position, double width, double height) :
    edges_{{position.x - width / 2, position.y + height / 2},
           {position.x + width / 2, position.y + height / 2},
           {position.x - width / 2, position.y - height / 2},
           {position.x + width / 2, position.y - height / 2}}
  {
    if (width <= 0 || height <= 0)
    {
      std::string message = "Height and Width must be positive.";
      message += " Width: " + std::to_string(width);
      message += " Height: " + std::to_string(height);
      throw std::invalid_argument(message);
    }
  }
  
  double Rectangle::getWidth() const
  {
    return std::sqrt(std::pow(edges_[0].x - edges_[1].x, 2) + std::pow(edges_[0].y - edges_[1].y, 2));
  }
  
  double Rectangle::getHeight() const
  {
    return std::sqrt(std::pow(edges_[0].x - edges_[2].x, 2) + std::pow(edges_[0].y - edges_[2].y, 2));;
  }
  
  point_t Rectangle::getPosition() const
  {
    point_t point{0,0};
    for (int i = 0; i < countEdges; ++i)
    {
      point.x += edges_[i].x;
      point.y += edges_[i].y;
    }
    point.x /= countEdges;
    point.y /= countEdges;
    return point;
  }
  
  double Rectangle::getArea() const
  {
    return getHeight() * getWidth();
  }
  
  rectangle_t Rectangle::getFrameRect() const
  {
    double maxX = std::max(std::max(edges_[0].x, edges_[1].x), std::max(edges_[2].x, edges_[3].x)),
      minX = std::min(std::min(edges_[0].x, edges_[1].x), std::min(edges_[2].x, edges_[3].x)),
      maxY = std::max(std::max(edges_[0].y, edges_[1].y), std::max(edges_[2].y, edges_[3].y)),
      minY = std::min(std::min(edges_[0].y, edges_[1].y), std::min(edges_[2].y, edges_[3].y));
    return rectangle_t{maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
  }
  
  void Rectangle::move(const point_t &position)
  {
    double deltaX = position.x - getPosition().x;
    double deltaY = position.y - getPosition().y;
    move(deltaX, deltaY);
  }
  
  void Rectangle::move(double x, double y)
  {
    for (point_t &edge : edges_)
    {
      edge.x += x;
      edge.y += y;
    }
  }
  
  void Rectangle::show(std::ostream &out)
  {
    out << "[H: " << getHeight() << ";W: " << getWidth() << ";" << getPosition() << "]\n";
  }
  
  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient must be positive. Coefficient: " + std::to_string(coefficient));
    }
    double width = getWidth();
    double height = getHeight();
    point_t position = getPosition();
    
    for (int i = 0; i < countEdges; ++i)
    {
      int kX = 1;
      int kY = 1;
      
      if (edges_[i].x < position.x)
      {
        kX = -1;
      }
      if (edges_[i].y < position.y)
      {
        kY = -1;
      }
      edges_[i].x = (position.x + kX * (width / 2) * coefficient);
      edges_[i].y = (position.y + kY * (height / 2) * coefficient);
    }
  }
  
  void Rectangle::rotate(double angle)
  {
    const double angleRad = (angle * M_PI) / 180;
    const double sin = std::sin(angleRad),
      cos = std::cos(angleRad);
    const double centerX = getPosition().x;
    const double centerY = getPosition().y;
    for (point_t &edge : edges_)
    {
      const double distanceX = edge.x - centerX;
      const double distanceY = edge.y - centerY;
      edge.x = centerX + distanceX * cos - distanceY * sin;
      edge.y = centerY + distanceX * sin + distanceY * cos;
    }
  }
}

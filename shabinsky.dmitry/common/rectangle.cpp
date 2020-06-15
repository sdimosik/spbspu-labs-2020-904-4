#include "rectangle.hpp"

#include <stdexcept>
#include <math.h>

namespace shabinsky
{
  Rectangle::Rectangle(const point_t &position, double width, double height) :
    width_(width),
    height_(height),
    position_(position),
    angle_(0),
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
    return width_;
  }
  
  double Rectangle::getHeight() const
  {
    return height_;
  }
  
  point_t Rectangle::getPosition() const
  {
    return position_;
  }
  
  double Rectangle::getArea() const
  {
    return width_ * height_;
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
    double deltaX = position.x - position_.x;
    double deltaY = position.y - position_.y;
    move(deltaX, deltaY);
  }
  
  void Rectangle::move(double x, double y)
  {
    position_.x += x;
    position_.y += y;
    for (point_t &edge : edges_)
    {
      edge.x += x;
      edge.y += y;
    }
  }
  
  void Rectangle::show(std::ostream &out)
  {
    out << "[H: " << this->height_ << ";W: " << this->width_ << ";" << this->position_ << "]\n";
  }
  
  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient must be positive. Coefficient: " + std::to_string(coefficient));
    }
    for (int i = 0; i < 4; ++i)
    {
      if (edges_[i].x >= position_.x)
      {
        edges_[i].x = (position_.x + (width_ / 2) * coefficient);
        if (edges_[i].y >= position_.y)
        {
          edges_[i].y = (position_.y + (height_ / 2) * coefficient);
        }
        else
        {
          edges_[i].y = (position_.y - (height_ / 2) * coefficient);
        }
      }
      else
      {
        edges_[i].x = (position_.x - (width_ / 2) * coefficient);
        if (edges_[i].y >= position_.y)
        {
          edges_[i].y = (position_.y + (height_ / 2) * coefficient);
        }
        else
        {
          edges_[i].y = (position_.y - (height_ / 2) * coefficient);
        }
      }
      /*
      if (i == 0 || i == 4)
      {
        edges_[i].x = (position_.x - (width_ / 2) * coefficient);
      }
      else
      {
        edges_[i].x = (position_.x + (width_ / 2) * coefficient);
      }
      
      if (i == 0 || i == 1)
      {
        edges_[i].y = (position_.y + (height_ / 2) * coefficient);
      }
      else
      {
        edges_[i].y = (position_.y - (height_ / 2) * coefficient);
      }*/
    }
    width_ *= coefficient;
    height_ *= coefficient;
  }
  
  void Rectangle::rotate(double angle)
  {
    const double angleRad = (angle * M_PI) / 180;
    const double sin = std::sin(angleRad),
      cos = std::cos(angleRad);
    for (point_t &edge : edges_)
    {
      const double centerX = position_.x;
      const double centerY = position_.y;
      const double distanceX = edge.x - centerX;
      const double distanceY = edge.y - centerY;
      edge.x = centerX + distanceX * cos - distanceY * sin;
      edge.y = centerY + distanceX * sin + distanceY * cos;
    }
  }
}

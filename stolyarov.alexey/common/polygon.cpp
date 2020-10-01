#include "polygon.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <string>

namespace stolyarov
{
  Polygon::Polygon(const point_t* points, size_t pointsNum) :
    Shape(point_t{ 0.0, 0.0 }),
    pointsNum_(pointsNum)
  {
    if (pointsNum_ < 3)
    {
      throw std::invalid_argument("Invalid argument: number of points in poligon must be 3 or more.");
    }

    points_ = std::make_unique<point_t[]>(pointsNum_);

    for (size_t i = 0; i < pointsNum_; ++i)
    {
      points_[i] = points[i];
    }

    if (!isConvex())
    {
      throw std::invalid_argument("Invalid argument: constructed poligon is not convex.");
    }

    if (getArea() == 0)
    {
      throw std::invalid_argument("Invalid argument: constructed poligon has area equal to zero.");
    }

    calculateCenter();
  }

  Polygon::Polygon(const Polygon& otherPolygon) :
    Shape({ otherPolygon.pos_.x, otherPolygon.pos_.y }),
    pointsNum_(otherPolygon.pointsNum_)
  {
    points_ = std::make_unique<point_t[]>(pointsNum_);
    for (size_t i = 0; i < pointsNum_; ++i)
    {
      points_[i] = otherPolygon.points_[i];
    }
  }

  Polygon& stolyarov::Polygon::operator=(const Polygon& otherPolygon)
  {
    if (this == &otherPolygon)
    {
      return *this;
    }
    pointsNum_ = otherPolygon.pointsNum_;
    try 
    {
      points_ = std::make_unique<point_t[]>(pointsNum_);
    }
    catch (const std::exception& message)
    {
      throw message;
    }
    for (size_t i = 0; i < pointsNum_; ++i)
    {
      points_[i] = otherPolygon.points_[i];
    }
    return *this;
  }

  point_t Polygon::getCenter() const noexcept
  {
    return pos_;
  }

  void Polygon::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < pointsNum_; ++i)
    {
      points_[i].x += x;
      points_[i].y += y;
    }
    pos_.x += x;
    pos_.y += y;
  }

  void Polygon::move(const point_t& pos) noexcept
  {
    double deltaX = pos_.x - pos.x;
    double deltaY = pos_.y - pos.y;
    pos_ = pos;
    for (size_t i = 0; i < pointsNum_; ++i)
    {
      points_[i].x = points_[i].x - deltaX;
      points_[i].y = points_[i].y - deltaY;
    }
  }

  double stolyarov::Polygon::getArea() const noexcept
  {
    double area = 0;
    for (size_t i = 0; i < pointsNum_ - 1; i++)
    {
      area += (points_[i].x + points_[i + 1].x)
        * (points_[i].y - points_[i + 1].y);
    }
    area += (points_[pointsNum_ - 1].x + points_[0].x)
      * (points_[pointsNum_ - 1].y - points_[0].y);
    return 0.5 * fabs(area);
  }

  size_t stolyarov::Polygon::getPointsNum() const
  {
    return pointsNum_;
  }

  void stolyarov::Polygon::printInf()
  {
    std::cout << "Polygon information" << '\n'
      << "plygon's location:" << '\n'
      << "x: " << pos_.x << '\n' << "y: " << pos_.y << '\n'
      << "Area of the polygon: " << getArea() << '\n' << '\n';
  }

  void Polygon::printFrameInf()
  {
    std::cout << "Frame information" << '\n'
      << "Center's location:" << '\n'
      << "x: " << getFrameRect().pos.x << '\n' << "y: " << getFrameRect().pos.y << '\n'
      << "Parameters of the frame:" << '\n'
      << "height: " << getFrameRect().height << '\n' << "widht: " << getFrameRect().width << '\n' << '\n';
  }

  rectangle_t stolyarov::Polygon::getFrameRect() const noexcept
  {
    double frameRectLeftBorder = points_[0].x;
    double frameRectRightBorder = points_[0].x;
    double frameRectTopBorder = points_[0].y;
    double frameRectBottomBorder = points_[0].y;

    for (size_t i = 1; i < pointsNum_; ++i)
    {
      frameRectLeftBorder = std::min(points_[i].x, frameRectLeftBorder);
      frameRectRightBorder = std::max(points_[i].x, frameRectRightBorder);
      frameRectBottomBorder = std::min(points_[i].y, frameRectBottomBorder);
      frameRectTopBorder = std::max(points_[i].y, frameRectTopBorder);
    }

    rectangle_t frameRect;
    frameRect.width = frameRectRightBorder - frameRectLeftBorder;
    frameRect.height = frameRectTopBorder - frameRectBottomBorder;
    frameRect.pos = { frameRectLeftBorder + frameRect.width / 2, frameRectBottomBorder + frameRect.height / 2 };

    return frameRect;
  }

  void Polygon::scale(double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Wrong Parameters: parameter must be positive number. Wrong argument: coefficient = " +
        std::to_string(rate));
    }

    const point_t prevCenter{ getCenter() };

    for (size_t i = 0; i < pointsNum_; i++)
    {
      points_[i].x = rate * (prevCenter.x - points_[i].x) + prevCenter.x;
      points_[i].y = rate * (prevCenter.y - points_[i].y) + prevCenter.y;
    }
  }

  void Polygon::rotate(const double angle) noexcept
  {
    const double a = angle / 180 * M_PI;
    const double sinA = sin(a);
    const double cosA = cos(a);

    const point_t center = getCenter();
    for (size_t i = 0; i < pointsNum_; ++i)
    {
      double prevX = points_[i].x,
        prevY = points_[i].y;
      points_[i].x = (prevX - center.x) * cosA - (prevY - center.y) * sinA + center.x;
      points_[i].y = (prevX - center.x) * sinA + (prevY - center.y) * cosA + center.y;
    }
  }

  bool Polygon::isConvex()
  {
    for (size_t i = 0; i < (pointsNum_ - 1); ++i)
    {
      double pos1 = (points_[i + 1].y - points_[i].y) * (points_[0].x - points_[i].x)
        - (points_[i + 1].x - points_[i].x) * (points_[0].y - points_[i].y);
      double pos2 = 0;
      for (size_t j = 1; j < pointsNum_; ++j)
      {
        pos2 = (points_[i + 1].y - points_[i].y) * (points_[j].x - points_[i].x)
          - (points_[i + 1].x - points_[i].x) * (points_[j].y - points_[i].y);
        if (pos2 * pos1 >= 0)
        {
          pos1 = pos2;
        }
        else
        {
          return false;
        }
      }
    }
    return true;
  }

  void Polygon::calculateCenter()
  {
    double x = 0, y = 0;
    for (size_t i = 0; i < pointsNum_; i++)
    {
      x += points_[i].x;
      y += points_[i].y;
    }
    pos_ = { x / pointsNum_, y / pointsNum_ };
  }
}

#include "triangle.hpp"
#include <cmath>

Triangle::Triangle(const point_t& top1, const point_t& top2, const point_t& top3) :
    top1_(top1),
    top2_(top2),
    top3_(top3)
{
  double a = (top1_.x - top2_.x) * (top1_.x - top2_.x) + (top1_.y - top2_.y) * (top1_.y - top2_.y);
  double b = (top2_.x - top3_.x) * (top2_.x - top3_.x) + (top2_.y - top3_.y) * (top2_.y - top3_.y);
  double c = (top3_.x - top1_.x) * (top3_.x - top1_.x) + (top3_.y - top1_.y) * (top3_.y - top1_.y);

  if (a < 0 || b < 0 || c < 0)
  {
    throw std::invalid_argument("Invalid triangle vertex");
  }

  double aSqrt = sqrt(a);
  double bSqrt = sqrt(b);
  double cSqrt = sqrt(c);

  if (aSqrt + bSqrt < cSqrt || aSqrt + cSqrt < bSqrt || bSqrt + cSqrt < aSqrt)
  {
    throw std::invalid_argument("Invalid triangle vertex");
  }
}

double Triangle::getArea() const
{
  double aSqrt = sqrt((top1_.x - top2_.x) * (top1_.x - top2_.x) + (top1_.y - top2_.y) * (top1_.y - top2_.y));
  double bSqrt = sqrt((top2_.x - top3_.x) * (top2_.x - top3_.x) + (top2_.y - top3_.y) * (top2_.y - top3_.y));
  double cSqrt = sqrt((top3_.x - top1_.x) * (top3_.x - top1_.x) + (top3_.y - top1_.y) * (top3_.y - top1_.y));
  double p = (aSqrt + bSqrt + cSqrt) / 2;

  return sqrt(p * (p - aSqrt) * (p - bSqrt) * (p - cSqrt));
}

rectangle_t Triangle::getFrameRect() const
{
  double xMin = std::min(top1_.x, std::min(top2_.x, top3_.x));
  double xMax = std::max(top1_.x, std::max(top2_.x, top3_.x));
  double yMin = std::min(top1_.y, std::min(top2_.y, top3_.y));
  double yMax = std::max(top1_.y, std::max(top2_.y, top3_.y));

  return rectangle_t{
      xMax - xMin, yMax - yMin,
      point_t{xMin + (xMax - xMin) / 2, yMin + (yMax - yMin) / 2}
  };
}

void Triangle::move(const point_t& point)
{
  double xCenter = (top1_.x + top2_.x + top3_.x) / 3;
  double yCenter = (top1_.y + top2_.y + top3_.y) / 3;

  double xAxis = point.x - xCenter;
  double yAxis = point.y - yCenter;

  top1_.x += xAxis;
  top1_.y += yAxis;
  top2_.x += xAxis;
  top2_.y += yAxis;
  top3_.x += xAxis;
  top3_.y += yAxis;
}

void Triangle::move(double xAxis, double yAxis)
{
  top1_.x += xAxis;
  top1_.y += yAxis;
  top2_.x += xAxis;
  top2_.y += yAxis;
  top3_.x += xAxis;
  top3_.y += yAxis;
}

void Triangle::print() const
{
  std::cout << "vertex 1.x = " << top1_.x << " vertex 1.y = " << top1_.y << " vertex 2.x = " << top2_.x
            << " vertex 2.y = " << top2_.y << " vertex 3.x = " << top3_.x << " vertex 3.y = " << top3_.y << std::endl;
}

void Triangle::printFrameRectangle() const
{
  rectangle_t rect = getFrameRect();

  std::cout << "height = " << rect.height << " width = " << rect.width << " center.x = " << rect.pos.x << " center.y = "
            << rect.pos.y << std::endl;
}

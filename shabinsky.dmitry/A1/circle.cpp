//
// Created by sdimosik on 21.03.2020.
//
#include "circle.hpp"
#include <stdexcept>
#include <cmath>

Circle::Circle(double radius, const point_t &position)
{
    if (radius <= 0)
    {
        throw std::invalid_argument("Radius must be positive");
    }

    radius_ = radius;
    position_ = position;
}

double Circle::getRadius() const
{
    return radius_;
}

point_t Circle::getPosition() const
{
    return position_;
}

double Circle::getArea() const
{
    return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
    return rectangle_t{2 * radius_, 2 * radius_, position_};
}

void Circle::move(const point_t &position)
{
    position_ = position;
}

void Circle::move(double x, double y)
{
    position_ = {x + position_.x, y + position_.y};
}

//
// Created by sdimosik on 21.03.2020.
//
#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const point_t &position, double width, double height)
{
    if (width <= 0 && height <= 0)
    {
        throw std::invalid_argument("Height and Width must be positive");
    }
    position_ = position;
    width_ = width;
    height_ = height;
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
    return rectangle_t{width_, height_, position_};
}

void Rectangle::move(const point_t &position)
{
    position_ = position;
}

void Rectangle::move(double x, double y)
{
    position_ = {x + position_.x, y + position_.y};
}

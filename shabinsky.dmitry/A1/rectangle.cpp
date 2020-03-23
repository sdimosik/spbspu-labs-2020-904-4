#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t &position, double width, double height) :
  position_(position),
  width_(width),
  height_(height)
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
    return rectangle_t{width_, height_, position_};
}

void Rectangle::move(const point_t &position)
{
    position_ = position;
}

void Rectangle::move(double x, double y)
{
    position_.x += x;
    position_.y += y;
}

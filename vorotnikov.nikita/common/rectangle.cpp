#include <string>
#include <stdexcept>
#include "rectangle.h"

namespace vorotnikov {
  Rectangle::Rectangle(double width, double height, const point_t &pos) :
    width_(width),
    height_(height),
    pos_(pos)
  {
    if (width_ <= 0.0 || height_ <= 0.0) {
      throw std::invalid_argument(std::string("Invalid parameter: width and height should be positive: width = "
          + std::to_string(width_) + ", height = " + std::to_string(height_)));
    }
  }

  double Rectangle::getArea() const {
    return height_ * width_;
  }

  rectangle_t Rectangle::getFrameRect() const {
    return rectangle_t{width_, height_, pos_};
  }

  void Rectangle::move(const point_t &point) {
    pos_ = point;
  }

  void Rectangle::move(double x, double y) {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::scale(double value) {
    if (value <= 0) {
      throw std::invalid_argument(std::string("Value must be positive, value = "
          + std::to_string(value)));
    }
    width_ *= value;
    height_ *= value;
  }
}

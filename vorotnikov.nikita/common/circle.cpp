#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <string>
#include "circle.hpp"

namespace vorotnikov {
  Circle::Circle(double radius, const point_t &pos) :
    radius_(radius),
    pos_(pos)
  {
    if (radius_ <= 0.0) {
      throw std::invalid_argument(std::string("Invalid parameter: radius should be positive, radius = "
          + std::to_string(radius_)));
    }
  }

  double Circle::getArea() const {
    return M_PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const {
    return rectangle_t{2.0 * radius_, 2.0 * radius_, pos_};
  }

  void Circle::move(double x, double y) {
    pos_.x += x;
    pos_.y += y;
  }

  void Circle::move(const point_t &point) {
    pos_ = point;
  }

  void Circle::scale(double value) {
    if (value <= 0) {
      throw std::invalid_argument(std::string("Value must be positive, value = "
          + std::to_string(value)));
    }
    radius_ *= value;
  }

  void Circle::rotate(const double) noexcept {

  }
}

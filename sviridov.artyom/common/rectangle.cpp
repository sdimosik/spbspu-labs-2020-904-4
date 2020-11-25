#include "rectangle.hpp"
#include <iostream>
namespace sviridov
{
  double Rectangle::getArea() const
  {
    return vertex_[0].getDistance(vertex_[1]) * vertex_[0].getDistance(vertex_[2]);
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    rectangle_t frame_rectangle = {{vertex_[2].x + (vertex_[1].x - vertex_[0].x),
        vertex_[2].y + (vertex_[1].y - vertex_[0].y)}, 0, 0};
    for (int i = 0; i < 3; i++)
    {
      frame_rectangle.expandRect(vertex_[i]);
    }
    return frame_rectangle;
  }

  Rectangle::Rectangle(const point_t &pos, double height, double width) :
      vertex_{{pos.x - height / 2, pos.y - width / 2},
                    {pos.x - height / 2, pos.y + width / 2},
                    {pos.x + height / 2, pos.y - width / 2}}
  {
    if ((height <= 0) || (width <= 0))
    {
       throw std::invalid_argument("No correct arguments for construct rectangle");
    }
  }

  void Rectangle::printInform(std::ostream &out) const
  {
    point_t center = Rectangle::getFrameRect().pos;
    out << "Rectangle " << "pos = " << center.x << " "
        << center.y << " height " << vertex_[0].getDistance(vertex_[2])
        << " width = " << vertex_[0].getDistance(vertex_[1]);
  }


  std::ostream &operator<<(std::ostream &out, const Rectangle &out_rect)
  {
    out_rect.printInform(out);
    return out;
  }

  void Rectangle::move(const point_t &pos)
  {
    point_t center = Rectangle::getFrameRect().pos;
    Rectangle::move(pos.x - center.x, pos.y - center.y);
  }

  void Rectangle::move(double dx, double dy)
  {
    for (int i = 0; i < 3; i++)
    {
      vertex_[i].x += dx;
      vertex_[i].y += dy;
    }
  }

  void Rectangle::scale(double coefficient)
  {
    point_t center = Rectangle::getFrameRect().pos;
    if ((coefficient > 0) && (coefficient != 1))
    {
      for (int i = 0; i < 3; i++)
      {
        vertex_[i] = {center.x + (vertex_[i].x - center.x) * coefficient,
            center.y + (vertex_[i].y - center.y) * coefficient};
      }
    } else if (coefficient != 1)
    {
      throw std::invalid_argument("No correct arguments for scale rectangle");
    }
  }
  bool operator==(const Rectangle & rect1, const Rectangle & rect2)
  {
        return ((rect1.vertex_[0] == rect2.vertex_[0]) && (rect1.vertex_[1] == rect2.vertex_[1])
                && (rect1.vertex_[2] == rect2.vertex_[2]));
  }
}

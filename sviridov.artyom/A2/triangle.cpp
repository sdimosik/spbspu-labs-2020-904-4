#include "triangle.hpp"
#include <cmath>
namespace sviridov
{
  double Triangle::getArea() const
  {
    return fabs(0.5 * ((vertex_[0].x - vertex_[2].x) * (vertex_[1].y - vertex_[2].y)
        - (vertex_[1].x - vertex_[2].x) * (vertex_[0].y - vertex_[2].y)));
  }


  rectangle_t Triangle::getFrameRect() const
  {
    rectangle_t frame_rectangle = {vertex_[0], 0, 0};
    frame_rectangle.expandRect(vertex_[1]);
    frame_rectangle.expandRect(vertex_[2]);
    return frame_rectangle;
  }

  Triangle::Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c) :
      vertex_{pos_a, pos_b, pos_c}
    {
      if (getArea() == 0)
      {
          throw std::invalid_argument("No correct arguments for construct triangle");
      }
  }


  void Triangle::move(const point_t &end_pos)
  {
    point_t center = Triangle::getFrameRect().pos;
    Triangle::move(end_pos.x - center.x, end_pos.y - center.y);
  }

  void Triangle::move(double dx, double dy)
  {
    for (int i = 0; i < 3; i++)
    {
      vertex_[i].x += dx;
      vertex_[i].y += dy;
    }
  }

  void Triangle::printInform(std::ostream &out) const
  {
    out << "Triangle "
    << " A:(" << vertex_[0].x << ';' << vertex_[0].y
    << ") B:(" << vertex_[1].x << ';' << vertex_[1].y
    << ") C:(" << vertex_[2].x << ';' << vertex_[2].y << ")";
  }

  std::ostream &operator<<(std::ostream &out, const Triangle &out_triangle)
  {
    out_triangle.printInform(out);
    return out;
  }

  void Triangle::scale(double coefficient)
  {
    point_t center = Triangle::getFrameRect().pos;
      if ((coefficient > 0) && (coefficient != 1))
      {
        for (int i = 0; i < 3; i++)
        {
         vertex_[i] = {center.x + (vertex_[i].x - center.x) * coefficient,
             center.y + (vertex_[i].y - center.y) * coefficient};
        }
      } else if (coefficient != 1)
      {
        throw std::invalid_argument("No correct arguments for scale triangle");
      }
  }
  point_t Triangle::getPosVertexA() const
  {
    return vertex_[0];
  }

  point_t Triangle::getPosVertexB() const
  {
    return vertex_[1];
  }

  point_t Triangle::getPosVertexC() const
  {
    return vertex_[2];
  }
}

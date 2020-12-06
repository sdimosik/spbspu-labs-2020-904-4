#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"
namespace sviridov
{
  class Triangle : public Shape
  {
  public:
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    Triangle(const point_t&, const point_t&, const point_t&);
    friend std::ostream& operator<<(std::ostream&, const Triangle&);
    void move(const point_t&) override;
    void move(double, double) override;
    void scale(double) override;
    point_t getPosVertexA() const;
    point_t getPosVertexB() const;
    point_t getPosVertexC() const;
    friend bool operator==(const Triangle&, const Triangle&);
  private:
    point_t vertex_[3];
    void printInform(std::ostream&) const override;
  };
  std::ostream& operator<<(std::ostream&, const Triangle&);
  bool operator==(const Triangle&, const Triangle&);
}
#endif

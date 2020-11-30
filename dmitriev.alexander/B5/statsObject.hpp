#ifndef STATSOBJECT_HPP
#define STATSOBJECT_HPP

#include "shape.hpp"

class StatsObject
{
public:

  StatsObject();

  void operator()(Shape &);

  friend std::ostream &operator<<(std::ostream &, const StatsObject &);

private:
  size_t verticesCount_;
  size_t triangleCount_;
  size_t squareCount_;
  size_t rectangleCount_;

};

#endif

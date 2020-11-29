#ifndef SPBSPU_LABS_2020_904_4_OBJECTSTATS_HPP
#define SPBSPU_LABS_2020_904_4_OBJECTSTATS_HPP

#include "shape.hpp"

class ObjectStats
{
public:

  ObjectStats();

  void operator()(Shape &);

  friend std::ostream &operator<<(std::ostream &, const ObjectStats &);

private:
  size_t topsCount_;
  size_t triangleCount_;
  size_t squareCount_;
  size_t rectangleCount_;

};

#endif

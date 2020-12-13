#ifndef SHAPE_PTR_HPP
#define SHAPE_PTR_HPP
#include <memory>
#include "shape.hpp"

Shape::ShapePtr creatShapePtr(const std::string& name, const Point& center);
std::ostream& operator <<(std::ostream& out, const Shape::ShapePtr& shape);
std::istream& operator >>(std::istream& in, Shape::ShapePtr& shape);
std::ostream& operator <<(std::ostream& out, const Shape::ConstShapePtr& shape);
std::istream& operator >>(std::istream& in, Shape::ConstShapePtr& shape);

#endif

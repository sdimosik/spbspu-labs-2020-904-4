#ifndef B5_TASK_FUNC_HPP
#define B5_TASK_FUNC_HPP

#include "shape.hpp"

int count_vertices(Shapes& shapes);
int count_triangles(Shapes& shapes);
int count_rectangles(Shapes& shapes);
int count_squares(Shapes& shapes);
void delete_pentagons(Shapes& shapes);
std::vector<Point> create_point_vec(Shapes& shapes);

#endif //B5_TASK_FUNC_HPP

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"
namespace anastasiev
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix&);
    Matrix(Matrix&&)  = default;
    ~Matrix() = default;
    Matrix& operator=(const Matrix&);
    Matrix& operator=(Matrix&&)  = default;
    void addShape(const std::shared_ptr<Shape>&);
    std::shared_ptr<Shape>& getShape(unsigned int row, unsigned int column);
  private:
    bool isOverlapping(const std::shared_ptr<Shape>&, const std::shared_ptr<Shape>&) const;
    unsigned int rows_;
    unsigned int columns_;
    std::unique_ptr<std::shared_ptr<Shape>[]> elements_;
  };
}
#endif

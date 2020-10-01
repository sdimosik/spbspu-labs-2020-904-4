#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace kundik
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    std::shared_ptr<Shape>& getShape(size_t row, size_t col);
    void addShape(const std::shared_ptr<Shape>& shape);
  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;
    size_t rows_;
    size_t cols_;
    bool isLapping(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2) const noexcept;
  };
}
#endif

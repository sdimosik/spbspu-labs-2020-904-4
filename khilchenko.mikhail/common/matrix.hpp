#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace khilchenko
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix &other);
    Matrix& operator=(Matrix&& other) noexcept;
    void addShape(const std::shared_ptr<Shape>& shape);
    std::shared_ptr<Shape>& getShape(size_t row, size_t column);
    size_t getAmountOfRows()const noexcept;
    size_t getAmountOfColoumns()const noexcept;
  private:
    using arrayPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    size_t amountOfRows_;
    size_t amountOfColumns_;
    arrayPtr matrix_;

    bool isShapesOverlaped(const std::shared_ptr<Shape>& first, const std::shared_ptr<Shape>& second);
  }; 
}

#endif

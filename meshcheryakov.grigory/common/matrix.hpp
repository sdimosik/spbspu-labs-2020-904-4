#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include "shape.hpp"

namespace meshcheryakov
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      friend class Matrix;
      std::shared_ptr<Shape> &operator[](size_t index);

    private:
      Layer(std::shared_ptr<Shape> *shapes,size_t size);

      std::shared_ptr<Shape> *shapes_;
      size_t size_;
    };

    Matrix();
    Matrix(const Matrix &otherMatrix);
    Matrix(Matrix &&otherMatrix) noexcept;
    ~Matrix() = default;
    Matrix &operator=(const Matrix &otherMatrix);
    Matrix &operator=(Matrix &&otherMatrix) noexcept;
    void addShape(const std::shared_ptr<Shape> &shape);
    Matrix::Layer operator[](const size_t index);
    size_t getRows() const noexcept;
    size_t getColumns() const noexcept;

  private:
    using matrixPtr = std::unique_ptr<std::shared_ptr<Shape>[]>;
    matrixPtr matrix_;
    size_t columns_;
    size_t rows_;

    bool checkOverLapping(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2) const noexcept;
  };
}

#endif //MATRIX_H

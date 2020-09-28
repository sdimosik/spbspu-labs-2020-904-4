#ifndef USHAKOV_A_MATRIX_HPP
#define USHAKOV_A_MATRIX_HPP

#include "memory"
#include "shape.hpp"

namespace ushakov
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      friend class Matrix;

      std::shared_ptr<Shape>& operator[](size_t index);

    private:
      Layer(std::shared_ptr<Shape> *shapes, size_t size);

      std::shared_ptr<Shape> *shapes_;
      size_t size_;
    };

    Matrix();

    Matrix(const Matrix& matrix);

    Matrix(Matrix&& matrix) noexcept;

    ~Matrix() = default;

    Matrix& operator=(const Matrix& matrix);

    Matrix& operator=(Matrix&& matrix) noexcept;

    Matrix::Layer operator[](size_t index);

    void addShape(const std::shared_ptr<Shape>& shape);

    size_t getRows() const noexcept;

    size_t getColumns() const noexcept;

    void print() const noexcept;

  private:
    using matrixElement = std::unique_ptr<std::shared_ptr<Shape>[]>;

    matrixElement elements_;
    size_t rows_;
    size_t columns_;

    static bool isIntersecting(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2) noexcept;
  };
}

#endif //USHAKOV_A_MATRIX_HPP

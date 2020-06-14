#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace bakaeva
{
  class Matrix
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;

    class Layer
    {
    public:
      friend class Matrix;

      shapePtr &operator[](size_t index);

    private:
      Layer(shapePtr *shapes, size_t size);

      shapePtr *shapes_;
      size_t size_;
    };

    Matrix();

    Matrix(const Matrix &other);

    Matrix(Matrix &&other) noexcept;

    ~Matrix() = default;

    Matrix &operator=(const Matrix &other);

    Matrix &operator=(Matrix &&other) noexcept;

    Matrix::Layer operator[](const size_t index);

    void addShape(const shapePtr &shape);

    size_t getRows() const noexcept;

    size_t getColumns() const noexcept;

    void printMatrix() const;

  private:
    using matrixElem = std::unique_ptr<shapePtr[]>;

    matrixElem elements_;
    size_t rows_;
    size_t columns_;

    bool isOverlapping(const shapePtr &shape1, const shapePtr &shape2) const noexcept;
  };
}

#endif

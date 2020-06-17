#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace spasoevich
{
  class Matrix
  {
  public:
    using shape_ptr = std::shared_ptr<Shape>;
    class Layer
    {
    public:
      friend class Matrix;
      shape_ptr& operator[] (size_t index);
    private:
      Layer(shape_ptr* arr, size_t size);
      size_t size_;
      shape_ptr* arr_;
    };
    Matrix();
    Matrix(const Matrix& src);
    Matrix(Matrix&& rhs) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    Layer operator[](size_t row) const;
    void addShape(const shape_ptr& shape);
    size_t getRows() const;
    size_t getColumns() const;
    void printMatrixData() const;
  private:
    using shape_array = std::unique_ptr<shape_ptr[]>;
    size_t rows_;
    size_t columns_;
    shape_array figures_;
    bool isOverlapping(const shape_ptr& shape1, const shape_ptr& shape2) const noexcept;
  };
}

#endif

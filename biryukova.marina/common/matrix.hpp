#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace biryukova
{
  class Matrix
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;
    using shapesArray = std::unique_ptr<shapePtr[]>;
    class Layer
    {
    public:
      friend class Matrix;
      ~Layer() = default;
      shapePtr& operator[](size_t index);
    private:
      shapePtr* array_;
      size_t size_;
      Layer(shapePtr* array, size_t size);
      Layer(const Layer& l) = default;
      Layer(Layer&& l) = default;
      Layer& operator=(const Layer& l) = default;
      Layer& operator=(Layer&& l) = default;

    };
    Matrix();
    Matrix(const Matrix& m);
    Matrix(Matrix&& m) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix& m);
    Matrix& operator=(Matrix&& m) noexcept;
    Layer operator[](size_t index) const;
    size_t getRows() const noexcept;
    size_t getColumns() const noexcept;
    void insert(shapePtr shape);
  private:
    size_t rows_;
    size_t columns_;
    shapesArray shapes_;
    void insert(shapePtr shape, size_t row, size_t column);
  };
}

#endif

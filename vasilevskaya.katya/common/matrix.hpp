#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace vasilevskaya
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      Shape::PointToShape& operator[](size_t index) const;

    private:
      friend Matrix;
      const Matrix& matrix_;
      size_t numberLayer_;
      Layer(const Matrix& matrix, size_t countShapeInLayer);
    };

    Matrix();
    Matrix(const Matrix& copiedMatrix);
    Matrix(Matrix&& portableMatrix) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix& copiedMatrix);
    Matrix& operator=(Matrix&& portableMatrix) noexcept;
    Layer operator[](size_t index) const;
    size_t getSizeMatrix() const;
    size_t getColumn() const;
    size_t getLine() const;
    void addShape(const Shape::PointToShape& newShape);
    void printMatrix() const;

  private:
    std::unique_ptr<Shape::PointToShape[]> arrayMatrix_;
    size_t column_;
    size_t line_;
    size_t getNumberOfLayerForInsert(const Shape::PointToShape& newShape) const;
    void extendMatrixInWidth();
    void extendMatrixInHeight();
    size_t findEmptyPlaceInLayer(size_t layer) const;
  };
}

#endif

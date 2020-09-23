#ifndef MATRIX
#define MATRIX

#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace kichigin
{
  class Matrix
  {
  public:
    Matrix(unsigned int layerFullSize = 0);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) = default;
    ~Matrix() = default;
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) = default;
    std::shared_ptr<Shape> getShape(unsigned int row, unsigned int column) const;
    void addShape(const std::shared_ptr<Shape>& shape);
    void addCompositeShape(const std::shared_ptr<CompositeShape>& compShape);
    unsigned int getFullSize() const noexcept;
    unsigned int getLayersNumber() const noexcept;
    unsigned int getLayerFullSize() const noexcept;
    unsigned int getLayerCurrentSize(unsigned int index) const;
  private:
    using arrayType = std::unique_ptr<std::shared_ptr<Shape>[]>;
    arrayType matrix_;
    unsigned int matrixFullSize_;
    unsigned int layerFullSize_;
    bool isShapeOverclaped(const std::shared_ptr<Shape>& first, const std::shared_ptr<Shape>& second);
  };
}

#endif//!MATRIX

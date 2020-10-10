#ifndef MATRIX
#define MATRIX

#include <ctime>
#include <iostream>
#include <memory>
#include "shape.hpp"

namespace brezho
{
  class Matrix
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;
    class Layer
    {
    public:
      friend class Matrix;
      ~Layer() = default; 
      shapePtr& operator[](size_t index);

    private:
      Layer(shapePtr* layer, size_t size);
      Layer(const Layer& layer) = default; 
      Layer(Layer&& layer) = default; 
      Layer& operator=(Layer&& layer) = default; 
      Layer& operator=(Layer& layer) = default; 
      shapePtr* layer_;
      size_t size_;
    };
    Matrix() noexcept;
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) = default;
    ~Matrix() = default;
    Matrix::Layer operator[](size_t index);
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) = default;
    void addShape(const shapePtr& shape);
    size_t getLayerSize() const noexcept;
    size_t getLayerCapacity() const noexcept;
    size_t getShapeCount(size_t layerNumber) const;
    void printMatrixAreas(std::ostream& out);

  private:
    void increaseLayerSize();
    void addLayer();
    using matrixPtr = std::unique_ptr<shapePtr[]>;
    matrixPtr matrix_;
    size_t layerUsedSize_;
    size_t layerFullSize_;
    std::unique_ptr<size_t[]> usedSize_;
    size_t fullSize_;
    static bool isSuperimposed(const shapePtr& shape1, const shapePtr& shape2);
  };
}

#endif

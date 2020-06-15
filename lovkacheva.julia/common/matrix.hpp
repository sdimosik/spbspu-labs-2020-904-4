#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace lovkacheva
{
  class Matrix
  {
  public:
    using ShapePtr = std::shared_ptr<Shape>;
    using ShapeArray = std::unique_ptr<ShapePtr[]>;
    using SizeArray = std::unique_ptr<size_t[]>;

    class Layer
    {
    public:
      friend class Matrix;
      ~Layer() = default;

      ShapePtr operator[](size_t index);

    private:
      ShapeArray* layerContents_;
      size_t beginIndex_;
      size_t size_;

      Layer(const Layer& other) = default;

      Layer(Layer&& other) = default;

      Layer(ShapeArray* contents,size_t beginIndex ,size_t size);

      Layer& operator=(const Layer& other) = default;

      Layer& operator=(Layer&& other) = default;
    };

    Matrix();

    Matrix(const Matrix& other);

    Matrix(Matrix&& other) = default;

    ~Matrix() = default;

    Matrix& operator=(const Matrix& other);

    Matrix& operator=(Matrix&& other) = default;

    Layer operator[](size_t index);

    void addShape(const ShapePtr& shape);

    size_t getLayerSize(size_t index) const;

    size_t getRows() const noexcept;

    size_t getColumns() const noexcept;

  private:
    SizeArray layerSizes_;
    size_t layerCapacity_;
    size_t layerNumber_;
    size_t maxLayerNumber_;
    ShapeArray contents_;
    const static int GROWTH_FACTOR = 2;

    void increaseMaxLayerNumber();
    void increaseLayerCapacity();

    bool doIntersect(const ShapePtr& first, const ShapePtr& second) const noexcept;
  };
}
#endif

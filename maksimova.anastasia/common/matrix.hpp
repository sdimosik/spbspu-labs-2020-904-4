#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace maksimova
{
  class Matrix
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;
    using matrixPtr = std::unique_ptr<shapePtr[]>;
    class Layer
    {
    public:
      friend class Matrix;
      shapePtr& operator[] (size_t index);

    private:
      Layer(shapePtr* shape, size_t size);
      shapePtr* shape_;
      size_t size_;
    };

    Matrix();

    Matrix(const Matrix& element);

    Matrix(Matrix&& element);

    ~Matrix() = default;

    Matrix &operator=(const Matrix & element);

    Matrix &operator=(Matrix && element) = default;

    Layer operator[](const size_t index);

    void addElement(const shapePtr& shape);

    size_t getLevels() const noexcept;

    size_t getColumns() const noexcept;

    void printInf() const;

  private:
    size_t levels_;
    size_t columns_;
    matrixPtr figure_;

    bool check_above(const shapePtr &shape1, const shapePtr &shape2) const noexcept;
  };
}

#endif

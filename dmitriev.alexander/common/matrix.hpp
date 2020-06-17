#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace dmitriev
{
  class Matrix
  {
  public:
    Matrix();

    Matrix(const Matrix &other);

    Matrix(Matrix &&other) noexcept;

    ~Matrix() = default;

    Matrix &operator=(const Matrix &other);

    Matrix &operator=(Matrix &&other) noexcept = default;

    std::shared_ptr<Shape> &getShape(size_t row, size_t column);

    void addShape(const std::shared_ptr<Shape> &shape);

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> items_;
    size_t rows_;
    size_t columns_;

    bool isOverlapping(const std::shared_ptr<Shape> &first, const std::shared_ptr<Shape> &second) const;
  };
}

#endif //SPBSPU_LABS_2020_904_4_MATRIX_HPP

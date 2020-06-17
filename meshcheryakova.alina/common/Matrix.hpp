#ifndef LABS_SPBPU_MATRIX_HPP
#define LABS_SPBPU_MATRIX_HPP

#include <memory>
#include "composite-shape.hpp"

namespace meshcheryakova
{
  class Matrix
  {
  public:
    using shape_ptr = std::shared_ptr<Shape>;
    using shape_array = std::unique_ptr<shape_ptr[]>;

    Matrix();
    Matrix(const Matrix& other_matrix);
    Matrix(Matrix&& other_matrix) noexcept;
    ~Matrix() = default;
    Matrix& operator =(const Matrix& other_matrix);
    Matrix& operator =(Matrix&& other_matrix) noexcept;

    void separate(CompositeShape &compShape);
    bool isOverlay(const shape_ptr &first, const shape_ptr &second_shape) const;

    shape_ptr &getShape(const size_t row, const size_t column) ;
    size_t getRows() const noexcept;
    size_t getColumns() const noexcept;

  private:
    size_t rows_;
    size_t columns_;
    shape_array list_of_shapes_;

    void separate(const shape_array &array, const size_t size);
    void add(std::shared_ptr<Shape> &shape, size_t row, size_t column);
  };
}

#endif //LABS_SPBPU_MATRIX_HPP

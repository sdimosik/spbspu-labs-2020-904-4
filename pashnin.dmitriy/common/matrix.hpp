
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace pashnin
{
  class Matrix
  {
  public:
    using shapePtr = std::shared_ptr<Shape>;
    
    Matrix();
    
    Matrix(const Matrix &other);
    
    Matrix(Matrix &&other) noexcept;
    
    ~Matrix() = default;
    
    Matrix &operator=(const Matrix &other);
    
    Matrix &operator=(Matrix &&other) noexcept = default;
    
    shapePtr &getShape(size_t row, size_t column);
    
    void addShape(const shapePtr &shape);
  
  private:
    std::unique_ptr<shapePtr[]> items_;
    size_t rows_;
    size_t columns_;
    
    bool isOverlapping(const shapePtr &first, const shapePtr &second) const;
  };
}

#endif

//
// Created by sdimosik on 24.05.2020.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace shabinsky
{
  class Matrix
  {
  public:
    using shapePtr = std::shared_ptr<shabinsky::Shape>;
    using matrixPtr = std::unique_ptr<shapePtr[]>;
    
    Matrix();
    
    Matrix(const Matrix &matrix);
    
    Matrix(Matrix &&matrix) noexcept;
    
    void add(const shapePtr &shape);
    
    void remove(size_t layerNumber, size_t shapeNumberInLayer);
    
    void print() const;
    
    size_t getRows() const;
    
    size_t getColumns() const;
    
    size_t getSize() const;
    
    matrixPtr::pointer operator[](size_t index) const;
  
  private:
    matrixPtr elements_;
    size_t rows_;
    size_t columns_;
    
    static bool isOverlay(const shapePtr &shape1, const shapePtr &shape2);
  };
}

#endif //MATRIX_HPP

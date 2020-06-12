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
    
    class Layer
    {
    public:
      friend class Matrix;
      
      shapePtr &operator[](size_t index);
    
    private:
      Layer(shapePtr *shapes, size_t size);
      
      Layer(const Layer &layer) = default;
  
      Layer(Layer && layer) = default;
      
      shapePtr *shapes_;
      size_t size_;
    };
    
    Matrix();
    
    Matrix(const Matrix &matrix);
    
    Matrix(Matrix &&matrix) noexcept;
    
    ~Matrix() = default;
    
    Layer operator[](size_t index);
    
    void add(const shapePtr &shape);
    
    void remove(size_t layerNumber, size_t shapeNumberInLayer);
    
    void print() const;
    
    size_t getRows() const;
    
    size_t getColumns() const;
    
    size_t getSize() const;
  
  private:
    matrixPtr elements_;
    size_t rows_;
    size_t columns_;
    
    static bool isOverlay(const shapePtr &shape1, const shapePtr &shape2);
  };
}

#endif //MATRIX_HPP

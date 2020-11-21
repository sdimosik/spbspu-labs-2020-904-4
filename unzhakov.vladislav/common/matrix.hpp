#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace unzhakov
{
  class Matrix
  {
  public:
    class ConstLayer
    {
    public:
      const Shape::SharedPtr operator[](size_t index) const;
      size_t getSize() const;
    protected:
      size_t index_;
    private:
      friend class Matrix;
      const Matrix *layer_;
      ConstLayer(const Matrix *elem, size_t index);
    };

    class Layer : public ConstLayer
    {
    public:
      void add(const Shape::SharedPtr &shape);
    private:
      friend class Matrix;
      Matrix *layer_;
      Layer(Matrix *elem, size_t index);
    };

    Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other);
    ~Matrix() = default;

    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other);
    Layer operator[](size_t index);
    const ConstLayer operator[](size_t index) const;
    size_t getRow() const;
    void addLayer();
  private:
    friend class Layer;
    friend class ConstLayer;
    size_t lines_;
    size_t columns_;
    std::unique_ptr<Shape::SharedPtr []> elements_;
    void addInMatrix(const Shape::SharedPtr &shape, size_t index);
  };
}

#endif


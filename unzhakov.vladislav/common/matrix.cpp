#include "matrix.hpp"
#include <cmath>
#include <memory>
#include <stdexcept>
#include "base-types.hpp"

unzhakov::Matrix::Matrix():
  lines_(0),
  columns_(0),
  elements_(nullptr)
{}

unzhakov::Matrix::Matrix(const Matrix &other):
  lines_(other.lines_),
  columns_(other.columns_),
  elements_(nullptr)
{
  if (other.lines_)
  {
    elements_ = std::make_unique<Shape::SharedPtr[]>(other.lines_ * other.columns_);
    for (size_t i = 0; i < lines_; i++)
    {
      elements_[i] = other.elements_[i];
    }
  }
}

unzhakov::Matrix::Matrix(Matrix &&other):
  lines_(other.lines_),
  columns_(other.columns_),
  elements_(std::move(other.elements_))
{
  other.lines_ = 0;
  other.columns_ = 0;
}

unzhakov::Matrix &unzhakov::Matrix::operator=(const Matrix &other)
{
  if (this == &other)
  {
    return *this;
  }
  if (other.lines_ == 0)
  {
    lines_ = 0;
    columns_ = 0;
    elements_ = nullptr;
    return *this;
  }
  std::unique_ptr<Shape::SharedPtr[]> temp = std::make_unique<Shape::SharedPtr[]>(other.lines_ * other.columns_);
  for (size_t i = 0; i < other.lines_ * other.columns_; i++)
  {
    temp[i] = other.elements_[i];
  }
  lines_ = other.lines_;
  columns_ = other.columns_;
  elements_ = std::move(temp);
  return *this;
}

unzhakov::Matrix &unzhakov::Matrix::operator=(Matrix &&other)
{
  if (this == &other)
  {
    return *this;
  }
  lines_ = other.lines_;
  columns_ = other.columns_;
  elements_ = std::move(other.elements_);
  other.lines_ = 0;
  other.columns_ = 0;
  return *this;
}

unzhakov::Matrix::Layer unzhakov::Matrix::operator[](size_t index)
{
  if (index >= lines_)
  {
    throw std::out_of_range("Index must be less");
  }
  return Layer(this, index);
}

const unzhakov::Matrix::ConstLayer unzhakov::Matrix::operator[](size_t index) const
{
  if (index >= lines_)
  {
    throw std::out_of_range("Index must be less");
  }
  return ConstLayer(this, index);
}

size_t unzhakov::Matrix::ConstLayer::getSize() const
{
  size_t size = 0;
  for (size_t i = 0; (i < layer_->columns_) && (layer_->elements_[index_ * layer_->columns_ + i]); i++)
  {
    size++;
  }
  return size;
}

size_t unzhakov::Matrix::getRow() const
{
  return lines_;
}

void unzhakov::Matrix::addLayer()
{
  std::unique_ptr<Shape::SharedPtr[]> tempMatrix(std::make_unique<Shape::SharedPtr[]>(columns_ * (lines_ + 1)));
  for (size_t i = 0; i < lines_ * columns_; i++)
  {
    tempMatrix[i] = std::move(elements_[i]);
  }
  elements_ = std::move(tempMatrix);
  lines_++;
}

void unzhakov::Matrix::addInMatrix(const Shape::SharedPtr &shape, size_t index)
{
  std::unique_ptr<Shape::SharedPtr[]> tempMatrix;
  size_t length = (*this)[index].getSize();
  if (lines_ == 0)
  {
    lines_++;
  }
  tempMatrix = std::make_unique<Shape::SharedPtr[]>((columns_ + 1) * lines_);
  for (size_t i = 0; i < lines_; i++)
  {
    for (size_t j = 0; j < columns_; j++)
    {
      tempMatrix[i * (columns_ + 1) + j] = std::move(elements_[i * columns_ + j]);
    }
  }
  elements_ = std::move(tempMatrix);
  columns_++;
  elements_[index * columns_ + length] = shape;
}

unzhakov::Matrix::ConstLayer::ConstLayer(const Matrix *elem, size_t index):
  index_(index),
  layer_(elem)
{}

void unzhakov::Matrix::Layer::add(const unzhakov::Shape::SharedPtr &shape)
{
  layer_->addInMatrix(shape, index_);
}

unzhakov::Matrix::Layer::Layer(Matrix *elem, size_t index):
  ConstLayer(elem, index),
  layer_(elem)
{}

const unzhakov::Shape::SharedPtr unzhakov::Matrix::ConstLayer::operator[](size_t index) const
{
  if (index >= layer_->columns_)
  {
    throw std::out_of_range("Index must be less");
  }
  return layer_->elements_[index_ * layer_->columns_ + index];
}

#include "matrix.hpp"
#include <cmath>

bool lovkacheva::Matrix::doIntersect(const ShapePtr& first, const ShapePtr& second) const noexcept
{
  if (!first || !second)
  {
    return false;
  }
  double distanceX = fabs(first->getFrameRect().pos.x - second->getFrameRect().pos.x);
  double distanceY = fabs(first->getFrameRect().pos.y - second->getFrameRect().pos.y);
  return (distanceX < ((first->getFrameRect().width + second->getFrameRect().width) / 2))
      && (distanceY < ((first->getFrameRect().height + second->getFrameRect().height) / 2));
}

lovkacheva::Matrix::Matrix() :
  layerSizes_(nullptr),
  layerCapacity_(0),
  layerNumber_(0),
  maxLayerNumber_(0),
  contents_(nullptr)
{}

lovkacheva::Matrix::Layer lovkacheva::Matrix::operator[](size_t index)
{
  if (index >= layerNumber_)
  {
    throw std::out_of_range("The layer index is out of range");
  }
  return Layer(&contents_, layerCapacity_ * index, layerSizes_[index]);
}

void lovkacheva::Matrix::addShape(const ShapePtr& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("The shape to be added cannot be a null pointer");
  }
  if (maxLayerNumber_ == 0)
  {
    ShapeArray tempContents = std::make_unique<ShapePtr[]>(1);
    SizeArray tempLayerSizes = std::make_unique<size_t[]>(1);
    maxLayerNumber_ = 1;
    layerNumber_ = 1;
    layerCapacity_ = 1;
    contents_ = std::move(tempContents);
    layerSizes_ = std::move(tempLayerSizes);
    layerSizes_[0] = 1;
    contents_[0] = shape;
  }
  else
  {
    size_t neededLayer = 0;
    for (size_t i = 0; i < layerNumber_; ++i)
    {
      for (size_t j = 0; j < layerSizes_[i]; ++j)
      {
        if (doIntersect(contents_[layerCapacity_ * i], shape))
        {
          neededLayer = i + 1;
          break;
        }
      }
    }
    if (neededLayer == layerNumber_)
    {
      if (layerNumber_ == maxLayerNumber_)
      {
        increaseMaxLayerNumber();
      }
      ++layerNumber_;
    }
    else if (layerSizes_[neededLayer] == layerCapacity_)
    {
      increaseLayerCapacity();
    }
    contents_[layerCapacity_ * neededLayer + layerSizes_[neededLayer]] = shape;
    ++layerSizes_[neededLayer];
  }
}

void lovkacheva::Matrix::increaseMaxLayerNumber()
{
  ShapeArray tempContents = std::make_unique<ShapePtr[]>((maxLayerNumber_ * GROWTH_FACTOR) * layerCapacity_);
  SizeArray tempLayerSizes = std::make_unique<size_t[]>(maxLayerNumber_ * GROWTH_FACTOR);
  for (size_t i = 0; i < layerNumber_; ++i)
  {
    tempLayerSizes[i] = layerSizes_[i];
    for (size_t j = 0; j < layerSizes_[i]; ++j)
    {
      tempContents[i * layerCapacity_ + j] = contents_[i * layerCapacity_ + j];
    }
  }
  maxLayerNumber_ *= GROWTH_FACTOR;
  contents_ = std::move(tempContents);
  layerSizes_ = std::move(tempLayerSizes);
}

void lovkacheva::Matrix::increaseLayerCapacity()
{
  ShapeArray tempContents = std::make_unique<ShapePtr[]>(maxLayerNumber_ * (GROWTH_FACTOR * layerCapacity_));
  for (size_t i = 0; i < layerNumber_; ++i)
  {
    for (size_t j = 0; j < layerSizes_[i]; ++j)
    {
      tempContents[i * GROWTH_FACTOR * layerCapacity_ + j] = contents_[i * layerCapacity_ + j];
    }
  }
  layerCapacity_ *= GROWTH_FACTOR;
  contents_ = std::move(tempContents);
}

lovkacheva::Matrix::Matrix(const lovkacheva::Matrix& other):
  layerSizes_(std::make_unique<size_t[]>(other.layerNumber_)),
  layerCapacity_(other.layerCapacity_),
  layerNumber_(other.layerNumber_),
  maxLayerNumber_(other.maxLayerNumber_),
  contents_(std::make_unique<ShapePtr[]>(other.maxLayerNumber_ * other.layerCapacity_))
{
  for (size_t i = 0; i < layerNumber_; ++i)
  {
    layerSizes_[i] = other.layerSizes_[i];
    for (size_t j = 0; j < layerSizes_[i]; ++j)
    {
      contents_[i * layerCapacity_ + j] = other.contents_[i * layerCapacity_ + j];
    }
  }
}

lovkacheva::Matrix& lovkacheva::Matrix::operator=(const lovkacheva::Matrix& other)
{
  if (this != &other)
  {
    SizeArray tempLayerSizes = std::make_unique<size_t[]>(other.layerNumber_);
    ShapeArray tempContents = std::make_unique<ShapePtr[]>(other.maxLayerNumber_ * other.layerCapacity_);
    layerCapacity_ = other.layerCapacity_;
    maxLayerNumber_ = other.maxLayerNumber_;
    layerNumber_ = other.layerNumber_;
    for (size_t i = 0; i < layerNumber_; ++i)
    {
      tempLayerSizes[i] = other.layerSizes_[i];
      for (size_t j = 0; j < tempLayerSizes[i]; ++j)
      {
        tempContents[i * layerCapacity_ + j] = other.contents_[i * layerCapacity_ + j];
      }
    }
    contents_ = std::move(tempContents);
    layerSizes_ = std::move(tempLayerSizes);
  }
  return *this;
}


size_t lovkacheva::Matrix::getRows() const noexcept
{
  return layerNumber_;
}

size_t lovkacheva::Matrix::getColumns() const noexcept
{
  size_t result = 0;
  for (size_t i = 0; i < layerNumber_; ++i)
  {
    if (layerSizes_[i] > result)
    {
      result = layerSizes_[i];
    }
  }
  return result;
}

size_t lovkacheva::Matrix::getLayerSize(size_t index) const
{
  if (index >= layerNumber_)
  {
    throw std::out_of_range("The layer index is out of range");
  }
  return layerSizes_[index];
}

lovkacheva::Matrix::Layer::Layer(lovkacheva::Matrix::ShapeArray* layerContents, size_t beginIndex, size_t size) :
  layerContents_(layerContents),
  beginIndex_(beginIndex),
  size_(size)
{ }

lovkacheva::Matrix::ShapePtr lovkacheva::Matrix::Layer::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("The shape index is out of range");
  }
  return (*layerContents_)[beginIndex_ + index];
}

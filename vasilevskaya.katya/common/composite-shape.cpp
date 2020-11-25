#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <memory>
#include <cmath>
#include "shape.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

vasilevskaya::CompositeShape::CompositeShape():
  countShape_(0),
  capacity_(PRIMORDIAL_CAPACITY),
  arrayShape_(allocatorForArray_.allocate(PRIMORDIAL_CAPACITY))
{}

vasilevskaya::CompositeShape::CompositeShape(size_t capacity):
  countShape_(0),
  capacity_(capacity),
  arrayShape_(allocatorForArray_.allocate(capacity))
{}

vasilevskaya::CompositeShape::CompositeShape(const vasilevskaya::CompositeShape& copiedShape):
  countShape_(copiedShape.countShape_),
  capacity_(copiedShape.capacity_),
  arrayShape_(allocatorForArray_.allocate(copiedShape.capacity_))
{
  for (size_t i = 0; i < copiedShape.countShape_; ++i)
  {
    allocatorForArray_.construct(&arrayShape_[i], copiedShape.arrayShape_[i]);
  }
}

vasilevskaya::CompositeShape::CompositeShape(vasilevskaya::CompositeShape&& portableShape) noexcept:
  countShape_(portableShape.countShape_),
  capacity_(portableShape.capacity_),
  arrayShape_(std::move(portableShape.arrayShape_))
{
  portableShape.countShape_ = 0;
  portableShape.capacity_ = 0;
  portableShape.arrayShape_ = nullptr;
}

vasilevskaya::CompositeShape::~CompositeShape()
{
  for (size_t i = 0; i < countShape_; ++i)
  {
    allocatorForArray_.destroy(&arrayShape_[i]);
  }
  allocatorForArray_.deallocate(arrayShape_, capacity_);
}

vasilevskaya::CompositeShape& vasilevskaya::CompositeShape::operator=(const vasilevskaya::CompositeShape& copiedShape)
{
  if (this == &copiedShape)
  {
    return *this;
  }
  PointToShape* newArrayShape = allocatorForArray_.allocate(copiedShape.capacity_);
  for (size_t i = 0; i < copiedShape.countShape_; i++)
  {
    allocatorForArray_.construct(&newArrayShape[i], copiedShape.arrayShape_[i]);
  }
  for (size_t i = 0; i < countShape_; i++)
  {
    allocatorForArray_.destroy(&arrayShape_[i]);
  }
  allocatorForArray_.deallocate(arrayShape_, capacity_);
  countShape_ = copiedShape.countShape_;
  capacity_ = copiedShape.capacity_;
  arrayShape_ = newArrayShape;
  return *this;
}

vasilevskaya::CompositeShape& vasilevskaya::CompositeShape::operator=(vasilevskaya::CompositeShape&& portableShape) noexcept
{
  if (this == &portableShape)
  {
    return *this;
  }
  for (size_t i = 0; i < countShape_; i++)
  {
    allocatorForArray_.destroy(&arrayShape_[i]);
  }
  allocatorForArray_.deallocate(arrayShape_, capacity_);
  countShape_ = portableShape.countShape_;
  capacity_ = portableShape.capacity_;
  arrayShape_ = std::move(portableShape.arrayShape_);
  portableShape.arrayShape_ = nullptr;
  portableShape.capacity_ = 0;
  portableShape.countShape_ = 0;
  return *this;
}

vasilevskaya::CompositeShape::PointToShape vasilevskaya::CompositeShape::operator[](size_t index) const
{
  if (index >= countShape_)
  {
    throw std::out_of_range("An array element with this index does not exist !");
  }
  return arrayShape_[index];
}

double vasilevskaya::CompositeShape::getArea() const
{
  double areaAllShapes = 0;
  for (size_t i = 0; i < countShape_; ++i)
  {
    areaAllShapes += arrayShape_[i]->getArea();
  }
  return areaAllShapes;
}

vasilevskaya::point_t vasilevskaya::CompositeShape::getPosition() const
{
  return getFrameRect().pos;
}

vasilevskaya::rectangle_t vasilevskaya::CompositeShape::getFrameRect() const
{
  rectangle_t firstFrameRect{-1, -1, {0, 0}};
  size_t firstNotEmptyShape = 0;
  for (; firstNotEmptyShape < countShape_; ++firstNotEmptyShape)
  {
    if ((arrayShape_[firstNotEmptyShape]->getFrameRect().height > 0) || (arrayShape_[firstNotEmptyShape]->getFrameRect().width > 0))
    {
      firstFrameRect = arrayShape_[firstNotEmptyShape]->getFrameRect();
      break;
    }
  }
  if (firstNotEmptyShape == countShape_)
  {
    return firstFrameRect;
  }
  double maxRightCoordinateX = firstFrameRect.width / 2 + firstFrameRect.pos.x;
  double minLeftCoordinateX = firstFrameRect.pos.x - firstFrameRect.width / 2;
  double maxTopCoordinateY = firstFrameRect.height / 2 + firstFrameRect.pos.y;
  double minLowerCoordinateY = firstFrameRect.pos.y - firstFrameRect.height / 2;
  for (; firstNotEmptyShape < countShape_; ++firstNotEmptyShape)
  {
    rectangle_t currentFrameRect = arrayShape_[firstNotEmptyShape]->getFrameRect();
    if ((currentFrameRect.height <= 0) && (currentFrameRect.width <= 0))
    {
      continue;
    }

    double rightCoordinateX = currentFrameRect.width / 2 + currentFrameRect.pos.x;
    maxRightCoordinateX = std::max(maxRightCoordinateX, rightCoordinateX);

    double leftCoordinateX = currentFrameRect.pos.x - currentFrameRect.width / 2;
    minLeftCoordinateX = std::min(leftCoordinateX, minLeftCoordinateX);

    double topCoordinateY = currentFrameRect.height / 2 + currentFrameRect.pos.y;
    maxTopCoordinateY = std::max(maxTopCoordinateY, topCoordinateY);

    double lowerCoordinateY = currentFrameRect.pos.y - currentFrameRect.height / 2;
    minLowerCoordinateY = std::min(lowerCoordinateY, minLowerCoordinateY);
  }
  double widthFrameRect = maxRightCoordinateX - minLeftCoordinateX;
  double heightFrameRect = maxTopCoordinateY - minLowerCoordinateY;
  point_t centerFrameRect {(maxRightCoordinateX + minLeftCoordinateX) / 2, (maxTopCoordinateY + minLowerCoordinateY) / 2};
  return {heightFrameRect, widthFrameRect, centerFrameRect};
}

void vasilevskaya::CompositeShape::move(double onTheAbscissa, double onTheOrdinate)
{
  for (size_t i = 0; i < countShape_; ++i)
  {
    arrayShape_[i]->move(onTheAbscissa, onTheOrdinate);
  }
}

void vasilevskaya::CompositeShape::move(const vasilevskaya::point_t& newPoint)
{
  double differentX = newPoint.x - getFrameRect().pos.x;
  double differentY = newPoint.y - getFrameRect().pos.y;
  move(differentX, differentY);
}

void vasilevskaya::CompositeShape::printFigure() const
{
  for (size_t i = 0; i < countShape_; ++i)
  {
    arrayShape_[i]->printFigure();
  }
  std::cout << "\nBounding rectangle\n" << "Height : " << getFrameRect().height
      << "\nWidth : " << getFrameRect().width << "\nCenter : X = " << getFrameRect().pos.x
      << " Y = " << getFrameRect().pos.y;
}

void vasilevskaya::CompositeShape::scale(double quotient)
{
  if (quotient < 0)
  {
    throw std::invalid_argument("The coefficient must be greater than zero !");
  }
  vasilevskaya::point_t centerFrameRect = getPosition();
  for (size_t i = 0; i < countShape_; ++i)
  {
    double differentX = arrayShape_[i]->getFrameRect().pos.x - centerFrameRect.x;
    double differentY = arrayShape_[i]->getFrameRect().pos.y - centerFrameRect.y;
    arrayShape_[i]->move(differentX * (quotient - 1), differentY * (quotient - 1));
    arrayShape_[i]->scale(quotient);
  }
}

void vasilevskaya::CompositeShape::rotate(double angle)
{
  point_t centerFrameRect = getPosition();
  double angleRotation = angle * M_PI / 180;
  for (size_t i = 0; i < countShape_; i++)
  {
    double deltaX = arrayShape_[i]->getPosition().x - centerFrameRect.x;
    double deltaY = arrayShape_[i]->getPosition().y - centerFrameRect.y;
    double newCoordinateX = centerFrameRect.x + deltaX * cos(angleRotation) - deltaY * sin(angleRotation);
    double newCoordinateY = centerFrameRect.y + deltaX * sin(angleRotation) + deltaY * cos(angleRotation);
    double accuracy = pow(10, 6);
    newCoordinateX = round(newCoordinateX * accuracy) / accuracy;
    newCoordinateY = round(newCoordinateY * accuracy) / accuracy;
    arrayShape_[i]->move(newCoordinateX - arrayShape_[i]->getPosition().x, newCoordinateY - arrayShape_[i]->getPosition().y);
  }
}

void vasilevskaya::CompositeShape::pushBack(const PointToShape& newShape)
{
  if (!newShape)
  {
    throw std::invalid_argument("You can't add an empty shape");
  }
  if (capacity_ == countShape_)
  {
    allocateMemory();
  }
  allocatorForArray_.construct(&arrayShape_[countShape_], newShape);
  countShape_++;
}

void vasilevskaya::CompositeShape::allocateMemory()
{
  if (capacity_ == 0)
  {
    PointToShape* newArray = allocatorForArray_.allocate(PRIMORDIAL_CAPACITY);
    allocatorForArray_.deallocate(arrayShape_, capacity_);
    capacity_ = PRIMORDIAL_CAPACITY;
    arrayShape_ = newArray;
    return;
  }
  PointToShape* newArray = allocatorForArray_.allocate(capacity_ * EXPANSION_FACTOR);
  for (size_t j = 0; j < countShape_; ++j)
  {
    allocatorForArray_.construct(&newArray[j], arrayShape_[j]);
    allocatorForArray_.destroy(&arrayShape_[j]);
  }
  allocatorForArray_.deallocate(arrayShape_, capacity_);
  arrayShape_ = newArray;
  capacity_ *= EXPANSION_FACTOR;
}


void vasilevskaya::CompositeShape::printFrameRect() const
{
  if (capacity_ == 0)
  {
    return;
  }
  std::cout << "Composite shape\n";
  for (size_t i = 0; i < capacity_; i++)
  {
    std::cout << i + 1 << " figure(FrameRectangle):\n";
    arrayShape_[i]->printFrameRect();
  }
}


void vasilevskaya::CompositeShape::remove(size_t index)
{
  if (index >= countShape_)
  {
    throw std::invalid_argument("There is no such element. Deletion is not possible");
  }
  for (size_t i = index; i < countShape_ - 1; ++i)
  {
    arrayShape_[index] = arrayShape_[index + 1];
  }
  allocatorForArray_.destroy(&arrayShape_[countShape_ - 1]);
  countShape_--;
}

size_t vasilevskaya::CompositeShape::getCount() const
{
  return countShape_;
}

size_t vasilevskaya::CompositeShape::getCapacity() const
{
  return capacity_;
}

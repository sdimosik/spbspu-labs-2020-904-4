#include "composite-shape.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "base-types.hpp"

unzhakov::CompositeShape::CompositeShape():
  array_(nullptr),
  size_(0)
{}

unzhakov::CompositeShape::CompositeShape(const unzhakov::CompositeShape &otherCompositeShape):
  array_(std::make_unique<SharedPtr[]>(otherCompositeShape.size_)),
  size_(otherCompositeShape.size_)
{
  for (size_t i = 0; i < otherCompositeShape.size_; i++)
  {
    array_[i] = otherCompositeShape.array_[i];
  }
}

unzhakov::CompositeShape::CompositeShape(CompositeShape &&other) noexcept:
  array_(std::move(other.array_)),
  size_(other.size_)
{
  other.size_ = 0;
}

unzhakov::CompositeShape &
unzhakov::CompositeShape::operator=(const unzhakov::CompositeShape &otherCompositeShape)
{
  if (this != &otherCompositeShape)
  {
    if (otherCompositeShape.size_)
    {
      std::unique_ptr<SharedPtr[]> tmp(new SharedPtr[otherCompositeShape.size_]);
      for (size_t i = 0; i < otherCompositeShape.size_; i++)
      {
        tmp[i] = otherCompositeShape.array_[i];
      }
      array_ = std::move(tmp);
    }
    else
    {
      array_ = nullptr;
    }
    size_ = otherCompositeShape.size_;
  }
  return *this;

}

unzhakov::CompositeShape &unzhakov::CompositeShape::operator=(CompositeShape &&shape) noexcept
{
  if (this != &shape)
  {
    array_ = std::move(shape.array_);
    size_ = shape.size_;
    shape.size_ = 0;
  }
  return *this;
}

unzhakov::CompositeShape::SharedPtr unzhakov::CompositeShape::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Invalid index, more than size\n");
  }
  return array_[index];
}

void unzhakov::CompositeShape::add(const SharedPtr &figure)
{
  if (!figure)
  {
    throw std::invalid_argument("ERROR: No any figure\n");
  }
  if (figure.get() == this)
  {
    throw std::invalid_argument("ERROR: Can't add this composite shape\n");
  }
  std::unique_ptr<SharedPtr[]> tempArray = std::make_unique<SharedPtr[]>(size_ + 1);
  for (size_t i = 0; i < size_; i++)
  {
    tempArray[i] = array_[i];
  }
  tempArray[size_] = figure;
  size_++;
  array_.swap(tempArray);
}

void unzhakov::CompositeShape::remove(size_t index)
{
  if (size_ == 0)
  {
    throw std::logic_error("The Composite Shape is empty");
  }

  if (index >= size_)
  {
    throw std::out_of_range("Invalid this argument = " + std::to_string(index) + "\n");
  }

  for (size_t i = index; i < size_ - 1; i++)
  {
    std::swap(array_[i], array_[i + 1]);
  }
  array_[--size_].reset();
}

double unzhakov::CompositeShape::getArea() const
{
  if (size_ == 0)
  {
    return 0.0;
  }
  double sumArea = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    sumArea += array_[i]->getArea();
  }
  return sumArea;
}

unzhakov::rectangle_t unzhakov::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return unzhakov::rectangle_t{-1, -1, {0, 0}};
  }

  double maxX = 0, maxY = 0, minX = 0, minY = 0;
  bool wasFirstFigureFound = false;
  size_t i = 0;
  for (i = 0; i < size_; i++)
  {
    rectangle_t figureFrame = array_[i]->getFrameRect();
    if (figureFrame.width >= 0 && figureFrame.height >= 0)
    {
      maxX = figureFrame.pos.x + figureFrame.width / 2.0;
      maxY = figureFrame.pos.y + figureFrame.height / 2.0;
      minX = figureFrame.pos.x - figureFrame.width / 2.0;
      minY = figureFrame.pos.y - figureFrame.height / 2.0;
      wasFirstFigureFound = true;
      break;
    }
  }

  if (!wasFirstFigureFound)
  {
    return unzhakov::rectangle_t{-1, -1, {0, 0}};
  }

  for (size_t j = i + 1; j < size_; j++)
  {
    rectangle_t frame = array_[j]->getFrameRect();
    if (frame.width != -1 && frame.height != -1)
    {
      maxX = std::max(maxX, frame.pos.x + frame.width / 2.0);
      maxY = std::max(maxY, frame.pos.y + frame.height / 2.0);
      minX = std::min(minX, frame.pos.x - frame.width / 2.0);
      minY = std::min(minY, frame.pos.y - frame.height / 2.0);
    }
  }

  return {maxX - minX, maxY - minY, {(maxX + minX) / 2.0, (maxY + minY) / 2.0}};

}

size_t unzhakov::CompositeShape::getSize() const
{
  return size_;
}

unzhakov::point_t unzhakov::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

void unzhakov::CompositeShape::move(const unzhakov::point_t &pos)
{
  if (size_ == 0)
  {
    return;
  }
  const point_t tempPoint = getFrameRect().pos;
  move(pos.x - tempPoint.x, pos.y - tempPoint.y);

}

void unzhakov::CompositeShape::printData() const
{
  if (size_ == 0)
  {
    return;
  }
  std::cout << "Composite shape\n";
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << i + 1 << " figure(data):\n";
    array_[i]->printData();
  }
}

void unzhakov::CompositeShape::printArea() const
{
  if (size_ == 0)
  {
    return;
  }
  std::cout << "Composite shape\n";
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << i + 1 << " figure(area):\n";
    array_[i]->printArea();
  }
}

void unzhakov::CompositeShape::printFrameRectangle() const
{
  if (size_ == 0)
  {
    return;
  }
  std::cout << "Composite shape\n";
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << i + 1 << " figure(FrameRectangle):\n";
    array_[i]->printFrameRectangle();
  }
}

void unzhakov::CompositeShape::move(double x, double y)
{
  if (size_ == 0)
  {
    return;
  }
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(x, y);
  }
}

void unzhakov::CompositeShape::scale(double coefficient)
{
  if (size_ == 0)
  {
    return;
  }
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient\n");
  }
  const point_t centreFrameRect = getCenter();
  for (size_t i = 0; i < size_; i++)
  {
    const double posX = (array_[i]->getCenter().x - centreFrameRect.x) * coefficient + centreFrameRect.x;
    const double posY = (array_[i]->getCenter().y - centreFrameRect.y) * coefficient + centreFrameRect.y;
    array_[i]->move({posX, posY});
    array_[i]->scale(coefficient);
  }
}

void unzhakov::CompositeShape::rotate(double angle)
{
  const double a = angle / 180 * M_PI;
  const double sinAngle = sin(a);
  const double cosAngle = cos(a);
  const point_t frameRectCentre = getCenter();
  for (size_t i = 0; i < size_; i++)
  {
    const point_t shapeCentre = array_[i]->getCenter();
    double posX = (shapeCentre.x - frameRectCentre.x) * cosAngle - (shapeCentre.y - frameRectCentre.y) * sinAngle +
                  frameRectCentre.x;
    double posY = (shapeCentre.x - frameRectCentre.x) * sinAngle + (shapeCentre.y - frameRectCentre.y) * cosAngle +
                  frameRectCentre.y;
    array_[i]->move({posX, posY});
    array_[i]->rotate(angle);
  }
}


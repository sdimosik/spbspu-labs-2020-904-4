#include "composite-shape.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <limits>
#include <cmath>

namespace maksimova
{
    CompositeShape::CompositeShape() :
            size_(0),
            count_(1),
            shapes_(std::make_unique<shapePtr[]>(1))
    {}

    CompositeShape::CompositeShape(const size_t count) :
            size_(0),
            count_(count),
            shapes_(std::make_unique<shapePtr[]>(count))
    {}

    CompositeShape::CompositeShape(const CompositeShape &other) :
            size_(other.size_),
            count_(other.count_),
            shapes_(std::make_unique<shapePtr[]>(other.count_))
    {
        for (size_t i = 0; i < size_; ++i)
        {
            shapes_[i] = other.shapes_[i];
        }
    }

    CompositeShape::CompositeShape(CompositeShape &&other) :
            size_(other.size_),
            count_(other.count_),
            shapes_(std::move(other.shapes_))
    {
        other.size_ = 0;
        other.count_ = 0;
        other.shapes_.reset();
    }

    CompositeShape &CompositeShape::operator=(const CompositeShape &other)
    {
        if (this == &other)
        {
            return *this;
        }
        else
        {
            shapeArray temp = std::make_unique<shapePtr[]>(other.count_);
            for (size_t i = 0; i < other.size_; ++i)
            {
                temp[i] = other.shapes_[i];
            }
            size_ = other.size_;
            count_ = other.count_;
            shapes_ = std::move(temp);
            return *this;
        }
    }

    CompositeShape &CompositeShape::operator=(CompositeShape &&other)
    {
        if (this == &other)
        {
            return *this;
        }
        size_ = other.size_;
        count_ = other.count_;
        shapes_ = std::move(other.shapes_);
        other.size_ = 0;
        other.count_ = 0;
        other.shapes_.reset();
        return *this;
    }

    CompositeShape::shapePtr &CompositeShape::operator[](const size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Invalid index entered. Index: " + std::to_string(index));
        }
        return shapes_[index];
    }

    double CompositeShape::getArea() const
    {
        double sumArea = 0;
        for (size_t i = 0; i < size_; ++i)
        {
            sumArea += shapes_[i]->getArea();
        }
        return sumArea;
    }

    rectangle_t CompositeShape::getFrameRect() const
    {
        if (size_ == 0)
        {
            return {0, 0, {0, 0}};
        }
        double left = std::numeric_limits<double>::max();
        double right = std::numeric_limits<double>::lowest();
        double low = std::numeric_limits<double>::max();
        double top =  std::numeric_limits<double>::lowest();
        for (size_t i = 0; i < size_; i++)
        {
            const rectangle_t rec = shapes_[i]->getFrameRect();
            left = std::min(left, rec.pos.x - rec.width / 2);
            right = std::max(right, rec.pos.x + rec.width / 2);
            low = std::min(low, rec.pos.y - rec.height / 2);
            top = std::max(top, rec.pos.y + rec.height / 2);
        }
        return {right - left, top - low,{(right + left) / 2, (top + low) / 2}};
    }

    void CompositeShape::move(const point_t &pos)
    {
        double dx = pos.x - this->getFrameRect().pos.x;
        double dy = pos.y - this->getFrameRect().pos.y;
        for (size_t i = 0; i < size_; ++i)
        {
            shapes_[i]->move(dx, dy);
        }
    }

    void CompositeShape::move(const double dx, const double dy)
    {
        for (size_t i = 0; i < size_; ++i)
        {
            shapes_[i]->move(dx, dy);
        }
    }

    void CompositeShape::scale(const double coefficient)
    {
        if (coefficient <= 0)
        {
            throw std::invalid_argument("Invalid coefficient. Coefficient: "
                                        + std::to_string(coefficient));
        }
        point_t pos = getFrameRect().pos;
        for (size_t i = 0; i < size_; i++)
        {
            shapes_[i]->scale(coefficient);
            double move_x = shapes_[i]->getFrameRect().pos.x - pos.x;
            double move_y = shapes_[i]->getFrameRect().pos.y - pos.y;
            shapes_[i]->move(pos);
            shapes_[i]->move(move_x * coefficient, move_y * coefficient);
        }
    }

    void CompositeShape::addShape(const CompositeShape::shapePtr &shape)
    {
        if (shape == nullptr)
        {
            throw std::invalid_argument("Added value is null");
        }
        if (size_ == count_)
        {
            shapeArray temp(std::make_unique<shapePtr[]>(count_ * 2 + 1));
            for (size_t i = 0; i < size_; i++)
            {
                temp[i] = shapes_[i];
            }
            count_ = count_ * 2 + 1;
            shapes_ = std::move(temp);
        }
        shapes_[size_] = shape;
        size_++;
    }

    void CompositeShape::deleteShape(const size_t index)
    {
        if (size_ == 0 || index >= size_)
        {
            throw std::out_of_range("Invalid index entered. Index: " + std::to_string(index));
        }
        for (size_t i = index; i < size_ - 1; ++i)
        {
            shapes_[i] = shapes_[i + 1];
        }
        shapes_[size_ - 1] = nullptr;
        size_--;
    }

    void CompositeShape::print() const
    {
        std::cout << "Amount of elements:  " << size_ << "." << std::endl;
        std::cout << "Whole area:  " << getArea() << std::endl;
        std::cout << "Composite shape center = (" << getFrameRect().pos.x << ", "
                  << getFrameRect().pos.y << ")" << std::endl;
    }

    void CompositeShape::rotate(const double angle)
    {
        double angleRad = angle * M_PI / (CIRCLE_ANGLE / 2);
        point_t pos = getFrameRect().pos;
        for (size_t i = 0; i < size_; i++)
        {
            double distanceX = shapes_[i]->getFrameRect().pos.x - pos.x;
            double distanceY = shapes_[i]->getFrameRect().pos.y - pos.y;
            const double dX = (distanceX * fabs(cos(angleRad))) - (distanceY * fabs(sin(angleRad)));
            const double dY = (distanceX * fabs(sin(angleRad))) + (distanceY * fabs(cos(angleRad)));
            shapes_[i]->move({pos.x + dX,pos.y + dY});
            shapes_[i]->rotate(angle);
        }
    }

    Matrix CompositeShape::partition() const
    {
        Matrix matrix;
        for(size_t i = 0; i < size_; ++i)
        {
            matrix.addElement(shapes_[i]);
        }
        return matrix;
    }
}

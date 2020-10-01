#include <stdexcept>
#include <math.h>
#include "composite-shape.hpp"

  namespace meshcheryakova
  {
   CompositeShape::CompositeShape() noexcept :
      spaciousness_(0),
      size_(0),
      shapes_ (nullptr)
   {}

   CompositeShape::CompositeShape(const CompositeShape &other):
      spaciousness_(other.spaciousness_),
      size_(other.size_),
      shapes_(new std::shared_ptr<Shape>[other.spaciousness_])
   {
      for(size_t i = 0; i < other.size_; i++)
      {
        shapes_[i] = other.shapes_[i];
      }
   }

   CompositeShape::CompositeShape(CompositeShape &&other) noexcept :
      spaciousness_(other.spaciousness_),
      size_(other.size_),
      shapes_(std::move(other.shapes_))
   {
     other.spaciousness_ = 0;
     other.size_ = 0;
     other.shapes_.reset();
   }

   CompositeShape &CompositeShape::operator=(const CompositeShape &other)
   {
     if(this == &other)
     {
       return *this;
     }
     else
     {
       arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(other.spaciousness_);
       for(size_t i = 0; i < other.size_; i++)
       {
         temp[i] = other.shapes_[i];
       }
       spaciousness_ = other.spaciousness_;
       size_ = other.size_;
       shapes_ = std::move(temp);
       return *this;
     }
   }

   CompositeShape &CompositeShape::operator=(CompositeShape &&other) noexcept
   {
     spaciousness_ = other.spaciousness_;
     size_ = other.size_;
     shapes_ = std::move(other.shapes_);
     other.spaciousness_ = 0;
     other.size_ = 0;
     other.shapes_.reset();
     return *this;
   }

   CompositeShape::CompositeShape(const size_t spaciousness) :
      spaciousness_(spaciousness),
      size_(0),
      shapes_(new std::shared_ptr<Shape>[spaciousness])
   {}

   std::shared_ptr<Shape> &CompositeShape::operator[](const size_t index) const
   {
     if(index >= size_ || size_ == 0)
     {
       throw std::out_of_range(std::string("That index is out of range = ") += std::to_string(index));
     }
     return shapes_[index];
   }

   double CompositeShape::getArea() const noexcept
   {
      double full_area = 0;
      for(size_t i = 0; i < size_; i++)
      {
        full_area += shapes_[i]->getArea();
      }
      return full_area;
   }

    rectangle_t CompositeShape::getFrameRect() const noexcept
    {
      if (size_ == 0)
      {
        return {0, 0, {0, 0}};
      }
      else
      {
        double max_top = 0;
        double max_bot = 0;
        double max_left = 0;
        double max_right = 0;
        rectangle_t current;
        for(size_t i = 0; i < size_; i++)
        {
          current = shapes_[i]->getFrameRect();
          max_top = std::max(current.pos.y + (current.height / 2), max_top);
          max_bot = std::min(current.pos.y - (current.height / 2), max_bot);
          max_left = std::min(current.pos.x - (current.width / 2), max_left);
          max_right = std::max(current.pos.x + (current.width / 2), max_right);
        }
        return {(max_right - max_left), (max_top - max_bot),{(max_right - max_left) / 2 + max_left, (max_top - max_bot) / 2 + max_bot }};
      }
    }

    void CompositeShape::move(const point_t &spot) noexcept
    {
      this->move(spot.x - getFrameRect().pos.x, spot.y - getFrameRect().pos.y);
    }

    void CompositeShape::move(double x, double y) noexcept
    {
      for(size_t i = 0; i < size_; i++)
      {
        shapes_[i]->move(x, y);
      }
    }

    void CompositeShape::printSpot(std::ostream &out)
    {
      out << "Spots of shapes \n";
      for(size_t i = 0; i < size_; i ++)
      {
        out << "shape number " << i << ", his spot: " ;
        shapes_[i]->printSpot(out);
      }
    }

    void CompositeShape::scale(double coefficient)
    {
      if (coefficient <= 0)
      {
        throw std::invalid_argument(std::string("Invalid coefficient in composite shape = ")
            += std::to_string(coefficient));
      }
      const point_t centre = getFrameRect().pos;
      for (size_t i = 0; i < size_; i++)
      {
        const double y_difference = shapes_[i]->getFrameRect().pos.y - centre.y;
        const double x_difference = shapes_[i]->getFrameRect().pos.x - centre.x;
        shapes_[i]->move({centre.x + coefficient * x_difference, centre.y + coefficient * y_difference});
        shapes_[i]->scale(coefficient);
      }
    }

    void CompositeShape::printParametersWithoutSpot(std::ostream &out)
    {
      out << "Info: size = " << size_ << " full area of shapes = " << getArea() << '\n'
          << " FrameRect of shapes with height = " << getFrameRect().height
          << " and width = " << getFrameRect().width << '\n';
    }

    void CompositeShape::addElement(const std::shared_ptr<Shape> &shape)
    {
      if (shape == nullptr)
      {
        throw std::invalid_argument("Shape is NULL");
      }
      if (size_ == spaciousness_)
      {
        const int coefficient = 2;
        arrayPtr temp_shape(new std::shared_ptr<Shape>[spaciousness_ * coefficient]);
        for (size_t i = 0; i < size_; i++)
        {
          temp_shape[i] = shapes_[i];
        }
        spaciousness_ *= coefficient ;
        shapes_ = std::move(temp_shape);
      }
      shapes_[size_] = shape;
      size_++;
    }

    void CompositeShape::deleteElement(const size_t index)
    {
      if(size_ == 0 || index >= size_)
      {
        throw std::out_of_range("Index is out of range. Index = " + std::to_string(index));
      }
      size_--;
      for (size_t i = index; i < size_ - 1; i++)
      {
        shapes_[i] = shapes_[i + 1];
      }
      shapes_[size_] = nullptr;
    }

    size_t CompositeShape::getSize() const noexcept
    {
      return size_;
    }

    void CompositeShape::rotate(double angle) noexcept
    {
      double radians = M_PI * angle / 180;
      double sin = std::sin(radians);
      double cos = std::cos(radians);
      const point_t centre = getFrameRect().pos;

      for (size_t i = 0; i < size_; i++)
      {
        point_t rotate_spot = shapes_[i]->getFrameRect().pos;
        double x_before_rotate = rotate_spot.x - centre.x;
        double y_before_rotate = rotate_spot.y - centre.y;
        double rotation_x = x_before_rotate * cos - y_before_rotate * sin;
        double rotation_y = x_before_rotate * sin + y_before_rotate * cos;
        shapes_[i]->move(rotation_x + centre.x, rotation_y + centre.y);
        shapes_[i]->rotate(angle);
      }
    }

    CompositeShape::arrayPtr& CompositeShape::getShapes()
    {
      return shapes_;
    }

  }


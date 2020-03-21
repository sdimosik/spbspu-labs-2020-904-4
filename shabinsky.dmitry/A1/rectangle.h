//
// Created by sdimosik on 21.03.2020.
//
#ifndef HW01_RECTANGLE_H
#define HW01_RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(const point_t &position, double width, double height);

    ~Rectangle() override = default;

    double getWidth() const;

    double getHeight() const;

    point_t getPosition() const;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &position) override;

    void move(double x, double y) override;

private:
    double width_, height_;
    point_t position_{};
};

#endif //HW01_RECTANGLE_H

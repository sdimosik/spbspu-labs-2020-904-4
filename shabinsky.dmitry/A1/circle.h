//
// Created by sdimosik on 21.03.2020.
//
#ifndef HW01_CIRCLE_H
#define HW01_CIRCLE_H
#include "shape.h"

class Circle : public Shape
{
public:
    Circle(double radius, const point_t &position);

    ~Circle() override = default;

    double getRadius() const;

    point_t getPosition() const;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &position) override;

    void move(double x, double y) override;

private:
    double radius_;
    point_t position_{};
};

#endif //HW01_CIRCLE_H

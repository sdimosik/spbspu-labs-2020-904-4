#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

class Triangle : public Shape
{
public:
    Triangle(const point_t &pos1, const point_t &pos2, const point_t &pos3);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &point) override;

    void move(double x, double y) override;

	double getCenterX();

	double getCenterY();

private:
    point_t point1_, point2_, point3_;
	point_t pos_;
	double side1, side2, side3;
};
#endif
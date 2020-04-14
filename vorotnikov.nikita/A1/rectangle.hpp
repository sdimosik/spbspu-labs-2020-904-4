#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
	Rectangle(double width, double height, const point_t &pos);

	double getArea() const override;

	rectangle_t getFrameRect() const override;

	void move(const point_t &point) override;

	void move(double x, double y) override;

private:
	double width_, height_;
	point_t pos_;
};
#endif

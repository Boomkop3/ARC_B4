#include "Shape.h"

Shape::Shape()
{
	this->width=-1;
	this->height=-1;
	this->depth=-1;
}

Shape::Shape(double width, double height, double depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}

void Shape::set_shape_type(ShapeType shape_type)
{
	this->shape_type=shape_type;
}

void Shape::set_dimension(double width, double height, double depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}

void Shape::set_width(double width)
{
	this->width = width;
}

void Shape::set_height(double height)
{
	this->height = height;
}

void Shape::set_depth(double depth)
{
	this->depth = depth;
}

double Shape::get_width(void) const
{
	return this->width;
}

double Shape::get_height(void) const
{
	return this->height;
}

double Shape::get_depth(void) const
{
	return this->depth;
}

Shape::ShapeType Shape::get_shape_type() const
{
	return this->shape_type;
}



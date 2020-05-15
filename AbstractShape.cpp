#include "AbstractShape.h"

AbstractShape::AbstractShape()
{
	this->width = -1;
	this->height = -1;
	this->depth = -1;
}

AbstractShape::AbstractShape(double width, double height, double depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}

void AbstractShape::set_shape_type(ShapeType shapetype)
{
	this->shape_type = shapetype;
}

void AbstractShape::set_dimension(double width, double height, double depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}

void AbstractShape::set_width(double width)
{
	this->width = width;
}

void AbstractShape::set_height(double height)
{
	this->height = height;
}

void AbstractShape::set_depth(double depth)
{
	this->depth = depth;
}

double AbstractShape::get_width(void) const
{
	return this->width;
}

double AbstractShape::get_height(void) const
{
	return this->height;
}

double AbstractShape::get_depth(void) const
{
	return this->depth;
}

AbstractShape::ShapeType AbstractShape::get_shape_type() const
{
	return this->shape_type;
}

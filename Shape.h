#pragma once
#include <iostream>
#include <sstream>
#include "utils.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class Shape
{
public:
	typedef enum ShapeType { ABSTRACT, CUBOID, CYLINDER, PRISM, PYRAMID, SPHERE } ShapeType;

	void set_dimension(double, double, double);
	void set_width(double);
	void set_height(double);
	void set_depth(double);
	double get_width(void) const;
	double get_height(void) const;
	double get_depth(void) const;
	virtual void get_indices(std::vector<glm::vec3>&, std::vector<glm::vec3>&) const = 0;
	virtual ShapeType get_shape_type() const;
protected:
	Shape();
	Shape(double, double, double);
	void set_shape_type(ShapeType);
private:
	double width, height, depth;
	ShapeType shape_type = ABSTRACT;
};


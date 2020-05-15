#pragma once
#include <iostream>
#include <sstream>
#include "utils.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "AbstractShape.h"

class Shape : public AbstractShape
{
public:
	Shape();
	Shape(double width, double height, double depth);
	virtual void get_indices(std::vector<glm::vec3>&, std::vector<glm::vec3>&) const = 0;
};


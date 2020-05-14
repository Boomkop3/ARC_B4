#pragma once
#include "Shape.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4

class Pyramid : public Shape
{
public:
	Pyramid();
	Pyramid(double, double, double);
	void get_indices(std::vector<glm::vec3>& vertices_out, std::vector<glm::vec3>& indices_out) const override;

	const static int vertices_count = 5;
	const static int indices_count = 18;
};


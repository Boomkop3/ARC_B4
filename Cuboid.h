#pragma once
#include "Shape.h"

#define CUBOID_A 0
#define CUBOID_B 1
#define CUBOID_C 2
#define CUBOID_D 3
#define CUBOID_E 4
#define CUBOID_F 5
#define CUBOID_G 6
#define CUBOID_H 7

class Cuboid : public Shape
{
public:
	Cuboid();
	Cuboid(double, double, double);
	void get_indices(std::vector<glm::vec3>& vertices_out, std::vector<glm::vec3>& indices_out) const override;
	const static int vertices_count = 8;
	const static int indices_count = 24; // 36 when using triangles
};

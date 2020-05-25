#include "Cylinder.h"
#include <tuple>

Cylinder::Cylinder() : AdvancedShape::AdvancedShape()
{
	this->set_shape_type(AbstractShape::ADVANCED);
}

Cylinder::Cylinder(double width, double height, double depth) : AdvancedShape::AdvancedShape(width, height, depth)
{
	this->set_shape_type(AbstractShape::ADVANCED);
}

void Cylinder::get_geometry(std::vector<SpecificIndice>& indices_types_out) const
{
	int indicesIndex = 0;
	double height = get_height();
	int steps = 32;
	double stepsize = PI * 2 / steps;
	double diametre = (get_width() + get_depth()) / 2.0;
	double radius = diametre / 2;

	std::vector<std::tuple<double, double>> coords;
	coords.resize(steps + 1);

	for (int i = 0; i < (steps + 1); i++)
	{
		double angle = stepsize * i;
		double x = cos(angle) * radius;
		double z = sin(angle) * radius;
		coords[i] = std::make_tuple(x, z);
	}

	indices_types_out.resize(
		6 + (coords.size() * 4)
	);

	indices_types_out[indicesIndex++] = { glm::vec3(0.0, height, 0.0), GL_TRIANGLE_FAN };
	for (size_t i = 0; i < coords.size(); i++)
	{
		auto x = std::get<0>(coords[i]);
		auto z = std::get<1>(coords[i]);
		indices_types_out[indicesIndex++] =
		{
			glm::vec3(x, height, z),
			GL_TRIANGLE_FAN
		};
	}

	

	for (size_t i = 0; i < coords.size(); i++)
	{
		auto x = std::get<0>(coords[i]);
		auto z = std::get<1>(coords[i]);
		indices_types_out[indicesIndex++] =
		{
			glm::vec3(x, height, z),
			GL_QUAD_STRIP
		};
		indices_types_out[indicesIndex++] =
		{
			glm::vec3(x, 0, z),
			GL_QUAD_STRIP
		};
	}

	auto x = std::get<0>(coords[0]);
	auto z = std::get<1>(coords[0]);
	indices_types_out[indicesIndex++] =
	{
		glm::vec3(x, 0, z),
		GL_QUAD_STRIP
	};
	indices_types_out[indicesIndex++] =
	{
		glm::vec3(x, height, z),
		GL_QUAD_STRIP
	};

	indices_types_out[indicesIndex++] = { glm::vec3(0.0, 0.0, 0.0), GL_TRIANGLE_FAN };

	for (size_t i = 0; i < coords.size(); i++)
	{
		auto x = std::get<0>(coords[i]);
		auto z = std::get<1>(coords[i]);
		indices_types_out[indicesIndex++] =
		{
			glm::vec3(x, 0, z),
			GL_TRIANGLE_FAN
		};
	}
}

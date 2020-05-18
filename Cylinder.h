#pragma once
#include "AdvancedShape.h"
class Cylinder : public AdvancedShape
{
public:
	Cylinder();
	Cylinder(double width, double height, double depth);
	void get_geometry(
		std::vector<SpecificIndice>& indices_types_out
	) const override;
};

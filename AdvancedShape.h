#pragma once
#include "AbstractShape.h"

typedef struct {
	glm::vec3 indice;
	int type;
} SpecificIndice;

class AdvancedShape : public AbstractShape
{
public:
	AdvancedShape();
	AdvancedShape(double width, double height, double depth);
	virtual void get_geometry(
		std::vector<SpecificIndice>& indices_types_out
	) const = 0;
};

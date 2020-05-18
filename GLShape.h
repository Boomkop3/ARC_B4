#pragma once
#include "Shape.h"
#include "AdvancedShape.h"
#include "Cuboid.h"
#include "Prism.h"
#include "Pyramid.h"
#include "DrawGLUnit.h"
#include "GLObject.h"

class GLShape : public DrawGLUnit
{
public:
	GLShape();
	GLShape(std::shared_ptr<Shape>);
	GLShape(std::shared_ptr<AdvancedShape>);
	void draw() const override;
	void drawAdvanced() const;
	void init_draw(std::shared_ptr<std::vector<tigl::Vertex>> vertex_vector, std::shared_ptr<std::vector<glm::vec3>> vertices, std::shared_ptr<std::vector<glm::vec3>> indices);
	GLenum get_draw_type() const;
protected:
private:
	std::shared_ptr<Shape> shape;
	std::shared_ptr<AdvancedShape> advancedShape;
	std::shared_ptr<std::vector<tigl::Vertex>> vertex_vector = nullptr;
	std::shared_ptr<std::vector<glm::vec3>> vertices = nullptr;
	std::shared_ptr<std::vector<glm::vec3>> indices = nullptr;
};


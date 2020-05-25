#include "GLShape.h"
#include "TextureColorComboGLUnit.h"
#include "TextureGLUnit.h"

GLShape::GLShape()
{

}

GLShape::GLShape(std::shared_ptr<Shape> shape)
{
	this->shape = shape;
}

GLShape::GLShape(std::shared_ptr<AdvancedShape> advancedShape)
{
	this->advancedShape = advancedShape;
}

void GLShape::draw() const
{
	if (this->vertex_vector && this->vertices && this->indices) {
		GLenum draw_type = get_draw_type();

		if (draw_type == GL_ZERO) {
			drawAdvanced();
		}
		else {
			this->shape->get_indices(*this->vertices, *this->indices);
			this->vertex_vector->resize(this->indices->size());

			AbstractShape::ShapeType shapeType = this->shape->get_shape_type();
			this->glObject->decorationGLUnit->fill_vertices(*this->indices, *this->vertex_vector, shapeType);

			tigl::drawVertices(draw_type, *this->vertex_vector);
		}
	}
}

void GLShape::drawAdvanced() const {
	auto indices_types = *(new std::vector<SpecificIndice>);
	advancedShape->get_geometry(indices_types);
	int size = indices_types.size();
	int type = indices_types[0].type;
	this->indices->resize(size);
	for (size_t i = 0; i < size; i++) {
		(*this->indices)[i] = indices_types[i].indice;
	}
	AbstractShape::ShapeType shapeType = this->advancedShape->get_shape_type();
	this->vertex_vector->resize(this->indices->size());
	this->glObject->decorationGLUnit->fill_vertices(*this->indices, *this->vertex_vector, shapeType);

	tigl::begin(type);
	for (size_t i = 0; i < size; i++)
	{
		if (type != indices_types[i].type) {
			tigl::end();
			tigl::begin(indices_types[i].type);
		}
		tigl::addVertex(
			(*this->vertex_vector)[i]
		);
		type = indices_types[i].type;
	}
	tigl::end();
}

void GLShape::init_draw(std::shared_ptr<std::vector<tigl::Vertex>> vertex_vector, std::shared_ptr<std::vector<glm::vec3>> vertices, std::shared_ptr<std::vector<glm::vec3>> indices)
{
	this->vertex_vector = vertex_vector;
	this->vertices = vertices;
	this->indices = indices;
}

GLenum GLShape::get_draw_type() const
{
	GLenum draw_type = GL_TRIANGLES;
	AbstractShape::ShapeType shapeType;
	if (this->shape != nullptr) {
		shapeType = this->shape->get_shape_type();
	}
	else if (this->advancedShape != nullptr) {
		shapeType = this->advancedShape->get_shape_type();
	}

	switch (shapeType) {
		case Shape::ABSTRACT:
			std::cout << "Why are you attempting to draw an abstract shape? Skipping draw." << std::endl;
			break;
		case Shape::CUBOID: draw_type = GL_QUADS; break;
		case Shape::CYLINDER: break;
		case Shape::SPHERE: break;
		case Shape::PRISM: break;
		case Shape::PYRAMID: break;
		case Shape::ADVANCED: draw_type = GL_ZERO; break;
	}
	return draw_type;
}

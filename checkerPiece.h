#pragma once
#include "TextureColorComboGLUnit.h"
#include "GLShape.h"
#include "Cylinder.h"

class CheckerPiece
{
private:
	int id;
	std::shared_ptr<GLObject> glObject;
public:
	enum Color {
		BLACK, 
		WHITE
	};
	int getId() const noexcept {
		return this->id;
	}
	std::shared_ptr<GLObject> getGlObject() const noexcept {
		return this->glObject;
	}
	CheckerPiece(
		std::shared_ptr<std::vector<tigl::Vertex>> buffer, 
		std::shared_ptr<std::vector<glm::vec3>> vertices_in, 
		std::shared_ptr<std::vector<glm::vec3>> indices_in, 
		std::shared_ptr<TextureAtlas> textureAtlas, 
		Color color, 
		bool isdouble, 
		int boardSize, 
		double boxSize, 
		int x, 
		int y, 
		double heightOffset
	);
};

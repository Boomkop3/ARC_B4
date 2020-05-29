#include "checkerPiece.h"

CheckerPiece::CheckerPiece(std::shared_ptr<std::vector<tigl::Vertex>> buffer, std::shared_ptr<std::vector<glm::vec3>> vertices_in, std::shared_ptr<std::vector<glm::vec3>> indices_in, std::shared_ptr<TextureAtlas> textureAtlas, Color color, bool isdouble, int boardSize, double boxSize, int x, int y, double height_offset)
{
	double height = isdouble ? boxSize / 2.0 : boxSize / 4.0;
	std::shared_ptr<GLShape> sharedShape = std::make_shared<GLShape>(
		std::make_shared<Cylinder>(
			boxSize, 
			height, 
			boxSize
		)
	);
	sharedShape->init_draw(buffer, vertices_in, indices_in);
	std::shared_ptr<GLObject> sharedGLObject = std::make_shared<GLObject>();
	sharedGLObject->setDrawGLUnit(sharedShape);
	sharedGLObject->position = glm::vec3(
		x * boxSize, 
		height_offset + (height / 2.0), 
		y * boxSize
	);
	sharedGLObject->rotation = glm::vec3(0, 0, 0); // prevent unpredictable behaviour

	// std::shared_ptr<TextureAtlas> textureAtlas = textureAtlas;

	std::shared_ptr<TextureColorComboGLUnit> pieceDecoration = std::make_shared<TextureColorComboGLUnit>();
	pieceDecoration->set_texture_color_filter(0.2f, 0.2f, 0.2f, 1.0f); // Apply R G B A filter on top of object
	pieceDecoration->set_texture_atlas(textureAtlas);
	pieceDecoration->set_texture_atlas_coords(2, 1);
	sharedGLObject->setDecorationGLUnit(pieceDecoration);

	this->glObject = sharedGLObject;

	// this->globjects.push_back(sharedGLObject);
}

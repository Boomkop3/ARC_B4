#include "CheckerBoardGL.h"

#define BOARD_SIZE 8
#define CUBOID_SIZE 1.0
#define BOARD_HEIGHT 0.25

CheckerBoardGL::CheckerBoardGL(std::shared_ptr<std::vector<tigl::Vertex>> buffer, std::shared_ptr<std::vector<glm::vec3>> vertices_in, std::shared_ptr<std::vector<glm::vec3>> indices_in)
{
	this->buffer = buffer;
	this->vertices_in = vertices_in;
	this->indices_in = indices_in;
}

CheckerBoardGL::~CheckerBoardGL()
{

}

void CheckerBoardGL::create_board()
{
	int textureToggle = 0;
	std::shared_ptr<TextureAtlas> textureAtlas = std::make_shared<TextureAtlas>(64, 64, 2, 2);
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		++textureToggle;
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			int x = row * CUBOID_SIZE;
			int z = col * CUBOID_SIZE;
			std::shared_ptr<GLShape> sharedShape = std::make_shared<GLShape>(
				std::make_shared<Cuboid>(CUBOID_SIZE, BOARD_HEIGHT, CUBOID_SIZE)
			);
			sharedShape->init_draw(this->buffer, this->vertices_in, this->indices_in);
			std::shared_ptr<GLObject> sharedGLObject = std::make_shared<GLObject>();
			sharedGLObject->setDrawGLUnit(sharedShape);
			sharedGLObject->position = glm::vec3(x, 0 - (CUBOID_SIZE / 2), z);
			sharedGLObject->rotation = glm::vec3(0, 0, 0); // initialize rotation to prevent unpredictable behaviour

			std::shared_ptr<TextureColorComboGLUnit> sharedDecoration = std::make_shared<TextureColorComboGLUnit>();
			sharedDecoration->set_texture_color_filter(1.f, 1.f, 1.f, 1.f); // Apply R G B A filter on top of object
			sharedDecoration->set_texture_atlas(textureAtlas);
			if ((++textureToggle) % 2 == 0) {
				sharedDecoration->set_texture_atlas_coords(2, 1);
			}
			else if (textureToggle % 2 == 1) {
				sharedDecoration->set_texture_atlas_coords(1, 2);
			}
			sharedGLObject->setDecorationGLUnit(sharedDecoration);
			this->globjects.push_back(sharedGLObject);
		}
	}
}

glm::vec2 CheckerBoardGL::GetCoordinateFor(int row, int column) {
	// ToDo make
	// int x = "";

}

glm::vec2 CheckerBoardGL::GetBoardCenter() {
	double centerDistance = ((BOARD_SIZE / 2.0f) * CUBOID_SIZE) - (CUBOID_SIZE / 2.0f);
	return glm::vec2(
		centerDistance, 
		centerDistance
	);
}

void CheckerBoardGL::draw_board()
{
	for (std::shared_ptr<GLObject> glObject : globjects) {
		glObject->draw();
	}
}

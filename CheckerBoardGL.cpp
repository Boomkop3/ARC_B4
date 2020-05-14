#include "CheckerBoardGL.h"

#define BOARD_SIZE 8
#define CUBOID_SIZE 1.
#define BOARD_BLOCK_HEIGHT .5

float scalarX = 1.f;
float scalarY = 1.f;
float scalarZ = 1.f;

CheckerBoardGL::CheckerBoardGL(std::shared_ptr<std::vector<tigl::Vertex>> buffer, std::shared_ptr<std::vector<glm::vec3>> vertices_in, std::shared_ptr<std::vector<glm::vec3>> indices_in)
{
	this->buffer = buffer;
	this->vertices_in = vertices_in;
	this->indices_in = indices_in;
}

CheckerBoardGL::~CheckerBoardGL()
{
}

static double cube_integer = 4;
static int cube_start = 0;
void CheckerBoardGL::create_board()
{
	std::shared_ptr<TextureAtlas> textureAtlas = std::make_shared<TextureAtlas>(64, 64, 2, 2);

	for (double z = -BOARD_SIZE/2.; z < BOARD_SIZE/2.; z++) {
		cube_start++;
			for (double y = -BOARD_BLOCK_HEIGHT / 2.; y < BOARD_BLOCK_HEIGHT/2.; y++) {
			int cube = cube_start;
			for (double x = -BOARD_SIZE / 2.; x < BOARD_SIZE/2.; x++)
			{

				std::shared_ptr<GLObject> sharedGLObject = std::make_shared<GLObject>();
				std::shared_ptr<TextureColorComboGLUnit> sharedDecoration = std::make_shared<TextureColorComboGLUnit>();
				std::shared_ptr<Cuboid> sharedCuboid = std::make_shared<Cuboid>(CUBOID_SIZE, CUBOID_SIZE, CUBOID_SIZE);
				std::shared_ptr<GLShape> sharedShape = std::make_shared<GLShape>(sharedCuboid);


				sharedShape->init_draw(this->buffer, this->vertices_in, this->indices_in);
				sharedGLObject->setDrawGLUnit(sharedShape);

				if ((++cube) % 2 == 0)
					sharedDecoration->set_texture_atlas_coords(2, 1);
				else if (cube % 2 == 1) sharedDecoration->set_texture_atlas_coords(1, 2);

				sharedGLObject->scale = glm::vec3(scalarX, scalarY, scalarZ);
				sharedGLObject->position = glm::vec3(x * CUBOID_SIZE * scalarX, y * CUBOID_SIZE * scalarY, z * CUBOID_SIZE * scalarZ);
				sharedGLObject->rotation = glm::vec3(0, 0, 0);

				sharedDecoration->set_texture_color_filter(1.f, 1.f, 1.f, 1.f); // Apply R G B A filter on top of object
				sharedDecoration->set_texture_atlas(textureAtlas);

				sharedGLObject->setDecorationGLUnit(sharedDecoration);
				this->globjects.push_back(sharedGLObject);
			}
		}
	}
}

void CheckerBoardGL::draw_board()
{
	for (std::shared_ptr<GLObject> glObject : globjects)
		glObject->draw();
}

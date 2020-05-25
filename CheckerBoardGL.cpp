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

void CheckerBoardGL::addPieces() {
	std::shared_ptr<GLShape> sharedShape = std::make_shared<GLShape>(
		std::make_shared<Cylinder>(1, 0.25, 1)
	);
	sharedShape->init_draw(this->buffer, this->vertices_in, this->indices_in);
	std::shared_ptr<GLObject> sharedGLObject = std::make_shared<GLObject>();
	sharedGLObject->setDrawGLUnit(sharedShape);
	sharedGLObject->position = glm::vec3(0, 0, 0);
	sharedGLObject->rotation = glm::vec3(0, 0, 0); // prevent unpredictable behaviour

	std::shared_ptr<TextureAtlas> textureAtlas = std::make_shared<TextureAtlas>(64, 64, 2, 2);

	std::shared_ptr<TextureColorComboGLUnit> pieceDecoration = std::make_shared<TextureColorComboGLUnit>();
	pieceDecoration->set_texture_color_filter(0.2f, 0.2f, 0.2f, 1.0f); // Apply R G B A filter on top of object
	pieceDecoration->set_texture_atlas(textureAtlas);
	pieceDecoration->set_texture_atlas_coords(2, 1);

	sharedGLObject->setDecorationGLUnit(pieceDecoration);

	this->globjects.push_back(sharedGLObject);
}

void CheckerBoardGL::create_board()
{
	addPieces();
	int textureToggle = 0;
	std::shared_ptr<TextureAtlas> textureAtlas = std::make_shared<TextureAtlas>(64, 96, 2, 3);

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		++textureToggle;
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			std::shared_ptr<TextureColorComboGLUnit> decoration = std::make_shared<TextureColorComboGLUnit>();
			decoration->set_texture_color_filter(1.f, 1.f, 1.f, 1.f); // Apply R G B A filter on top of object
			decoration->set_texture_atlas(textureAtlas);

			int x = row * CUBOID_SIZE;
			int z = col * CUBOID_SIZE;

			auto cube = GetSharedCuboid(CUBOID_SIZE, BOARD_HEIGHT, CUBOID_SIZE);
			cube->position = glm::vec3(x, 0 - (CUBOID_SIZE / 2), z);

			if ((++textureToggle) % 2 == 0) {
				decoration->set_texture_atlas_coords(2, 1);
			}
			else {
				decoration->set_texture_atlas_coords(1, 2);
			}
			cube->setDecorationGLUnit(decoration);
			this->globjects.push_back(cube);
		}
	}

	std::shared_ptr<TextureColorComboGLUnit> edgeDecoration = std::make_shared<TextureColorComboGLUnit>();
	edgeDecoration->set_texture_color_filter(1.f, 1.f, 1.f, 1.f); // Apply R G B A filter on top of object
	edgeDecoration->set_texture_atlas(textureAtlas);
	edgeDecoration->set_texture_atlas_coords(2, 2);

	double side_width = CUBOID_SIZE / 4.0 * 3.0;
	double side_height = side_width / 3 * 2;
	double side_length = BOARD_SIZE * CUBOID_SIZE;
	double side_bar_length = BOARD_SIZE * CUBOID_SIZE + (2 * side_width);

	auto leftEdge = GetSharedCuboid(side_bar_length, side_height, side_width);
	auto rightEdge = GetSharedCuboid(side_bar_length, side_height, side_width);
	auto backEdge = GetSharedCuboid(side_bar_length, side_height, side_width);
	auto frontEdge = GetSharedCuboid(side_bar_length, side_height, side_width);
	leftEdge->position = glm::vec3(
		(side_length / 2.0) - (CUBOID_SIZE / 2),
		0 - (CUBOID_SIZE / 2),
		0 - (CUBOID_SIZE / 2) - (side_width / 2.0)
	);
	rightEdge->position = glm::vec3(
		leftEdge->position.x,
		leftEdge->position.y,
		leftEdge->position.z + (side_length)+side_width
	);
	backEdge->position = glm::vec3(
		leftEdge->position.x - ((side_length / 2) + (side_width / 2)),
		leftEdge->position.y,
		leftEdge->position.z + ((side_length + side_width) / 2)
	);
	frontEdge->position = glm::vec3(
		leftEdge->position.x + ((side_length / 2) + (side_width / 2)),
		leftEdge->position.y,
		leftEdge->position.z + ((side_length + side_width) / 2)
	);
	backEdge->rotation = glm::vec3(0, 3.1315926 / 2.0, 0);
	frontEdge->rotation = backEdge->rotation;
	leftEdge->setDecorationGLUnit(edgeDecoration);
	rightEdge->setDecorationGLUnit(edgeDecoration);
	backEdge->setDecorationGLUnit(edgeDecoration);
	frontEdge->setDecorationGLUnit(edgeDecoration);
	this->globjects.push_back(leftEdge);
	this->globjects.push_back(rightEdge);
	this->globjects.push_back(backEdge);
	this->globjects.push_back(frontEdge);
}

inline std::shared_ptr<GLObject> CheckerBoardGL::GetSharedCuboid(double width, double height, double length) {
	std::shared_ptr<GLShape> sharedShape = std::make_shared<GLShape>(
		std::make_shared<Cuboid>(width, height, length)
		);
	sharedShape->init_draw(this->buffer, this->vertices_in, this->indices_in);
	std::shared_ptr<GLObject> sharedGLObject = std::make_shared<GLObject>();
	sharedGLObject->setDrawGLUnit(sharedShape);
	sharedGLObject->rotation = glm::vec3(0, 0, 0); // prevent unpredictable behaviour
	return sharedGLObject;
}

glm::vec3 CheckerBoardGL::GetCoordinateFor(int row, int column) {
	double rowDistance = getPartialCoordinateFor(row);
	double colDistance = getPartialCoordinateFor(column);
	return glm::vec3(
		rowDistance,
		0,
		colDistance
	);
}

std::shared_ptr<GLObject> CheckerBoardGL::GetShapeByCoordinate(int column, int row) {
	int index = 0;
	for (int x = 0; x < row - 1; x++)
		index++;
	for (int z = 0; z < column - 1; z++) 
		index++;
	return this->globjects[index];
}

std::shared_ptr<GLObject> CheckerBoardGL::highlightByCoordinate(int column, int row) {
	int index = 0;
	for (int x = 0; x < row - 1; x++) {
		index++;
		for (int z = 0; z < column - 1; z++)
			index++;
	}
	std::shared_ptr<TextureColorComboGLUnit> colorCombo = std::static_pointer_cast<TextureColorComboGLUnit>(this->globjects[index]->decorationGLUnit);
		colorCombo->set_texture_atlas_coords(1, 3);
	return this->globjects[index];
	
}

inline double getPartialCoordinateFor(int rowOrCol) {
	return (rowOrCol - 1.0) * CUBOID_SIZE;
}

glm::vec3 CheckerBoardGL::GetBoardCenter() {
	double centerDistance = ((BOARD_SIZE / 2.0f) * CUBOID_SIZE) - (CUBOID_SIZE / 2.0f);
	return glm::vec3(
		centerDistance,
		0,
		centerDistance
	);
}

void CheckerBoardGL::draw_board()
{
	for (std::shared_ptr<GLObject> glObject : globjects) {
		glObject->draw();
	}
}

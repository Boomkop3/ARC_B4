#include "CheckerBoardGL.h"

#define BOARD_SIZE 8
#define CUBOID_SIZE 1.0
#define BOARD_HEIGHT 0.25
#define BOARD_FLOOR -0.5

const auto defaultCheckersTexture = std::make_shared<TextureAtlas>(64, 96, 2, 3);

CheckerBoardGL::CheckerBoardGL(std::shared_ptr<std::vector<tigl::Vertex>> buffer, std::shared_ptr<std::vector<glm::vec3>> vertices_in, std::shared_ptr<std::vector<glm::vec3>> indices_in)
{
	this->buffer = buffer;
	this->vertices_in = vertices_in;
	this->indices_in = indices_in;
}

CheckerBoardGL::~CheckerBoardGL()
{

}

void CheckerBoardGL::addPiece(CheckerPiece::Color color, int x, int y) {
	std::shared_ptr<CheckerPiece> piece = std::make_shared<CheckerPiece>(
		this->buffer,
		this->vertices_in,
		this->indices_in,
		defaultCheckersTexture,
		color,
		false,
		BOARD_SIZE,
		CUBOID_SIZE,
		x,
		y,
		BOARD_FLOOR
	);
	this->glCheckerPieces.push_back(piece->getGlObject());
	this->glCheckerPiecesLocations.push_back(std::make_shared<glm::vec2>(x, y));
}

void CheckerBoardGL::addPieces() {
	// Example: This should be replaced with code that'll use the boardstate
	for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = ((j%2)==0)?1:0; i < BOARD_SIZE; i += 2)
		{
			addPiece(CheckerPiece::BLACK, i, j);
		}
	}
	for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = j%2; i < BOARD_SIZE; i += 2)
		{
			addPiece(CheckerPiece::WHITE, i, j+5);
		}
	}
}

void CheckerBoardGL::create_board()
{
	addPieces();
	int textureToggle = 0;
	std::shared_ptr<TextureAtlas> textureAtlas = defaultCheckersTexture;

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
	this->glDecorationBoardBorder.push_back(leftEdge);
	this->glDecorationBoardBorder.push_back(rightEdge);
	this->glDecorationBoardBorder.push_back(backEdge);
	this->glDecorationBoardBorder.push_back(frontEdge);
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
	int index = index = (row - 1) * BOARD_SIZE + column;
	return this->globjects[index];
}

void CheckerBoardGL::resetBoardColors() {
	for (std::shared_ptr<GLObject> glObject : globjects) {
		std::shared_ptr<TextureColorComboGLUnit> colorCombo = std::static_pointer_cast<TextureColorComboGLUnit>(glObject->decorationGLUnit);
		colorCombo->color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	}
}

void CheckerBoardGL::selectRight() {
	if (this->selectedTile.x < BOARD_SIZE-1) {
		this->selectedTile.x++;
		resetBoardColors();
		highlightByCoordinate();
	}
}

void CheckerBoardGL::selectLeft() {
	if (this->selectedTile.x > 0) {
		this->selectedTile.x--;
		resetBoardColors();
		highlightByCoordinate();
	}
}

void CheckerBoardGL::selectUp() {
	if (this->selectedTile.y > 0) {
		this->selectedTile.y--;
		resetBoardColors();
		highlightByCoordinate();
	}
}

void CheckerBoardGL::selectDown() {
	if (this->selectedTile.y < BOARD_SIZE-1) {
		this->selectedTile.y++;
		resetBoardColors();
		highlightByCoordinate();
	}
}

void CheckerBoardGL::highlightByCoordinate() {
	std::cout << "selected Coordinates " << this->selectedTile.x << " , " << this->selectedTile.y << std::endl;

	int index = index=this->selectedTile.x*BOARD_SIZE+this->selectedTile.y;
	if (index >= 0 && index < this->globjects.size()) {
		std::shared_ptr<TextureColorComboGLUnit> colorCombo = std::static_pointer_cast<TextureColorComboGLUnit>(this->globjects[index]->decorationGLUnit);
		colorCombo->color = glm::vec4(200.f, 200.f, 200.f, 1.f);
	}
}

void CheckerBoardGL::selectPieceByHighlightedLocationAlternate() {
	for (std::shared_ptr<GLObject> checkerPiece : glCheckerPieces) {
		if (glm::vec3(checkerPiece->position.x, 0, checkerPiece->position.z) == GetCoordinateFor((this->selectedTile.x+1), (this->selectedTile.y+1)))
			checkerPiece->liftableGLUnit->lift();
		else checkerPiece->liftableGLUnit->drop();
	}
}

std::shared_ptr<GLObject> CheckerBoardGL::getLiftedPiece() {
	for (std::shared_ptr<GLObject> checkerPiece : glCheckerPieces) {
		if (checkerPiece->liftableGLUnit->isLifted)
			return checkerPiece;
	}
	return nullptr;
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
	for (std::shared_ptr<GLObject> checkerPiece : glCheckerPieces) {
		checkerPiece->draw();
		checkerPiece->liftableGLUnit->update(0.0f);
	}
	for (std::shared_ptr<GLObject> boardBorderPiece : glDecorationBoardBorder) {
		boardBorderPiece->draw();
	}
}

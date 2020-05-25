#pragma once
#include <iostream>
#include <time.h>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "cuboid.h"
#include "cylinder.h"
#include "Pyramid.h"
#include "Prism.h"
#include "GLShape.h"
#include "GLObject.h"
#include "DecorationGLUnit.h"
#include "TextureGLUnit.h"
#include "ColorGLUnit.h"
#include "TextureColorComboGLUnit.h"
#include "ColorGLUnit.h"
#include "GLUnit.h"
#include "GameCamera.h"

class CheckerBoardGL {
public:
	CheckerBoardGL(std::shared_ptr<std::vector<tigl::Vertex>> buffer, std::shared_ptr<std::vector<glm::vec3>> vertices_in, std::shared_ptr<std::vector<glm::vec3>> indices_in);
	~CheckerBoardGL();
	void addPieces();
	void create_board();
	glm::vec3 GetCoordinateFor(int row, int column); /// Gets the center of the given square > 1 based index
	std::shared_ptr<GLObject> GetShapeByCoordinate(int column, int row);
	std::shared_ptr<GLObject> highlightByCoordinate(int column, int row);
	glm::vec3 GetBoardCenter(); /// Gets the center of the surface the board
	void draw_board();
private:
	std::shared_ptr<GLObject> GetSharedCuboid(double x, double y, double z);
	std::shared_ptr<std::vector<tigl::Vertex>> buffer;
	std::shared_ptr<std::vector<glm::vec3>> vertices_in;
	std::shared_ptr<std::vector<glm::vec3>> indices_in;
	std::vector<std::shared_ptr<GLObject>> globjects;
};

inline double getPartialCoordinateFor(int rowOrCol);

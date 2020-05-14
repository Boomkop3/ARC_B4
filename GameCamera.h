#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.h"
#include <iostream>

struct GLFWwindow;

class GameCamera
{
public:
	GameCamera(GLFWwindow*);

	glm::mat4 getMatrix();
	void update(GLFWwindow*);
	void update2(GLFWwindow*);

private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec2 rotation = glm::vec2(0, 0);
	bool mousePointerEnabled = false;
	void move(float angle, float fac);
	void move2();
};



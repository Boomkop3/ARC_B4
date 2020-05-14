#include "GameCamera.h"
static double camX;
static double camZ;
static double rotX;



GameCamera::GameCamera(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

glm::mat4 GameCamera::getMatrix()
{
	glm::vec3 viewPosOrTargetPos = glm::vec3(0, 0, 0);  // Kijkt nu naar positie 0,0,0

	glm::mat4 viewMat = glm::lookAt(
		glm::vec3(camX, 0, camZ) + viewPosOrTargetPos,
		glm::vec3(0,0,0),
		glm::vec3(0.0f, 1.0f, 0.0f));
	viewMat = glm::rotate(viewMat, (float)rotX, glm::vec3(1, 0, 0));
	viewMat = glm::translate(viewMat, glm::vec3(this->translation.x, this->translation.y, this->translation.z));
	return viewMat;
}

void GameCamera::move(float angle, float fac)
{
	position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}

void GameCamera::move2()
{

}


void GameCamera::update(GLFWwindow* window)
{
	update2(window);
	return;

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	std::cout << "rot y: " << rotation.y << std::endl;


	if (!this->mousePointerEnabled) {

		rotation.x -= (float)(lastY - y) / 1000.f;
		rotation.y -= (float)(lastX - x) / 1000.f;

		lastX = x;
		lastY = y;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			move(0, .05f);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			move(180, .05f);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			move(90, .05f);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			move(-90, .05f);
	}
	static bool holdButton = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (!holdButton) {
			glfwSetInputMode(window, GLFW_CURSOR, this->mousePointerEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			this->mousePointerEnabled = !this->mousePointerEnabled;
		}
		holdButton = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		holdButton = false;
	}
}

static double rotY=0;
static double radius = 10;
void GameCamera::update2(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		rotY-=.02;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		rotY+=.02;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		rotX += .02f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		rotX -= .02f;
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		radius-=.1;
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		radius += .1;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		this->translation.y -= .02;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		this->translation.y += .02;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		this->translation.x += .02;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->translation.x -= .02;

	camX = sin(rotY) * radius;
	camZ = cos(rotY) * radius;


	// When escape is pressed the mouse pointer can be locked / unlocked.
	static bool holdButton = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (!holdButton) {
			glfwSetInputMode(window, GLFW_CURSOR, this->mousePointerEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			this->mousePointerEnabled = !this->mousePointerEnabled;
		}
		holdButton = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		holdButton = false;
	}
}

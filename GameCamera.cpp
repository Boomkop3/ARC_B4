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
		glm::vec3(0, 0, 0),
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

static double rotY = 0;
static double radius = 10;

void GameCamera::rotateToLeft() {
	rotY -= .02;
}

void GameCamera::rotateToRight() {
	rotY += .02;
}

void GameCamera::rotateToBottom() {
	rotX += .02f;
}

void GameCamera::rotateToTop() {
	rotX -= .02f;
}

void GameCamera::decreaseRadius() {
	radius -= .1;
}

void GameCamera::increaseRadius() {
	radius += .1;
}


void GameCamera::checkKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		rotateToLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		rotateToRight();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		rotateToBottom();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		rotateToTop();
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		decreaseRadius();
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		increaseRadius();
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		setPlayer1Cam();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		setPlayer2Cam();
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		setStartGamePosition();

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

void GameCamera::checkTargetRadius() {
	if (this->targetRadius != -1) {
		if (radius != targetRadius) {
			std::cout << "Absolute value" << std::abs(targetRadius - radius) << std::endl;
			if (std::abs(targetRadius - radius) > INC_DEC_VALUE_RADIUS) {
				if (radius > targetRadius)
					radius -= INC_DEC_VALUE_RADIUS;
				else
					radius += INC_DEC_VALUE_RADIUS;
			}
			else targetRadius = -1;
		}
	}
}

void GameCamera::checkTargetRotation() {
	if (this->targetRotation.x != -1) {
		if (rotX != targetRotation.x) {
			std::cout << "Absolute value" << std::abs(targetRotation.x - rotX) << std::endl;
			if (std::abs(targetRotation.x - rotX) > INC_DEC_VALUE_ROTATIONX) {
				if (rotX > targetRotation.x)
					rotX -= INC_DEC_VALUE_ROTATIONX;
				else
					rotX += INC_DEC_VALUE_ROTATIONX;
			}
			else {
				rotX = targetRotation.x;
				targetRotation.x = -1;
			}
		}
	}

	if (this->targetRotation.y != -1) {
		if (rotY != targetRotation.y) {
			if (std::abs(targetRotation.y - rotY) > INC_DEC_VALUE_ROTATIONY) {
				if (rotY > targetRotation.y)
					rotY -= INC_DEC_VALUE_ROTATIONY;
				else
					rotY += INC_DEC_VALUE_ROTATIONY;
			}
			else {
				rotY = targetRotation.y;
				targetRotation.y = -1;
			}
		}
	}
}

void GameCamera::setPlayer1Cam() {
	this->targetRadius = 10.7;
	this->targetRotation.y = 0;
	this->targetRotation.x = .17 * PI;
}

void GameCamera::setPlayer2Cam() {
	this->targetRadius = 10.7;
	this->targetRotation.y = PI;
	this->targetRotation.x = -.17 * PI;
}

void GameCamera::setStartGamePosition() {
	rotX = PI / 2.;
	rotY = 0;
	radius = 1.;
	this->targetRadius = 11.3;
}

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION // Only allowed in main file to prevent linker errors.

#include <iostream>
#include <time.h>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "cuboid.h"
#include "GLShape.h"
#include "stb_image.h"
#include "GLObject.h"
#include "DecorationGLUnit.h"
#include "TextureGLUnit.h"
#include "ColorGLUnit.h"
#include "TextureColorComboGLUnit.h"
#include "ColorGLUnit.h"
#include "GLUnit.h"
#include "GameCamera.h"
#include "CheckerBoardGL.h"
#include "GestureDetection.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define VSYNC_ON 1
#define VSYNC_OFF 0

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

//Prototypes
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void update();
void imGuiUpdate();
void initImGui();
void destroyImGui();
bool initOpenGL();
bool init();
void draw();
void create_checkerboard();

//ARC vars
const char* APP_TITLE = "Augmented Reality Checkers";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool gFullscreen = false;

//Window pointer
GLFWwindow* gWindow = NULL;

//Shared (smart) pointers
std::shared_ptr<GameCamera> gCamera;
std::shared_ptr<std::vector<tigl::Vertex>> gBuffer = std::make_shared<std::vector<tigl::Vertex>>();
std::shared_ptr<std::vector<glm::vec3>> gVertices_in = std::make_shared<std::vector<glm::vec3>>();;
std::shared_ptr<std::vector<glm::vec3>> gIndices_in = std::make_shared<std::vector<glm::vec3>>();;
std::shared_ptr<CheckerBoardGL> gCheckerBoardGL;
std::shared_ptr<GestureDetection> gGestureDetection;
static void GLClearError()
{
	// Possibility for thread.yield?
	while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError() {
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
	}
}
bool my_tool_active = false;
int main(void)
{
	std::cout << "Initialize program" << std::endl;
	if (!init()) {
		return -1;
	}
	//Create board
	create_checkerboard();
	//Setup IMGUI
	initImGui();
	//Set clear color
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//Setup gesture detection using OpenCV
	gGestureDetection = std::make_shared<GestureDetection>();
	gGestureDetection->visionApp2();
	std::cout << "Setup done, entering program loop..." << std::endl;
	while (!glfwWindowShouldClose(gWindow))
	{
		update();
		draw();
		imGuiUpdate();
		glfwSwapBuffers(gWindow);
		glfwPollEvents();
	}
	destroyImGui();
	glfwTerminate();
	return 0;
}

bool vsync = true;
void imGuiUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	glfwSwapInterval(vsync ? VSYNC_ON : VSYNC_OFF);

	ImGui::Text("Dit is imgui! \n \nVia de GUI kun je vsync nu aan- of uitzetten. \n\nMvg, \n Dustin");
	ImGui::Text("\n\nKnopjes!");
	ImGui::Checkbox("Vsync", &vsync);
	ImGui::Text("Applicatie gemiddelde %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void initImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(gWindow, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}

void destroyImGui() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

bool initOpenGL() {
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	if (gFullscreen)
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);
		if (pVmode != NULL) {
			gWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
		}
	}
	else
	{
		gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	}

	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);
	glfwSetKeyCallback(gWindow, glfw_onKey);

	glewExperimental = GL_TRUE;

	std::cout << "Glew init" << std::endl;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to init GLEW" << std::endl;
		return false;
	}

	std::cout << "Clear color, depth test, glfwSwapInterval" << std::endl;
	glClearColor(.4f, .75f, .6f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(VSYNC_ON);

	return true;
}

bool init()
{
	if (!initOpenGL()) {
		return false;
	}
	tigl::init();

	tigl::shader->enableColor(true);
	tigl::shader->enableTexture(true);

	GLuint textureId = -1;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int width, height, comp;

	unsigned char* data = stbi_load(
		"texture_map_checkers3.png", 
		&width, &height, &comp, 
		STBI_rgb_alpha
	);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stbi_image_free(data);
	gCamera = std::make_shared<GameCamera>(gWindow);


	return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		if (gCamera->player1Cam)
			gCheckerBoardGL->selectUp();
		else gCheckerBoardGL->selectDown();
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (!gCamera->player1Cam)
			gCheckerBoardGL->selectUp();
		else gCheckerBoardGL->selectDown();
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		if (gCamera->player1Cam)
			gCheckerBoardGL->selectLeft();
		else gCheckerBoardGL->selectRight();
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		if (!gCamera->player1Cam)
			gCheckerBoardGL->selectLeft();
		else gCheckerBoardGL->selectRight();
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (gCheckerBoardGL->getLiftedPiece()) {
			std::shared_ptr<GLObject> lifted = gCheckerBoardGL->getLiftedPiece();
			// if move is allowed -->
			glm::vec3 movePos = gCheckerBoardGL->GetCoordinateFor(gCheckerBoardGL->selectedTile.x+1, gCheckerBoardGL->selectedTile.y+1);
			lifted->liftableGLUnit->moveToXY(movePos.x, movePos.z);
			lifted->liftableGLUnit->drop();
		} else 
		gCheckerBoardGL->selectPieceByHighlightedLocationAlternate();
	}
}

static const double updatesPerSecond = 100.;
static double timer = 1/updatesPerSecond;
double lastFrameTime = .0;

void update()
{
	double currentFrameTime = glfwGetTime();
	double deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	timer -= deltaTime;
	if (timer <= 0) {
		timer = 1./updatesPerSecond;
		gCamera->updateKeyInput(gWindow);
		gCamera->checkTargetRadius();
		gCamera->checkTargetRotation();
	}
}

void create_checkerboard() {
	gCheckerBoardGL = std::make_shared<CheckerBoardGL>(gBuffer, gVertices_in, gIndices_in);
	gCheckerBoardGL->create_board();
	glm::vec3 centerPos = gCheckerBoardGL->GetBoardCenter();
	gCamera->translation.x = -centerPos.x;
	gCamera->translation.y = -centerPos.y;
	gCamera->translation.z = -centerPos.z;

	gCheckerBoardGL->highlightByCoordinate();

	//tigl::shader->enableLighting(true);
	//tigl::shader->setLightCount(1);
	//tigl::shader->setLightPosition(0, centerPos);
	//tigl::shader->setLightDirectional(0, true);
	//tigl::shader->setLightAmbient(0, glm::vec3(.5f, .5f, .5f));
	//tigl::shader->setLightDiffuse(0, glm::vec3(.6f, .6f, .6f));
	//tigl::shader->setLightSpecular(0, glm::vec3(1.f, .8f, .4f));
	//tigl::shader->setShinyness(.5f);

	gCamera->setStartGamePosition();
}

void draw() {
	int width, height;
	glfwGetWindowSize(gWindow, &width, &height);
	glViewport(0, 0, width, height);

	glm::mat4 projection = glm::perspective(glm::radians(45.f), width / (float)height, .1f, 100.f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(gCamera->getMatrix());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gCheckerBoardGL->draw_board();
}

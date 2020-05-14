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
#include "Pyramid.h"
#include "Prism.h"
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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define VSYNC_ON 1
#define VSYNC_OFF 0

// using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

const char* APP_TITLE = "Open GL test";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool gFullscreen = false;

GLFWwindow* gWindow = NULL;
GameCamera* gCamera = NULL;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void update();
void imGuiUpdate();
void initImGui();
void destroyImGui();
bool initOpenGL();
bool init();

void draw();
void create_checkerboard();

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

	std::cout << "Create objects" << std::endl;

	create_checkerboard();

	//Setup IMGUI
	initImGui();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



	std::cout << "Main program loop" << std::endl;
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
		"texture_map_checkers.png", 
		&width, &height, &comp, 
		STBI_rgb_alpha
	);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stbi_image_free(data);
	gCamera = new GameCamera(gWindow);


	return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// reserved for later use
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
		gCamera->update(gWindow);
	}
}

std::shared_ptr<std::vector<tigl::Vertex>> buffer = std::make_shared<std::vector<tigl::Vertex>>();
std::shared_ptr<std::vector<glm::vec3>> vertices_in = std::make_shared<std::vector<glm::vec3>>();;
std::shared_ptr<std::vector<glm::vec3>> indices_in = std::make_shared<std::vector<glm::vec3>>();;
std::shared_ptr<CheckerBoardGL> checkerBoardGL;

void create_checkerboard() {
	checkerBoardGL = std::make_shared<CheckerBoardGL>(buffer, vertices_in, indices_in);
	checkerBoardGL->create_board();
	glm::vec3 centerPos = checkerBoardGL->GetBoardCenter();
	gCamera->translation.x = -centerPos.x;
	gCamera->translation.y = -centerPos.y;
	gCamera->translation.z = -centerPos.z;
}

void draw() {
	int width, height;
	glfwGetWindowSize(gWindow, &width, &height);
	glViewport(0, 0, width, height);

	glm::mat4 projection = glm::perspective(glm::radians(45.f), width / (float)height, .1f, 100.f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(gCamera->getMatrix());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	checkerBoardGL->draw_board();
}

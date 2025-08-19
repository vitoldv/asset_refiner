#include <iostream>
#include <string>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "assimp/Importer.hpp"

#include "GLRenderer.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	800
#define WINDOW_TITLE	"AssetRefiner"

#define IS_FPS_LIMIT	true
#define TARGET_FPS		60

GLFWwindow* window;
std::unique_ptr<GLRenderer> renderer;

// Frame time control 
int previousFrameTime = 0;
int currentFrameTime = 0;
float deltaTime;

void createWindow();
void createRenderer();

int main()
{
	createWindow();
	createRenderer();

	float frameTime = 0;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);

		currentFrameTime = glfwGetTime() * 1000.0f;
		frameTime = currentFrameTime - previousFrameTime;

		float TARGET_FRAME_TIME = 1000.0f / TARGET_FPS;
		if (IS_FPS_LIMIT && frameTime < TARGET_FRAME_TIME) continue;

		deltaTime = frameTime / 1000.0f;
		previousFrameTime = currentFrameTime;

		renderer->draw();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

void createRenderer()
{
	renderer = std::make_unique<GLRenderer>();
	renderer->init(window);
}
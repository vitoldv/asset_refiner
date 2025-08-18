#include <iostream>
#include <string>

#include "GLFW/glfw3.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	800
#define WINDOW_TITLE	"AssetRefiner"

#define IS_FPS_LIMIT	true
#define TARGET_FPS		60

GLFWwindow* window;
// Frame time control 
int previousFrameTime = 0;
int currentFrameTime = 0;
float deltaTime;

int main()
{
	glfwInit();
	// Set GLFW to NOT work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

	float frameTime = 0;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		currentFrameTime = glfwGetTime() * 1000.0f;
		frameTime = currentFrameTime - previousFrameTime;

		float TARGET_FRAME_TIME = 1000.0f / TARGET_FPS;
		if (IS_FPS_LIMIT && frameTime < TARGET_FRAME_TIME) continue;

		deltaTime = frameTime / 1000.0f;
		previousFrameTime = currentFrameTime;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
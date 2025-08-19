#include <iostream>
#include <string>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "GLRenderer.h"
#include "AssetImporter.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	800
#define WINDOW_TITLE	"AssetRefiner"

#define IS_FPS_LIMIT	true
#define TARGET_FPS		60

#define ZFAR 100.0f
#define ZNEAR 0.1f
#define FOV 80.0f
#define CAMERA_ZOOM_STEP 0.1f
#define CAMERA_ROTATION_SPEED 0.5f

GLFWwindow* window;
std::unique_ptr<GLRenderer> renderer;
std::unique_ptr<Model> model;

struct Camera
{
	const glm::vec3 initialPosition = { 0, 0, -3.0f };
	const glm::vec3 target = { 0, 0, 0 };
	glm::vec3 position = initialPosition;
	glm::vec2 rotation = {0, 0};
	glm::vec3 up = { 0, 1.0f, 0 };
} camera;

struct CursorState
{
	bool isFirstClick = true;
	glm::dvec2 prevPos;
	glm::dvec2 currPos;
} cursorState;

// Frame time control 
int previousFrameTime = 0;
int currentFrameTime = 0;
float deltaTime;

void createWindow();
void createRenderer();
void setup();
void handleInput();
void update();

void onScrollCallback(GLFWwindow* window, double xoffset, double yOffset);

int main()
{
	createWindow();
	createRenderer();
	setup();

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

		handleInput();
		update();
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

	glfwSetScrollCallback(window, onScrollCallback);
}

void createRenderer()
{
	renderer = std::make_unique<GLRenderer>();
	renderer->init(window);
}

void setup()
{
	model = AssetImporter::importModel("assets\\Statue\\Statue.obj", true);
	renderer->setModel(*model);
	renderer->updateModelTransform(glm::mat4(1.0f));
	renderer->updateCameraViewProj(glm::lookAt(glm::vec3(0, 0, -5.0f), glm::vec3(0), glm::vec3(0, 1.0f, 0)),
		glm::perspective(70.0f, 1.0f, 0.1f, 100.0f));
}

void onScrollCallback(GLFWwindow* window, double xoffset, double yOffset)
{
	float currZoom = glm::length((camera.position - camera.target));
	float newZoom = currZoom - glm::sign(yOffset) * CAMERA_ZOOM_STEP;
	if (newZoom < 0.1f) newZoom = 0.1f;
	camera.position = glm::normalize(camera.position - camera.target) * newZoom;
}

void handleInput()
{
	// Orbit camera control
	{
		bool lmbPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		if (!lmbPressed)
		{
			cursorState.isFirstClick = true;
		}
		else
		{
			glfwGetCursorPos(window, &cursorState.currPos.x, &cursorState.currPos.y);
			if (cursorState.isFirstClick)
			{
				cursorState.prevPos = cursorState.currPos;				
				cursorState.isFirstClick = false;
			}
			else
			{				
				glm::dvec2 mouseDelta = cursorState.currPos - cursorState.prevPos;
				if (!glm::isnan(mouseDelta.x) && !glm::isnan(mouseDelta.y))
				{
					camera.rotation.y -= mouseDelta.x * CAMERA_ROTATION_SPEED;
					camera.rotation.x -= mouseDelta.y * CAMERA_ROTATION_SPEED;
				}
				cursorState.prevPos = cursorState.currPos;

				float val = (abs(camera.rotation.x) + 90.0f) / 180.0f;
				if ((int)val % 2 == 1)
				{
					camera.up = { 0, -1.0f, 0 };
				}
				else
				{
					camera.up = { 0, 1.0f, 0 };
				}

				glm::mat4 rx = glm::rotate(glm::mat4(1.0f), -glm::radians(camera.rotation.x), glm::vec3(1.0f, 0, 0));
				glm::mat4 ry = glm::rotate(glm::mat4(1.0f), glm::radians(camera.rotation.y), glm::vec3(0, 1.0f, 0));

				float distanceToTarget = glm::length(camera.position - camera.target);
				camera.position = ry * rx * glm::vec4(glm::normalize(camera.initialPosition), 1.0f);
				camera.position *= distanceToTarget;
			}
		}
	}
}

void update()
{
	glm::mat4 view = glm::lookAtRH(camera.position, camera.target, camera.up);
	glm::mat4 projection = glm::perspectiveRH_ZO(glm::radians(FOV), (float)WINDOW_WIDTH / WINDOW_HEIGHT, ZNEAR, ZFAR);
	renderer->updateCameraViewProj(view, projection);
}
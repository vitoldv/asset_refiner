#pragma once

//#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLModel.h"
#include "GLTexture.h"

#include "GLFW/glfw3.h"

#define BACKGROUND_COLOR 0x888800FF

class GLRenderer
{
public:

	~GLRenderer();

	int init(GLFWwindow* window);
	void draw();
	void updateCameraViewProj(glm::mat4 view, glm::mat4 projection);
	void updateModelTransform(glm::mat4 transform);
	void cleanup();

private:

	const char* MODEL_UNIFORM_NAME = "model";
	const char* NORMAL_MATRIX_UNIFORM_NAME = "normalMatrix";

	std::unique_ptr<GLShader> shader;
	std::unique_ptr<GLModel> model;
	glm::mat4 modelTransform;

	struct Camera
	{
		glm::mat4 view;
		glm::mat4 projection;
	} camera;
};
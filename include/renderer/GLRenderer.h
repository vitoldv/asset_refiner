#pragma once

//#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLModel.h"
#include "GLTexture.h"

#include "GLFW/glfw3.h"

#define BACKGROUND_COLOR 0x008B8BFF

class GLRenderer
{
public:

	int init(GLFWwindow* window);
	void draw();
	void setModel(const Model& model);
	void updateCameraViewProj(glm::mat4 view, glm::mat4 projection);
	void updateModelTransform(glm::mat4 transform);

private:

	const char* VIEW_UNIFORM_NAME = "view";
	const char* PROJECTION_UNIFORM_NAME = "projection";
	const char* MODEL_UNIFORM_NAME = "model";
	const char* NORMAL_MATRIX_UNIFORM_NAME = "normalMatrix";
	const char* LIGHT_DIRECTION_UNIFORM_NAME = "lightDirection";
	const char* VERTEX_SHADER_LOCAL_PATH = "shaders\\shader.vert";
	const char* FRAGMENT_SHADER_LOCAL_PATH = "shaders\\shader.frag";


	std::unique_ptr<GLShader> shader;
	std::unique_ptr<GLModel> model;
	glm::mat4 modelTransform;
	glm::vec3 lightDirection = { 0, -1.0f, -1.0f };

	struct Camera
	{
		glm::mat4 view;
		glm::mat4 projection;
	} camera;
};
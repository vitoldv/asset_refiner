#include "GLRenderer.h"

GLRenderer::~GLRenderer()
{
	cleanup();
}

int GLRenderer::init(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader = std::make_unique<GLShader>("shaders\\shader.vert", "shaders\\shader.frag");

	return 0;
}

void GLRenderer::draw()
{
	auto clearColor = GLUtils::getRGBANormalized(BACKGROUND_COLOR);
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (model != nullptr)
	{
		// Attach shader program
		shader->enable();
		// Setting uniforms
		shader->setUniform("view", camera.view);
		shader->setUniform("projection", camera.projection);
		// Calculate Normal matrix (required for proper normals transformation)
		glm::mat3 normalMat = glm::transpose(glm::inverse(camera.view * modelTransform));
		shader->setUniform(MODEL_UNIFORM_NAME, modelTransform);
		shader->setUniform(NORMAL_MATRIX_UNIFORM_NAME, normalMat);
		model->draw(*shader);
	}
}

void GLRenderer::updateCameraViewProj(glm::mat4 view, glm::mat4 projection)
{
	camera = { view, projection };
}

void GLRenderer::updateModelTransform(glm::mat4 transform)
{
	modelTransform = transform;
}

void GLRenderer::cleanup()
{
	// nothing ?
}

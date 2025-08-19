#include "GLRenderer.h"

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

	shader = std::make_unique<GLShader>(VERTEX_SHADER_LOCAL_PATH, FRAGMENT_SHADER_LOCAL_PATH);

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
		shader->setUniform(VIEW_UNIFORM_NAME, camera.view);
		shader->setUniform(PROJECTION_UNIFORM_NAME, camera.projection);
		// Calculate Normal matrix (required for proper normals transformation)
		glm::mat3 normalMat = glm::transpose(glm::inverse(camera.view * modelTransform));
		shader->setUniform(NORMAL_MATRIX_UNIFORM_NAME, normalMat);
		shader->setUniform(MODEL_UNIFORM_NAME, modelTransform);
		shader->setUniform(LIGHT_DIRECTION_UNIFORM_NAME, lightDirection);

		model->draw(*shader);
	}
}

void GLRenderer::setModel(const Model& model)
{
	if (this->model != nullptr)
	{
		this->model.release();
	}
	this->model = std::make_unique<GLModel>(1, model);
}

void GLRenderer::updateCameraViewProj(glm::mat4 view, glm::mat4 projection)
{
	camera = { view, projection };
}

void GLRenderer::updateModelTransform(glm::mat4 transform)
{
	modelTransform = transform;
}

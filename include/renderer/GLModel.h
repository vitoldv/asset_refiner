#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "GLMesh.h"
#include "GLShader.h"
#include "GLMaterial.h"
#include "GLUtils.h"

#include "Model.h"

class GLModel
{
public:
	const uint32_t id;

	GLModel(uint32_t id, const Model& model);
	~GLModel();

	void draw(GLShader& shader);

private:

	uint32_t meshCount;
	uint32_t materialCount;

	std::vector<GLMesh*> meshes;
	std::vector<GLMaterial*> materials;

	void createFromGenericModel(const Model& model);

	void cleanup();
};
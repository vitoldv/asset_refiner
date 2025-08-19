#pragma once

#include <stdexcept>
#include <string>

#include "glad/glad.h"

#include "Texture.h"

class GLTexture
{
public:

	const std::string name;
	uint32_t glId;

	GLTexture(const Texture& texture);
	~GLTexture();

private:

	void createFromImportedTexture(const Texture& texture);
	void cleanup();
};
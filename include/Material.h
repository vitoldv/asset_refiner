#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include <Texture.h>

class Material
{
public:

	const std::string name;

	float shininess;
	float opacity = 0;
	glm::vec3 ambientColor = {};
	glm::vec3 diffuseColor = {};
	glm::vec3 specularColor = {};

	std::shared_ptr<Texture> ambientTexture = {};
	std::shared_ptr<Texture> diffuseTexture = {};
	std::shared_ptr<Texture> specularTexture = {};
	std::shared_ptr<Texture> opacityMap = {};

	Material(const char* name) : name(name) {}
};
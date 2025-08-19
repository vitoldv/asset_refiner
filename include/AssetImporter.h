#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Model.h"
#include "Texture.h"

#define ASSIMP_PREPROCESS_FLAGS aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs
const std::vector<const char*> c_supportedFormats = { ".obj", ".fbx" };

class AssetImporter
{
public:

	static void importTexture(std::filesystem::path textureFilePath, bool printImportData, Texture& outTexture);
	static std::shared_ptr<Model> importModel(std::filesystem::path modelFilePath, bool printImportData = false);

};
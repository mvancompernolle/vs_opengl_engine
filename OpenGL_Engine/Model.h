#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Program.h"
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	/*  Functions   */
	Model(GLchar* path, bool defaultTexture = true);
	void render(Program program);
private:
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	bool defaultTexture;

	static std::vector<Texture> texturesLoaded;
};

#endif // MODEL_H
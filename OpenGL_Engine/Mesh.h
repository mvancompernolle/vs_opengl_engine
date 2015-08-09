#pragma once

#ifndef MESH_H
#define MESH_H

#include "Texture.h"
#include "Program.h"
#include "Vertex.h"

// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// GL Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Mesh {
public:
	/*  Functions  */
	// Constructor
	Mesh(std::vector<VertexTN> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	// Render the mesh
	void render(Program program);

	/*  Mesh Data  */
	std::vector<VertexTN> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;

	/*  Functions    */
	// Initializes all the buffer objects/arrays
	void setupMesh();

};

#endif // MESH_H
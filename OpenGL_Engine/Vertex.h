#ifndef OPENGL_ENGINE_VERTEX_H
#define OPENGL_ENGINE_VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 pos;
};

struct VertexC : Vertex {
	glm::vec3 color;
};

struct VertexT : Vertex {
	glm::vec2 tex;
};

struct VertexTN : Vertex {
	glm::vec3 normal;
	glm::vec2 tex;
};

struct VertexTNT : Vertex {
	glm::vec3 normal;
	glm::vec2 tex;
	glm::vec3 tangent;
};

struct VertexGrass : Vertex {
	glm::vec3 color;
	float angle;
};

#endif //OPENGL_ENGINE_VERTEX_H
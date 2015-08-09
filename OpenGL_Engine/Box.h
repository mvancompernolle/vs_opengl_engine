#ifndef OPENGL_ENGINE_BOX_H
#define OPENGL_ENGINE_BOX_H

#include "Entity.h"
#include "Program2D.h"
#include "Vertex.h"
#include "Texture.h"
#include <vector>

class Box : public Entity {
public:
	Box(float w = 1.0, float h = 1.0);
	virtual ~Box();

	virtual void tick(float dt);
	virtual void render();

private:
	std::vector<VertexT> geometry;
	std::vector<unsigned int> indices;
	Program2D program;
	GLuint ebo;
	Texture* texture;
};


#endif //OPENGL_ENGINE_BOX_H
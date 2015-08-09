#ifndef OPENGL_ENGINE_ENTITY_H
#define OPENGL_ENGINE_ENTITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include <vector>

class Entity {
public:
	Entity();
	virtual ~Entity();

	virtual void tick(float dt) = 0;
	virtual void render() = 0;

	virtual void scale(glm::vec3 scaleValue);
	virtual void rotate(float angle, const glm::vec3& axis);
	virtual void translate(const glm::vec3& amount);
	void setIdentity();

	const glm::mat4& getModel() const;

	int getWidth() const;
	int getHeight() const;
	void unbindVAO() const;
protected:
	int width, height;
	glm::mat4 model;
	GLuint vbo, vao;
};


#endif //OPENGL_ENGINE_ENTITY_H
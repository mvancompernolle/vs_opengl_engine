#define GLM_FORCE_RADIANS

#include "Entity.h"


Entity::Entity() {

	// generate vao and vbo
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

Entity::~Entity() {

}

void Entity::scale(glm::vec3 scale) {
	model = glm::scale(model, glm::vec3(scale.x , scale.y, scale.z));
}

void Entity::rotate(float angle, const glm::vec3& axis) {
	model = glm::rotate(model, glm::radians(angle), axis);
}

void Entity::translate(const glm::vec3& amount) {
	model = glm::translate(model, amount);
}


void Entity::setIdentity() {
	model = glm::mat4();
}

const glm::mat4& Entity::getModel() const {
	return model;
}


int Entity::getWidth() const {
	return width;
}

int Entity::getHeight() const {
	return height;
}

void Entity::unbindVAO() const {
	glBindVertexArray(0);
}
#define GLM_FORCE_RADIANS

#include "Engine.h"
#include "Program.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

Program::Program() {
}

Program::~Program() {

}

void Program::bind() {
	glUseProgram(program);
}

void Program::unbind() {
	glUseProgram(0);
}

bool Program::checkLocations() {
	bool allFound = true;
	std::vector<std::string> notFound;

	std::map<std::string, GLint>::iterator it;
	for (it = locations.begin(); it != locations.end(); it++) {
		if (it->second == -1) {
			notFound.push_back(it->first);
			allFound = false;
		}
	}

	if (!allFound) {
		std::cout << "Program: " << name << std::endl;
		for (int i = 0; i < notFound.size(); i++) {
			std::cout << notFound[i] << " not found." << std::endl;
		}
	}

	return allFound;
}

GLint Program::getLocation(const std::string& key) {
	return locations.at(key);
}


void Program::set(const std::string& key, float value) {
	glUniform1f(locations.at(key), value);
}

void Program::set(const std::string& key, int value) {
	glUniform1i(locations.at(key), value);
}

void Program::set(const std::string& key, bool value) {
	glUniform1i(locations.at(key), value);
}

void Program::set(const std::string& key, const glm::vec2& value) {
	glUniform2fv(locations.at(key), 1, glm::value_ptr(value));
}

void Program::set(const std::string& key, const glm::vec3& value) {
	glUniform3fv(locations.at(key), 1, glm::value_ptr(value));
}

void Program::set(const std::string& key, const glm::vec4& value) {
	glUniform4fv(locations.at(key), 1, glm::value_ptr(value));
}

void Program::set(const std::string& key, const glm::mat3& value) {
	glUniformMatrix3fv(locations.at(key), 1, GL_FALSE, glm::value_ptr(value));
}

void Program::set(const std::string& key, const glm::mat4& value) {
	glUniformMatrix4fv(locations.at(key), 1, GL_FALSE, glm::value_ptr(value));
}


void Program::linkProgram() {
	glLinkProgram(program);

	GLint shader_status;
	glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
	if (!shader_status) {
		std::cerr << "Unable to create shader program!" << std::endl;

		char buffer[512];
		glGetProgramInfoLog(program, 512, NULL, buffer); // inserts the error into the buffer
		std::cerr << buffer << std::endl;
		Engine::getEngine()->stop(1);
	}
}

GLuint Program::loadShader(const char* fileName, GLenum shaderType) {
	std::ifstream fin(fileName);
	if (!fin) {
		std::cerr << "Unable to open shader file: " << fileName << std::endl;
		Engine::getEngine()->stop(1);
	}

	std::string file_contents;
	fin.seekg(0, std::ios::end);
	auto length = fin.tellg();
	fin.seekg(0, std::ios::beg);

	file_contents.reserve(length);
	auto fileIterator = std::istreambuf_iterator<char>(fin);
	auto fileIteratorEnd = std::istreambuf_iterator<char>();
	file_contents.assign(fileIterator, fileIteratorEnd);

	fin.close();

	const char *shaderStr = file_contents.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderStr, NULL);
	glCompileShader(shader);

	GLint shader_status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);
	if (!shader_status) {
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);

		std::string shaderTypeStr = "shader";
		std::cerr << "Failed to compile " << shaderTypeStr << " loaded from " << fileName << std::endl;
		std::cerr << "Compile Error: " << buffer << std::endl;
		Engine::getEngine()->stop(1);
	}

	return shader;
}
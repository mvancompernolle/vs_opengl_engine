#ifndef OPENGL_ENGINE_PROGRAM_H
#define OPENGL_ENGINE_PROGRAM_H

#include <map>
#include <string>

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Program {
public:
	Program();
	virtual ~Program();
	virtual void init() {}

	void bind();
	void unbind();
	bool checkLocations();

	GLint getLocation(const std::string& key);

	void set(const std::string& key, float value);
	void set(const std::string& key, int value);
	void set(const std::string& key, bool value);
	void set(const std::string& key, const glm::vec2& value);
	void set(const std::string& key, const glm::vec3& value);
	void set(const std::string& key, const glm::vec4& value);
	void set(const std::string& key, const glm::mat3& value);
	void set(const std::string& key, const glm::mat4& value);

protected:
	static GLuint loadShader(const char* fileName, GLenum shaderType);
	void linkProgram();

	std::string name;
	GLuint program;
	GLuint shaders[3];
	std::map<std::string, GLint> locations;
};


#endif //OPENGL_ENGINE_PROGRAM_H
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
public:
	Texture(const std::string& fileName, GLenum target = GL_TEXTURE_2D, std::string type = "texture_diffuse");
	virtual ~Texture();
	virtual void bind(GLenum textureUnit);

	std::string fileName;
	GLenum target;
	GLuint textureID;
	std::string type;
};

#endif // TEXTURE_HPP
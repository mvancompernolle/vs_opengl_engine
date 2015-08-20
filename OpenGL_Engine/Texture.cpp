#include "Texture.h"
#include "Engine.h"

#include <iostream>

#include <FreeImagePlus.h>

Texture::Texture(const std::string& fileName, GLenum target, std::string type) : fileName(fileName), target(target), type(type) {

	fipImage image;
	if (image.load(fileName.c_str())) {
		if (image.getImageType() == FIT_UNKNOWN) {
			std::cerr << "Unknown image type for texture: " << fileName << std::endl;
			return;
		}

		image.convertTo32Bits();

		glGenTextures(1, &textureID);
		glBindTexture(target, textureID);
		glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		if (target == GL_TEXTURE_2D) {
			glTexImage2D(target, 0, GL_RGBA, image.getWidth(), image.getHeight(),
				0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)image.accessPixels());
		}
		else if(target == GL_TEXTURE_1D) {
			glTexImage1D(target, 0, GL_RGBA, image.getWidth(), 0,
				GL_BGRA, GL_UNSIGNED_BYTE, (void*)image.accessPixels());
		}

		glGenerateMipmap(target);
		glBindTexture(target, 0);
	}
	else {
		std::cout << "Failed to load texture " << fileName << std::endl;
	}

}

Texture::~Texture() {

}

void Texture::bind(GLenum textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(target, textureID);
}
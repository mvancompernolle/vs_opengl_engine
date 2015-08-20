#include "ProgramDirLight.h"
#include <iostream>

ProgramDirLight::ProgramDirLight() {
	name = "DirLight";
}

void ProgramDirLight::init() {
	program = glCreateProgram();

	shaders[0] = Program::loadShader("light.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("dirLight.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["color"] = glGetUniformLocation(program, "dirLight.base.color");
	locations["ambient"] = glGetUniformLocation(program, "dirLight.base.ambientIntensity");
	locations["diffuse"] = glGetUniformLocation(program, "dirLight.base.diffuseIntensity");
	locations["dir"] = glGetUniformLocation(program, "dirLight.direction");

	ProgramLight::init();

	checkLocations();
}

ProgramDirLight::~ProgramDirLight() {

}

void ProgramDirLight::setDirLight(const DirectionalLight& light) {
	set("color", light.color);
	set("ambient", light.ambientIntensity);
	set("diffuse", light.diffuseIntensity);
	set("dir", light.direction);
}

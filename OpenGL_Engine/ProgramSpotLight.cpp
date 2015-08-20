#include "ProgramSpotLight.h"

#include <iostream>

ProgramSpotLight::ProgramSpotLight() {
	name = "PointLight";
}

void ProgramSpotLight::init() {

	program = glCreateProgram();

	shaders[0] = Program::loadShader("light.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("spotLight.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["color"] = glGetUniformLocation(program, "spotLight.base.base.color");
	locations["ambient"] = glGetUniformLocation(program, "spotLight.base.base.ambientIntensity");
	locations["diffuse"] = glGetUniformLocation(program, "spotLight.base.base.diffuseIntensity");
	locations["pos"] = glGetUniformLocation(program, "spotLight.base.pos");
	locations["constant"] = glGetUniformLocation(program, "spotLight.base.atten.constant");
	locations["linear"] = glGetUniformLocation(program, "spotLight.base.atten.linear");
	locations["exp"] = glGetUniformLocation(program, "spotLight.base.atten.ex");
	locations["dir"] = glGetUniformLocation(program, "spotLight.direction");
	locations["cutoff"] = glGetUniformLocation(program, "spotLight.cutoff");

	ProgramLight::init();

	checkLocations();
}

void ProgramSpotLight::setSpotLight(const SpotLight& light) {
	set("color", light.color);
	set("ambient", light.ambientIntensity);
	set("diffuse", light.diffuseIntensity);
	set("pos", light.pos);
	set("constant", light.atten.constant);
	set("linear", light.atten.linear);
	set("exp", light.atten.exp);
	set("dir", light.direction);
	set("cutoff", light.cutoff);
}

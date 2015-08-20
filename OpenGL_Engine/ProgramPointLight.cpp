#include "ProgramPointLight.h"

#include <iostream>

ProgramPointLight::ProgramPointLight() {
	name = "PointLight";
}

void ProgramPointLight::init() {

	program = glCreateProgram();

	shaders[0] = Program::loadShader("light.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("pointLight.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["color"] = glGetUniformLocation(program, "pLight.base.color");
	locations["ambient"] = glGetUniformLocation(program, "pLight.base.ambientIntensity");
	locations["diffuse"] = glGetUniformLocation(program, "pLight.base.diffuseIntensity");
	locations["pos"] = glGetUniformLocation(program, "pLight.pos");
	locations["constant"] = glGetUniformLocation(program, "pLight.atten.constant");
	locations["linear"] = glGetUniformLocation(program, "pLight.atten.linear");
	locations["exp"] = glGetUniformLocation(program, "pLight.atten.ex");

	ProgramLight::init();

	checkLocations();
}

void ProgramPointLight::setPointLight(const PointLight& light) {
	set("color", light.color);
	set("ambient", light.ambientIntensity);
	set("diffuse", light.diffuseIntensity);
	set("pos", light.pos);
	set("constant", light.atten.constant);
	set("linear", light.atten.linear);
	set("exp", light.atten.exp);
}
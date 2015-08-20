#include "ProgramGeometry.h"
#include <iostream>

ProgramGeometry::ProgramGeometry() {
	name = "Geometry";
}

void ProgramGeometry::init() {
	program = glCreateProgram();

	shaders[0] = Program::loadShader("geometry.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("geometry.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
	locations["vs_tex"] = glGetAttribLocation(program, "vs_tex");
	locations["vs_normal"] = glGetAttribLocation(program, "vs_normal");
	locations["texture_diffuse1"] = glGetUniformLocation(program, "texture_diffuse1");
	locations["texture_specular1"] = glGetUniformLocation(program, "texture_specular1");
	locations["mvp"] = glGetUniformLocation(program, "mvp");
	locations["model"] = glGetUniformLocation(program, "model");
	locations["spec_power"] = glGetUniformLocation(program, "specularPower");

	checkLocations();
}

ProgramGeometry::~ProgramGeometry() {

}
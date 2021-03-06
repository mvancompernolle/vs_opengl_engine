#include "ProgramModel.h"
#include "Engine.h"
#include <iostream>

ProgramModel::ProgramModel() {
	name = "Model";
}

void ProgramModel::init() {
	program = glCreateProgram();

	shaders[0] = Program::loadShader("model.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("model.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
	locations["vs_tex"] = glGetAttribLocation(program, "vs_tex");
	locations["texture_diffuse1"] = glGetUniformLocation(program, "texture_diffuse1");
	locations["texture_specular1"] = glGetUniformLocation(program, "texture_specular1");
	locations["mvp"] = glGetUniformLocation(program, "mvp");

	checkLocations();
}

ProgramModel::~ProgramModel() {

}
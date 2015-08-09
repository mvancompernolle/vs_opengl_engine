#include "ProgramModel.h"
#include "Engine.h"
#include <iostream>

ProgramModel::ProgramModel() {

	shaders[0] = Program::loadShader("model.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("model.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
	locations["vs_tex"] = glGetAttribLocation(program, "vs_tex");
	locations["texture_diffuse1"] = glGetUniformLocation(program, "texture_diffuse1");
	locations["texture_diffuse2"] = glGetUniformLocation(program, "texture_diffuse2");
	locations["texture_diffuse3"] = glGetUniformLocation(program, "texture_diffuse3");
	locations["texture_diffuse4"] = glGetUniformLocation(program, "texture_diffuse4");
	locations["texture_diffuse5"] = glGetUniformLocation(program, "texture_diffuse5");
	locations["texture_diffuse6"] = glGetUniformLocation(program, "texture_diffuse6");
	locations["texture_diffuse7"] = glGetUniformLocation(program, "texture_diffuse7");
	locations["texture_diffuse8"] = glGetUniformLocation(program, "texture_diffuse8");
	locations["texture_specular1"] = glGetUniformLocation(program, "texture_specular1");
	locations["texture_specular2"] = glGetUniformLocation(program, "texture_specular2");
	locations["texture_specular3"] = glGetUniformLocation(program, "texture_specular3");
	locations["texture_specular4"] = glGetUniformLocation(program, "texture_specular4");
	locations["texture_specular5"] = glGetUniformLocation(program, "texture_specular5");
	locations["texture_specular6"] = glGetUniformLocation(program, "texture_specular6");
	locations["texture_specular7"] = glGetUniformLocation(program, "texture_specular7");
	locations["texture_specular8"] = glGetUniformLocation(program, "texture_specular8");
	locations["mvp"] = glGetUniformLocation(program, "mvp");

}

ProgramModel::~ProgramModel() {

}
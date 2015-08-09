#include "Program2D.h"
#include "Engine.h"
#include <iostream>

Program2D::Program2D() {

	shaders[0] = Program::loadShader("shader2D.vs", GL_VERTEX_SHADER);
	shaders[1] = Program::loadShader("shader2D.fs", GL_FRAGMENT_SHADER);

	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	linkProgram();

	locations["vs_pos"] = glGetAttribLocation(program, "vs_pos");
	locations["vs_tex"] = glGetAttribLocation(program, "vs_tex");
	locations["ourTexture"] = glGetUniformLocation(program, "ourTexture");
	locations["mvp"] = glGetUniformLocation(program, "mvp");

}

Program2D::~Program2D() {

}
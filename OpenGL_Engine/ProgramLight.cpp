#include "ProgramLight.h"

// SOURCE : http://ogldev.atspace.co.uk/www/tutorial36/tutorial36.html

#include <iostream>

ProgramLight::ProgramLight() {
	name = "Light";
}

void ProgramLight::init() {

	// get uniforms
	locations["mvp"] = glGetUniformLocation(program, "mvp");
	locations["colorMap"] = glGetUniformLocation(program, "colorMap");
	locations["normalMap"] = glGetUniformLocation(program, "normalMap");
	locations["posMap"] = glGetUniformLocation(program, "posMap");
	locations["specularMap"] = glGetUniformLocation(program, "specularMap");
	locations["screenSize"] = glGetUniformLocation(program, "screenSize");
	locations["cameraPos"] = glGetUniformLocation(program, "cameraPos");
}


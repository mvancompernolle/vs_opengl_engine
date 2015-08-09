// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "Graphics.h"
#include "Engine.h"
#include "Camera.h"
#include "Box.h"
#include "Model.h"
#include "ProgramModel.h"
#include <iostream>

Graphics::Graphics() {

	width = 1920;
	height = 1080;

	// init glfw window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// create window object
	window = glfwCreateWindow((float)width, (float)height, "Game Engine", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		Engine::getEngine()->stop(1);
	}
	glfwMakeContextCurrent(window);

	// initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		Engine::getEngine()->stop(1);
	}

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	proj = glm::perspective(60.0f, (float)width / (float)height, 0.1f, 100.0f);

	glViewport(0, 0, (float)width, (float)height);
	glClearColor(0.0, 0.0, 1.0, 1);
	glEnable(GL_DEPTH_TEST);

	camera = new Camera();

	box = new Box(1, 1);
	for (int i = 0; i < 1; i++) {
		models.push_back(new Model("nanosuit.obj"));
	}
	programModel = new ProgramModel;
}

Graphics::~Graphics() {
	glfwTerminate();
}

void Graphics::tick(float dt) {
	camera->tick(dt);
	view = camera->getView();
	box->tick(dt);
	if (!glfwWindowShouldClose(window))
		render();
}

void Graphics::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	box->render();
	programModel->bind();

	for (int i = 0; i < models.size(); i++) {
		glm::mat4 m;
		m = glm::translate(m, glm::vec3(i*2, 0, 0));
		programModel->set("mvp", proj * view * m);
		models[0]->render(*programModel);
	}

	glfwSwapBuffers(window);
}

void Graphics::setFOV(float fov) {
	proj = glm::perspective(fov, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void Graphics::stop() {

}

void Graphics::windowResized() {

}
#include "Engine.h"
#include "Graphics.h"
#include "Input.h"
#include "Camera.h"
#include "iostream"

std::map<int, bool> Input::keysPressed;
GLfloat Input::lastX;
GLfloat Input::lastY;
bool Input::firstMouse = true;
float Input::fov = 60.0f;

Input::Input() {
	glfwSetInputMode(Engine::getEngine()->graphics->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(Engine::getEngine()->graphics->window, keyCallBack);
	glfwSetCursorPosCallback(Engine::getEngine()->graphics->window, mouseCallBack);
	glfwSetScrollCallback(Engine::getEngine()->graphics->window, scrollCallBack);

	lastX = Engine::getEngine()->graphics->width / 2, lastY = Engine::getEngine()->graphics->height / 2;
}

Input::~Input() {

}

void Input::tick(float dt) {
	glfwPollEvents();
	handleMovementKeys();
}

void Input::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application

	if (action == GLFW_PRESS) {
		keysPressed[key] = true;

		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			Engine::getEngine()->stop();
			break;
		case GLFW_KEY_W:
			keysPressed[GLFW_KEY_W] = true;
			break;
		case GLFW_KEY_S:
			keysPressed[GLFW_KEY_S] = true;
			break;
		case GLFW_KEY_A:
			keysPressed[GLFW_KEY_A] = true;
			break;
		case GLFW_KEY_D:
			keysPressed[GLFW_KEY_D] = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		keysPressed[key] = false;
	}

}

void Input::mouseCallBack(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	// update the camera
	Engine::getEngine()->graphics->camera->processMouseMovement(xoffset, yoffset);

}

void Input::scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 90.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 90.0f)
		fov = 90.0f;

	Engine::getEngine()->graphics->setFOV(fov);
}

void Input::stop() {

}

const std::map<int, bool>& Input::getKeyMap() {
	return keysPressed;
}

void Input::handleMovementKeys() {
	if (keysPressed[GLFW_KEY_W])
		Engine::getEngine()->graphics->camera->processKeyboard(FORWARD);
	if (keysPressed[GLFW_KEY_S])
		Engine::getEngine()->graphics->camera->processKeyboard(BACKWARD);
	if (keysPressed[GLFW_KEY_A])
		Engine::getEngine()->graphics->camera->processKeyboard(LEFT);
	if (keysPressed[GLFW_KEY_D])
		Engine::getEngine()->graphics->camera->processKeyboard(RIGHT);
}
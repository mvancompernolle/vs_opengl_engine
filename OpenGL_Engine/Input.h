#ifndef OPENGL_ENGINE_INPUT_H
#define OPENGL_ENGINE_INPUT_H


#include <map>
#include <GLFW/glfw3.h>

class Input {
public:
	Input();
	~Input();

	void tick(float dt);
	void stop();
	const std::map<int, bool>& getKeyMap();

private:
	static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseCallBack(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
	void handleMovementKeys();
	float sensitivity;

	static GLfloat lastX, lastY;
	static std::map<int, bool> keysPressed;
	static bool firstMouse;
	static float fov;
};


#endif //OPENGL_ENGINE_INPUT_H
#ifndef OPENGL_ENGINE_GRAPHICS_H
#define OPENGL_ENGINE_GRAPHICS_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Engine;
class Box;
class Camera;
class Model;
class Program;

class Graphics {
public:
	Graphics();
	~Graphics();

	void tick(float dt);
	void render();
	void stop();
	void windowResized();
	void setFOV(float fov);

	GLFWwindow* window;
	int width, height;
	glm::mat4 view, proj;
	Camera* camera;
	Program* programModel;
private:
	Box* box;
	std::vector<Model*> models;
};


#endif //OPENGL_ENGINE_GRAPHICS_H
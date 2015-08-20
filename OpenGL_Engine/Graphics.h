#ifndef OPENGL_ENGINE_GRAPHICS_H
#define OPENGL_ENGINE_GRAPHICS_H

#include "GBuffer.h"
#include "LightingManager.h"
#include "ProgramModel.h"
#include "ProgramGeometry.h"
#include "ProgramDirLight.h"
#include "ProgramPointLight.h"
#include "ProgramSpotLight.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Engine;
class Box;
class Camera;
class Model;
class Program;
class GBuffer;
class LightingManager;

class Graphics {
public:
	Graphics();
	~Graphics();

	void tick(float dt);
	void render();
	void stop();
	void windowResized();
	void setFOV(float fov);
	void geometryPassDS();
	void dirLightPassDS();
	void pointLightPassDS();
	void spotLightPassDS();
	GLfloat calcPointLightSphere(const PointLight& light) const;

	GLFWwindow* window;
	int width, height;
	glm::mat4 view, proj;
	Camera* camera;

	// programs
	ProgramModel programModel;
	ProgramGeometry programGeometry;
	ProgramDirLight programDirLight;
	ProgramPointLight programPointLight;
	ProgramSpotLight programSpotLight;
private:
	Box* box;
	std::vector<Model*> models;
	GBuffer deferredBuffer;
	LightingManager lightingMgr;
	Model* renderQuad, *renderSphere;
};


#endif //OPENGL_ENGINE_GRAPHICS_H
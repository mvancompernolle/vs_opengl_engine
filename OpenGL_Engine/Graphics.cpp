#define GLEW_STATIC
#include <GL/glew.h>

#include "Graphics.h"
#include "Camera.h"
#include "Engine.h"
#include "LightingManager.h"
#include "Model.h"
#include "Box.h"
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
	glClearColor(0.0, 0.0, 0.0, 1);
	glEnable(GL_DEPTH_TEST);

	camera = new Camera();

	models.push_back(new Model("nanosuit.obj"));

	// initialize quad for rendering lights
	renderQuad = new Model("quad.obj", false);
	renderSphere = new Model("sphere.obj", false);

	// initialize shader programs
	programModel.init();
	programGeometry.init();

	programDirLight.init();
	programDirLight.bind();
	programDirLight.set("posMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	programDirLight.set("colorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	programDirLight.set("normalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	programDirLight.set("specularMap", GBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
	programDirLight.set("screenSize", glm::vec2(width, height));

	programPointLight.init();
	programPointLight.bind();
	programPointLight.set("posMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	programPointLight.set("colorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	programPointLight.set("normalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	programPointLight.set("specularMap", GBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
	programPointLight.set("screenSize", glm::vec2(width, height));

	programSpotLight.init();
	programSpotLight.bind();
	programSpotLight.set("posMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	programSpotLight.set("colorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	programSpotLight.set("normalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	programSpotLight.set("specularMap", GBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
	programSpotLight.set("screenSize", glm::vec2(width, height));

	// initialize buffer for deffered shading
	deferredBuffer.init(width, height);

	// initialize the lighting manager
	lightingMgr.init();
}

Graphics::~Graphics() {
	glfwTerminate();
}

void Graphics::tick(float dt) {
	lightingMgr.tick(dt);
	camera->tick(dt);
	view = camera->getView();

	if (!glfwWindowShouldClose(window))
		render();
}

void Graphics::render() {
	// clear the all the buffers from the previous screen rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// bind the deferred buffer
	deferredBuffer.startFrame();

	// render geometry info into the buffers
	geometryPassDS();

	// perform light calculations
	dirLightPassDS();
	spotLightPassDS();
	//pointLightPassDS();

	glDisable(GL_BLEND);

	// copy rendering results into default buffer
	deferredBuffer.bindForFinalPass();
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glfwSwapBuffers(window);
}

void Graphics::setFOV(float fov) {
	proj = glm::perspective(fov, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void Graphics::stop() {

}

void Graphics::windowResized() {

}

void Graphics::geometryPassDS() {
	// bind the geometry program and set the 4 different textures as outputs
	programGeometry.bind();
	deferredBuffer.bindForGeometryPass();

	// enable the depth test and clear previous buffers
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// render models into buffers
	for (int i = 0; i < models.size(); i++) {
		glm::mat4 m;
		m = glm::translate(m, glm::vec3(i*2, 0, -20));
		programGeometry.set("spec_power", 32);
		programGeometry.set("model", m);
		programGeometry.set("mvp", proj * view * m);
		models[i]->render(programGeometry);
	}

	glDepthMask(GL_FALSE);
}

void Graphics::dirLightPassDS() {
	// enable the directional light program 
	programDirLight.bind();

	// set the final texture as an output and results of geometry shader as input
	deferredBuffer.bindForLightPass();

	// disable the depth test and enable blending
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	
	// pass in the direction of the light and the cameras position then apply lighting
	programDirLight.setDirLight(lightingMgr.dirLight);
	programDirLight.set("cameraPos", camera->Position);
	programDirLight.set("mvp", glm::mat4());
	renderQuad->render(programDirLight);
}

void Graphics::pointLightPassDS() {
	programPointLight.bind();
	deferredBuffer.bindForLightPass();

	for (PointLight pLight : lightingMgr.pointLights) {
		// determine the scale of the point light
		GLfloat scale = calcPointLightSphere(pLight);
		glm::mat4 matrix = glm::translate(glm::mat4(), pLight.pos);

		// apply lighting from the point light
		programPointLight.setPointLight(pLight);
		programPointLight.set("cameraPos", camera->Position);
		programPointLight.set("mvp", proj * view * glm::scale(matrix, glm::vec3(scale, scale, scale)));
		renderSphere->render(programPointLight);
	}
}

void Graphics::spotLightPassDS() {
	// spot lights
	programSpotLight.bind();
	deferredBuffer.bindForLightPass();

	for (SpotLight spotLight : lightingMgr.spotLights) {
		programSpotLight.setSpotLight(spotLight);
		programSpotLight.set("cameraPos", camera->Position);
		programSpotLight.set("mvp", glm::mat4());
		renderQuad->render(programSpotLight);
	}
}

GLfloat Graphics::calcPointLightSphere(const PointLight& light) const {
	float maxColor = fmax(fmax(light.color.x, light.color.y), light.color.z);

	float returnVal = sqrtf((maxColor * 256 * light.diffuseIntensity / light.atten.exp) + light.atten.constant); // exp and constant
	//float returnVal = maxColor * (1/light.atten.linear) * 256; // linear
	/*float returnVal = (-light.atten.linear + sqrtf(light.atten.linear * light.atten.linear - 4 * light.atten.exp
	* (light.atten.constant - 256 * maxColor * light.diffuseIntensity))) / 2 * light.atten.exp;   */
	//std::cout << maxColor << std::endl;
	return returnVal;
}

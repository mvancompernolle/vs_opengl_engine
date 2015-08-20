#include "LightingManager.h"

#include <iostream>

#include "Engine.h"
#include "Graphics.h"
#include "Camera.h"

LightingManager::LightingManager(){

	dirLightAngle = -0.75f;
	increaseLightAngle();
}

LightingManager::~LightingManager() {

}

void LightingManager::init() {

	// init directional light
	dirLight.diffuseIntensity = 1.0f;
	dirLight.ambientIntensity = 0.2f;

	// init spot lights

	// init spot lights
	// first spot lights is camera flashlight
	SpotLight cameraLight;
	cameraLight.color = glm::vec3(1.0, 1.0, 1.0);
	cameraLight.diffuseIntensity = 1.0f;
	cameraLight.ambientIntensity = 1.0f;
	cameraLight.atten.constant = 1;
	cameraLight.atten.linear = .005;
	//cameraLight.pos = Engine::getEngine()->graphics->camera->Position;
	//cameraLight.direction = Engine::getEngine()->graphics->camera->Front;
	cameraLight.cutoff = .97;
	spotLights.push_back(cameraLight);

	bulletLight.diffuseIntensity = 20.0f;
	bulletLight.color = glm::vec3(1, 1, 0);
	bulletLight.atten.constant = 1.0f;
	bulletLight.atten.linear = 0.00f;
	bulletLight.atten.exp = 0.0001f;
}

void LightingManager::tick(float dt) {

	// tick all of the lights in the world
	// tick the cameraLight
	spotLights[0].pos = Engine::getEngine()->graphics->camera->Position;
	spotLights[0].direction = Engine::getEngine()->graphics->camera->Front;
}

void LightingManager::stop() {

}

void LightingManager::setDirectionalLight(DirectionalLight dirLight) {

	this->dirLight = dirLight;
}

void LightingManager::addSpotLight(SpotLight spotLight) {

	spotLights.push_back(spotLight);
}

void LightingManager::addPointLight(PointLight pointLight) {

	pointLights.push_back(pointLight);
}

void LightingManager::increaseLightAngle() {

	dirLightAngle -= 0.01;

	float y = -cos(dirLightAngle + 1.57);
	float x = -sin(dirLightAngle + 1.57);
	dirLight.direction = glm::normalize(glm::vec3(x, y, 0));
}

void LightingManager::decreaseLightAngle() {

	dirLightAngle += 0.01;

	float y = -cos(dirLightAngle + 1.57);
	float x = -sin(dirLightAngle + 1.57);
	dirLight.direction = glm::normalize(glm::vec3(x, y, 0));
}

void LightingManager::addTempPointLight(glm::vec3 pos, glm::vec3 color, float lifeTime) {
	if (pointLights.size() < 8) {
		PointLight pLight;
		pLight.diffuseIntensity = 1.0f;
		pLight.color = color;
		pLight.atten.constant = 1.0f;
		pLight.atten.linear = 0.00f;
		pLight.atten.exp = 0.000001f;
		pLight.timeToLive = lifeTime;
		pLight.pos = pos;
		pointLights.push_back(pLight);
	}
}
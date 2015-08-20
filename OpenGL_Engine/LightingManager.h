#pragma once
#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include <vector>
#include <glm/glm.hpp>
#include "Lights.h"

class LightingManager {

public:

	// public functions
	LightingManager();
	~LightingManager();

	void init();
	void tick(float dt);
	void stop();

	void setDirectionalLight(DirectionalLight dirLight);
	void addSpotLight(SpotLight spotLight);
	void addPointLight(PointLight pointLight);
	void increaseLightAngle();
	void decreaseLightAngle();
	void addTempPointLight(glm::vec3 pos, glm::vec3 color, float lifeTime);

	// public variables
	DirectionalLight dirLight;
	PointLight bulletLight;
	std::vector<SpotLight> spotLights;
	std::vector<PointLight> pointLights;

private:

	// private variables
	float dirLightAngle;

};


#endif // END LIGHTING_MANAGER_H


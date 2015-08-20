#pragma once
#ifndef LIGHTS_H
#define LIGHTS_H

#include <glm/glm.hpp>

// SOURCE : http://ogldev.atspace.co.uk/www/tutorial37/tutorial37.html


struct BaseLight {

	glm::vec3 color;
	float ambientIntensity;
	float diffuseIntensity;

	BaseLight() {

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		ambientIntensity = 0.0f;
		diffuseIntensity = 0.0f;
	}
};

struct DirectionalLight : public BaseLight {

	glm::vec3 direction;

	DirectionalLight() {

		direction = glm::vec3(0.0f, 0.0f, 0.0f);
	}
};

struct PointLight : public BaseLight {

	glm::vec3 pos;
	float timeToLive, dt;

	struct {

		float constant;
		float linear;
		float exp;
	} atten;

	PointLight() {

		pos = glm::vec3(0.0f, 0.0f, 0.0f);
		atten.constant = 0.0f;
		atten.linear = 0.0f;
		atten.exp = 0.0f;
		dt = 0.0f;
		timeToLive = -1;
	}
};

struct SpotLight : public PointLight {

	glm::vec3 direction;
	float cutoff;

	SpotLight() {

		direction = glm::vec3(0.0f, 0.0f, 0.0f);
		cutoff = 0.0f;
	}
};


#endif // END LIGHTS_H
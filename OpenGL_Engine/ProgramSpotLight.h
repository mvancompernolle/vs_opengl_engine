#pragma once
#ifndef PROGRAM_SPOT_LIGHT
#define	PROGRAM_SPOT_LIGHT

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ProgramLight.h"
#include "Lights.h"


class ProgramSpotLight : public ProgramLight {

public:

	// public functions
	ProgramSpotLight();
	void init();
	void setSpotLight(const SpotLight& light);

private:
};


#endif // END PROGRAM_SPOT_LIGHT


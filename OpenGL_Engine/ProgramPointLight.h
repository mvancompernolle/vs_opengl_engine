#pragma once
#ifndef POINT_LIGHT_DS_PROGRAM
#define	POINT_LIGHT_DS_PROGRAM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ProgramLight.h"
#include "Lights.h"


class ProgramPointLight : public ProgramLight {

public:

	// public functions
	ProgramPointLight();
	void init();
	void setPointLight(const PointLight& light);

private:
};


#endif // END POINT_LIGHT_DS_PROGRAM


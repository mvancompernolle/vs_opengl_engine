#pragma once
#ifndef DIR_LIGHT_PROGRAM_H
#define	DIR_LIGHT_PROGRAM_H

#include "ProgramLight.h"
#include "Lights.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ProgramDirLight : public ProgramLight {

public:

	// public functions
	ProgramDirLight();
	void init();
	void setDirLight(const DirectionalLight& light);
	virtual ~ProgramDirLight();

private:

};

#endif // end DIR_LIGHT_PROGRAM_H
#pragma once
#ifndef GEOMETRY_PROGRAM_H
#define	GEOMETRY_PROGRAM_H

#include "Program.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ProgramGeometry : public Program {

public:

	// public functions
	ProgramGeometry();
	void init();
	virtual ~ProgramGeometry();

private:

};

#endif // end GEOMETRY_PROGRAM_H


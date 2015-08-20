#pragma once
#ifndef LIGHT_PROGRAM
#define LIGHT_PROGRAM

// SOURCE : http://ogldev.atspace.co.uk/www/tutorial36/tutorial36.html

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"

class ProgramLight : public Program {

public:

	// public functions
	ProgramLight();
	virtual void init();

private:
};


#endif // END LIGHT_PROGRAM


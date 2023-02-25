#pragma once

#include "..\DragonFly Engine\Object.h"

// Define reticle visual char
#define RETICLE_CHAR '+'

class Reticle : public df::Object
{
public:
	Reticle();
	
	// Override function to draw reticle on game screen
	int draw(void) override;
	
	// Override event handler from Object
	int eventHandler(const df::Event* p_e) override;
};
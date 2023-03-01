#pragma once

// Engine Includes
#include "..\DragonFly Engine\Event.h"
#include "..\DragonFly Engine\ViewObject.h"

#define POINTS_STRING "Points"

class Points : public df::ViewObject
{
public:
	Points();
	int eventHandler(const df::Event* p_e);
};


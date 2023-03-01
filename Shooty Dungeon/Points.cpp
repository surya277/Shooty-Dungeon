
// Engine Includes
#include "..\DragonFly Engine\DisplayManager.h"
#include "..\DragonFly Engine\EventStep.h"

// Game Includes
#include "Points.h"
#include "../DragonFly Engine/EventView.h"

Points::Points() {

	setLocation(df::TOP_RIGHT);
	// Set string to view
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);

}

// Handle events
// Return 0 if ignored, else 1.

int Points::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		if (dynamic_cast <const df::EventStep*> (p_e)->getStepCount() % 30 == 0) {
			setValue(getValue() + 1);
		}
		return 1;
	}

	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	

	return 0;
}
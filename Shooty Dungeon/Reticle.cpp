// Engine Includes
#include "../DragonFly Engine/WorldManager.h"
#include "../DragonFly Engine/DisplayManager.h"
#include "../DragonFly Engine/EventMouse.h"

// Game Includes
#include "Reticle.h"

Reticle::Reticle()
{
	// Set object type
	setType("Reticle");

	// Ignore collision and overlap
	setSolidness(df::SPECTRAL);

	// Set display layer
	setAltitude(df::MAX_ALTITUDE);

	// Set object initial location
	df::Vector init_location;
	init_location.setX(WM.getBoundary().getHorizontal() / 2);
	init_location.setY(WM.getBoundary().getVertical() / 2);
	setPosition(init_location);
}

// Object event handler
int Reticle::eventHandler(const df::Event* p_e)
{
	// Handle mouse events
	if (p_e->getType() == df::MSE_EVENT)
	{
		const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*>(p_e);

		if (p_mouse_event->getMouseAction() == df::MOVED)
		{
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}

	return 0;
}

// Draw reticle char to game screen
int Reticle::draw()
{
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}